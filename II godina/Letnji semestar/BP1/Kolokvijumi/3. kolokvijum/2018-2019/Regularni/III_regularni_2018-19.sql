
-- 1.


create table VecProdateKarte
(
	id int identity(1,1) primary key,
	idFestivala int not null,
	godina int not null,
	dan int not null,
	idPosetioca int not null,
	cena float,
	foreign key (idFestivala) references festivali(idFestivala),
	foreign key (idPosetioca) references posetioci(idPosetioca)
)



/*
	II nacin za strani kljuc

	alter table VecProdateKarte add foreign key (idFestivala) references festivali(idFestivala)
	alter table VecProdateKarte add foreign key (idPosetioca) references posetioci(idPosetioca)
		
*/

create trigger triger_karte on karte
instead of insert
as
begin

	-- Ako se vrednosti koje treba upisati vec nalaze u tabeli karte, upisi ih u tabelu VecProdateKarte
	insert into VecProdateKarte
	select * from inserted i
	where exists (
					select * from karte 
					where	i.godina = godina 
						and i.dan = dan 
						and i.idPosetioca = idPosetioca
						and i.idFestivala = idFestivala
				 )

	-- Ako se vrednosti koje treba upisati NE nalaze u tabeli karte, upisi ih u tabelu karte
	insert into karte
	select * from inserted i
	where NOT exists (
						select * from karte 
						where	i.godina = godina 
							and i.dan = dan 
							and i.idPosetioca = idPosetioca
							and i.idFestivala = idFestivala
					 )
end

-- 2.

create function dajSastavBenda (@idBenda int, @godina int)
returns table
as
return 
(
	select m.idMuzicara, m.ime, m.prezime
	from sastav_benda sb join muzicari m 
		on	sb.idBenda = @idBenda and 
			sb.idMuzicara = m.idMuzicara and
			datepart(year, sb.datum1) <= @godina and ( sb.datum2 is null or @godina <= datepart(year,sb.datum2))
)

-- Primer poziva
select * from dbo.dajSastavBenda(1, 1988)

-- 3.
create function dajzaradu(@idfestivala int,@godina int)
returns float
as begin 
	declare @zarada float
	declare @brojbendova int
	declare @pobendu float

	select @zarada=sum(cena * 1.0)
	from karte k
	where k.idFestivala=@idfestivala and k.godina=@godina

	select @brojbendova=count(*)
	from lineup_festivala l
	where l.idFestivala=@idfestivala and l.godina=@godina

	set @pobendu= @zarada/@brojbendova

	return (@pobendu)
end




-- 4.
create function dajZaraduBendovaPoFestivalima()
returns table
as
return
(
	select idFestivala, godina, idBenda, dbo.dajZaradu(idFestivala, godina) as 'zaradaBenda'
	from lineup_festivala
)
go

-- Primer poziva
select dbo.dajZaradu(1,2004)
-- Primer poziva
select * from dajZaraduBendovaPoFestivalima()


------------------------------------------------------------

Declare @sql NVARCHAR(MAX) = N'';

SELECT @sql = @sql + N' DROP FUNCTION ' 
                   + QUOTENAME(SCHEMA_NAME(schema_id)) 
                   + N'.' + QUOTENAME(name)
FROM sys.objects
WHERE type_desc LIKE '%FUNCTION%';

Exec sp_executesql @sql
GO

---------------------------------------------------------------


--5.
create procedure prikaziZaraduPoClanuBenda(@idFestivala int, @godina int, @idBenda int, @zarada float)
as
begin 
	declare @idMuzicara int
	declare @ime varchar(20)
	declare @prezime varchar(20)
	declare @brojClanova int
	declare @nazivBenda varchar(20)
	declare @nazivFestivala varchar(20)

	-- Uzmi broj clanova benda
	set @brojClanova = (select count(*) from dbo.dajSastavBenda(@idBenda, @godina))
	-- Uzmi naziv benda
	set @nazivBenda = (select naziv from bendovi where idBenda = @idBenda)
	--Uzmi naziv festivala
	set @nazivFestivala = (select naziv from festivali where idFestivala = @idFestivala)

	-- Izracunaj zaradu po clanu
	declare @zaradapoClanu float
	set @zaradapoClanu = @zarada / @brojClanova
	
	-- Ako broj clanova nije nula i ako je zarada po clanu veca od 1000
	if @brojClanova != 0 and @zaradapoClanu > 1000
	begin
		-- Prodji kursorom kroz sve clanove benda i ispisi njihovu zaradu
		declare sastav cursor for
		select * from dbo.dajSastavBenda(@idBenda, @godina)

		open sastav

		fetch next from sastav into @idMuzicara, @ime, @prezime

		while @@fetch_status = 0
		begin
			print concat('Godine ', @godina , '. na festivalu ', @nazivFestivala , ', ' , @ime, ' ', @prezime, ' svirao je u bendu ', @nazivBenda, ' i zaradio ', @zaradapoClanu, ' dinara')
			fetch next from sastav into @idMuzicara, @ime, @prezime
		end

		close sastav
		deallocate sastav
	end
end

-- Primer poziva
exec prikaziZaraduPoClanuBenda 1, 2004, 1, 15000

-- 6.

create procedure prikaziZaradu
as
begin 
	declare @zaradaPoBendu float
	declare @idFestivala int
	declare @idBenda int
	declare @zaradaBenda int
	declare @godina int

	-- Prodji kroz zarade po festivalima
	declare zarade cursor for
	select * from dbo.dajZaraduBendovaPoFestivalima()

	open zarade

	fetch next from zarade into @idFestivala, @godina, @idBenda, @zaradaBenda

	while @@fetch_status = 0 
	begin
		-- za svaku godinu odravanja festivala i njegovu ukupnu zaradu, pozovi proceduru koja ispisuje koliko je svaki clan benda, koji je tada svirao, zaradio
		exec prikaziZaraduPoClanuBenda @idFestivala, @godina, @idBenda, @zaradaBenda
		fetch next from zarade into @idFestivala, @godina, @idBenda,  @zaradaBenda
	end

	close zarade
	deallocate zarade
end

-- Primer poziva
exec prikaziZaradu



