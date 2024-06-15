use festival

go

select * from bendovi
select * from festivali
select * from karte
select * from lineup_festivala
select * from muzicari
select * from posetioci
select * from sastav_benda
select * from tip_instrumenta

go

-- 1. zadatak
create table VecProdateKarte
(
	id int primary key identity(1,1),
	idFestivala int,
	godina int,
	dan int,
	idPosetioca int,
	cena int
)
--drop table VecProdateKarte
alter table VecProdateKarte add constraint fk_id_fest foreign key (idFestivala) references festivali(idFestivala)
alter table VecProdateKarte add constraint fk_id_pos foreign key (idPosetioca) references posetioci(idPosetioca)

go

create trigger NaUnosKarte on karte
instead of insert
as
begin
	insert into VecProdateKarte
	select distinct i.* from inserted i
	where exists (
					select * 
					from karte k
					where i.idFestivala = k.idFestivala
						and i.idPosetioca = k.idPosetioca
						and i.dan = k.dan
						and i.godina = k.godina
				 )

	insert into karte
	select distinct i.* from inserted i
	where not exists (
					select * 
					from karte k
					where i.idFestivala = k.idFestivala
						and i.idPosetioca = k.idPosetioca
						and i.dan = k.dan
						and i.godina = k.godina
				 )
end

go

-- 2. zadatak
create function DajSastavBenda
(
	@idBend int,
	@godina int
)
returns @sastav table
(
	id int,
	ime varchar(20),
	prezime varchar(20)
)
begin
	insert into @sastav
	select m.idMuzicara, m.ime, m.prezime
	from (
			select *
			from sastav_benda
			where idBenda = @idBend and @godina >= datepart(year, datum1) and (datum2 is NULL or @godina <= datepart(year, datum2))
		) s join muzicari m on s.idMuzicara = m.idMuzicara

	return
end

go

select *
from dbo.DajSastavBenda(1, 1988)

go


-- 3. zadatak
create function DajZaradu
(
	@idFestivala int,
	@godina int
)
returns float
as
begin
	declare @zarada int
	declare @brBendova int

	select @zarada = sum(cena)
	from karte
	where idFestivala = @idFestivala and godina = @godina

	select @brBendova = count(*)
	from lineup_festivala
	where idFestivala = @idFestivala and godina = @godina

	set @zarada = @zarada*1.0 / @brBendova

	return @zarada
end

go

select dbo.DajZaradu(1,2004)

go


-- 4. zadatak
create function DajZaraduBendovaPoFestivalima ()
returns @zarade table
(
	idFestivala int,
	godina int,
	idBenda int,
	zaradaBenda float
)
as
begin
	insert into @zarade
	select idFestivala, godina, idBenda, dbo.DajZaradu(idFestivala, godina)
	from lineup_festivala

	return
end

go

select *
from dbo.DajZaraduBendovaPoFestivalima()

go

-- 5. zadatak
create procedure PrikaziZaraduPoClanuBenda
(
	@idFest int,
	@godina int,
	@idBend int,
	@zarada float
)
as
begin
	declare @zaradaPoClanu float
	declare @brojClanova int

	select @brojClanova = count(*)
	from dbo.DajSastavBenda(@idBend, @godina)

	if(@brojClanova > 0)
	begin
		set @zaradaPoClanu = @zarada / @brojClanova
	end
	else
	begin
		set @zaradaPoClanu = 0
	end

	--kursor
	if @brojClanova > 0 and @zaradaPoClanu > 1000
	begin
		declare @idMuz int
		declare @imeMuz varchar(20)
		declare @prezimeMuz varchar(20)
		declare kursorPoMuzicarima cursor for select id, ime, prezime from dbo.DajSastavBenda(@idBend, @godina)

		open kursorPoMuzicarima
			fetch next from kursorPoMuzicarima into @idMuz, @imeMuz, @prezimeMuz
			while @@FETCH_STATUS = 0
			begin
				print concat(@imeMuz, ' ', @prezimeMuz, ' ', @idBend, ' ', @zaradaPoClanu)
				fetch next from kursorPoMuzicarima into @idMuz, @imeMuz, @prezimeMuz
			end
		close kursorPoMuzicarima
		deallocate kursorPoMuzicarima
	end
end

go

declare @z float
select @z = dbo.DajZaradu(2, 2008)
exec dbo.PrikaziZaraduPoClanuBenda 2, 2008, 6, @z

go

-- 6. zadatak
create procedure PrikaziZaradu
as
begin
	declare @zarada float
	declare @idFest int
	declare @godina int
	declare @idBend int
	declare kursorPoLineupovima cursor for select idFestivala, godina, idBenda from lineup_festivala

	open kursorPoLineupovima
		fetch next from kursorPoLineupovima into @idFest, @godina, @idBend
		while @@FETCH_STATUS = 0
		begin
			select @zarada = dbo.DajZaradu(@idFest, @godina)
			exec dbo.PrikaziZaraduPoClanuBenda @idFest, @godina, @idBend, @zarada

			fetch next from kursorPoLineupovima into @idFest, @godina, @idBend
		end
	close kursorPoLineupovima
	deallocate kursorPoLineupovima
end

go

exec PrikaziZaradu


/*
go 
drop procedure dbo.PrikaziZaradu
drop procedure dbo.PrikaziZaraduPoClanuBenda
drop function dbo.DajSastavBenda
drop function dbo.DajZaradu
drop function dbo.DajZaraduBendovaPoFestivalima
*/
