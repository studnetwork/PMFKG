use vozila

go

select * from tip_vozila
select * from marka_vozila
select * from modeli_vozila
select * from osobe
select * from vozila
select * from oglasi
select * from ponude

go

--  1. --
create table prodata_vozila
(
	idVozila int,
	idKupca int,
	prodajnaCena int,
	datumProdaje datetime,
	
	primary key (idVozila, idKupca, prodajnaCena, datumProdaje),
	foreign key (idVozila) references vozila (idVozila),
	foreign key (idKupca) references osobe (idOsobe)
)

--drop table prodata_vozila

select *
from prodata_vozila

go

--  2. --
create function Prodato
(
	@id int
)
returns int
as
begin
	declare @p int
	set @p = 0

	declare @pCena int
	declare @zDatum datetime
	declare @brPonuda int

	select @pCena = pocetnaCena, @zDatum = datumZavrsetka
	from oglasi
	where idVozila = @id

	if (@zDatum < getdate())
	begin
		select @brPonuda = count(*)
		from ponude
		where @pCena > ponudjenaCena
		
		if (@brPonuda > 0)
		begin
			set @p = 1
		end
	end

	return @p
end

go

select dbo.Prodato(1)

go

--  3. --
create procedure ProdajneInformacije
	@idVozila int,
	@idKupca int output,
	@prodajnaCena int output,
	@datumProdaje datetime output
as
begin
	declare @oglID int
	declare @oglDatZ datetime
	declare @cenaMAX int
	set @oglID = (select idOglasa from oglasi where idVozila = @idVozila)
	set @oglDatZ = (select datumZavrsetka from oglasi where @oglID = idOglasa)
	set @cenaMAX = (select max(ponudjenaCena) from ponude where idOglasa = @oglID)

	--if(dbo.Prodato(@idVozila) = 1)
	--begin
	declare @datMIN datetime
	set @datMIN = (select min(datumPonude)
					from ponude
					where idOglasa = @oglID and ponudjenaCena = @cenaMAX)
		
	set @datumProdaje = @oglDatZ

	select @idKupca = idPonudjaca, @prodajnaCena = ponudjenaCena
	from ponude
	where idOglasa = @oglID and ponudjenaCena = @cenaMAX and datumPonude = @datMIN
	--end
end

go

declare @idKup int
declare @cena int
declare @dat datetime

exec dbo.ProdajneInformacije 
		8, 
		@idKupca = @idKup output, 
		@prodajnaCena = @cena output, 
		@datumProdaje = @dat output

print(concat(@idKup, ' ', @cena, ' ', @dat))

go

--  4. --
create trigger NaUnosVozila on prodata_vozila
instead of insert
as
begin
	-- kursor
	declare @idVozila int
	declare @idKupca int
	declare @prodajnaCena int
	declare @datumProdaje datetime

	declare kursorPoInserdet cursor for select * from inserted
	open kursorPoInserdet
		fetch next from kursorPoInserdet into @idVozila, @idKupca, @prodajnaCena, @datumProdaje
		while @@FETCH_STATUS = 0
		begin
			if exists (select * from prodata_vozila where idVozila = @idVozila)
			begin
				update prodata_vozila set idKupca = @idKupca,
										  prodajnaCena = @prodajnaCena,
										  datumProdaje = @datumProdaje
				where idVozila = @idVozila
			end
			else
			begin
				insert into prodata_vozila values (@idVozila, @idKupca, @prodajnaCena, @datumProdaje)
			end

			fetch next from kursorPoInserdet into @idVozila, @idKupca, @prodajnaCena, @datumProdaje
		end
	close kursorPoInserdet
	deallocate kursorPoInserdet
end

insert into prodata_vozila values (1, 1, 1000, '2019-01-01')
								, (2, 1, 1500, '2019-01-01')
								, (2, 2, 3000, '2020-01-01')
								, (1, 3, 2000, '2019-01-01')
select * from prodata_vozila
delete from prodata_vozila

go

--  5. --
create procedure Provera
as
begin
	declare @idOglasa int
	declare @idVozila int
	declare @idKup int
	declare @cena int
	declare @datum datetime

	declare kursorPoOglasima cursor for select idVozila, idOglasa from oglasi
	open kursorPoOglasima
		fetch next from kursorPoOglasima into @idVozila, @idOglasa
		while @@FETCH_STATUS = 0
		begin
			if(dbo.Prodato(@idVozila) = 1)
			begin
				exec dbo.ProdajneInformacije 
						@idVozila, 
						@idKupca = @idKup output, 
						@prodajnaCena = @cena output, 
						@datumProdaje = @datum output
				insert into prodata_vozila values (@idVozila, @idKup, @cena, @datum)
				delete from ponude where idOglasa = @idOglasa
				delete from oglasi where idOglasa = @idOglasa
			end

			fetch next from kursorPoOglasima into @idVozila, @idOglasa
		end
	close kursorPoOglasima
	deallocate kursorPoOglasima
end

exec Provera
select * from prodata_vozila
select * from oglasi
select * from ponude
