/*
1
*/

create table prodata_vozila
(
	idVozila int not null,
	idKupca int not null,
	prodajnaCena int not null,
	datumProdaje datetime not null,
	primary key (idVozila, idKupca, prodajnaCena, datumProdaje)

)


/*
2
*/
go
create function funkcija_2 (@idVozila int)
returns int
as
begin

	declare @prodato int
	set @prodato = 0

	if exists (select * 
				from oglasi o join ponude p on o.idOglasa = p.idOglasa
				where idVozila = @idVozila and datumZavrsetka <= GETDATE()
				and p.ponudjenaCena >= o.pocetnaCena)
	begin
		set @prodato = 1
	end
	
	return @prodato
end

select dbo.funkcija_2 (16)

insert into oglasi values (16, '2019-11-11', '2019-12-12', 2000)
insert into ponude values (16,getdate(), 2200, 5)


/*
3

*/

CREATE PROCEDURE procedura_3 
	@idVozila int, @idKupca int output, @prodajnaCena int output, @datumProdaje datetime output
AS
BEGIN
	select @idKupca = p1.idPonudjaca, @prodajnaCena = p1.ponudjenaCena, @datumProdaje = p1.datumPonude 
	from ponude p1 join oglasi o on p1.idOglasa = o.idOglasa 
	left join ponude p2 on p1.idOglasa = p2.idOglasa and 
		(p1.ponudjenaCena < p2.ponudjenaCena or (p1.ponudjenaCena = p2.ponudjenaCena and p1.datumPonude > p2.datumPonude))
	where  p2.idOglasa is null and o.idVozila = @idVozila
	
END
GO


/*
4

*/


CREATE TRIGGER triger_4 ON prodata_vozila
instead of INSERT
AS 
BEGIN
	
	declare @idVozila int 
	declare @idKupca int 
	declare @prodajnaCena int 
	declare @datumProdaje datetime

	declare kursor cursor for
	select *
	from inserted

	open kursor

	fetch next from kursor into @idVozila, @idKupca, @prodajnaCena, @datumProdaje

	while @@FETCH_STATUS = 0
	begin

		if exists (select * from prodata_vozila where idVozila = @idVozila)
		begin 
			update prodata_vozila
			set idKupca = @idKupca, prodajnaCena = @prodajnaCena, datumProdaje = @datumProdaje
			where idVozila = @idVozila
		end
		else
		begin
			insert into prodata_vozila values (@idVozila, @idKupca, @prodajnaCena, @datumProdaje)
		end

		fetch next from kursor into @idVozila, @idKupca, @prodajnaCena, @datumProdaje

	end

	close kursor
	deallocate kursor 
	
END
GO

insert into prodata_vozila values (16,6, 2300,getdate())

select * from prodata_vozila


/*
5
*/


alter PROCEDURE procedura_5 
AS
BEGIN
	declare @idVozila int
	declare @idOglasa int

	declare kursor1 cursor for
	select idVOzila, idOglasa
	from oglasi

	open kursor1

	fetch next from kursor1 into @idVozila, @idOglasa

	while @@FETCH_STATUS = 0
	begin

		if(dbo.funkcija_2(@idVozila) = 1)
		begin
			declare @idKupca int 
			declare @prodajnaCena int 
			declare @datumProdaje datetime

			exec procedura_3 @idVozila, @idKupca output, @prodajnaCena output, @datumProdaje output
			select @idKupca, @prodajnaCena, @datumProdaje

			insert into prodata_vozila values (@idVozila, @idKupca, @prodajnaCena, @datumProdaje)
			delete from ponude where idOglasa = @idOglasa
			delete from oglasi where idOglasa = @idOglasa
		end

		fetch next from kursor1 into @idVozila,@idOglasa
	end

	close kursor1
	deallocate kursor1

END


update oglasi set datumZavrsetka = getdate() 

exec procedura_5

select * from prodata_vozila