-- ZADATAK 1
CREATE TABLE prodata_vozila 
(
	idVozila int not null,
	idKupca int not null,
	prodajnaCena int not null, 
	datumProdaje datetime not null
)

ALTER TABLE prodata_vozila
add constraint pk_ProdVozila primary key (idVozila, idKupca, datumProdaje)

-- ZADATAK 2
CREATE FUNCTION proveriVozilo 
(
	@idVozila int
)
RETURNS int
AS
BEGIN
	
	DECLARE @prodatoVozilo int
	SET @prodatoVozilo = 0
	
	SELECT @prodatoVozilo = COUNT(o.idOglasa)
	FROM oglasi o JOIN ponude p ON o.idOglasa = p.idOglasa 
	WHERE o.datumZavrsetka>p.datumPonude AND o.idVozila = @idVozila
	GROUP BY o.idVozila
	HAVING count(idVozila)>1

	RETURN @prodatoVozilo

END
GO

--ZADATAK 3
CREATE PROCEDURE proveriCenu  
	@idVozila int ,
	@idKupca int output, 
	@prodajnaCena int output,
	@datumProdaje datetime output
AS
BEGIN
	SELECT @idVozila = o.idVozila, @prodajnaCena = MAX(p.ponudjenaCena)
	FROM oglasi o JOIN ponude p ON o.idOglasa = p.idOglasa
	WHERE o.idVozila = @idVozila
	GROUP BY o.idVozila

	SELECT @datumProdaje = datumPonude, @idKupca = idPonudjaca
	FROM oglasi o JOIN ponude p ON o.idOglasa = p.idOglasa
	WHERE o.idVozila = @idVozila AND p.ponudjenaCena = @prodajnaCena
END
GO


declare @idKupca int 
declare @prodajnaCena int
declare @datumKupovine datetime
exec proveriCenu @idVozila = 1, @idKupca = @idKupca output, @prodajnaCena = @prodajnaCena output, @datumProdaje = @datumKupovine output


print(@idKupca)
print(@prodajnaCena)
print(@datumKupovine)

-- ZADATAK 4

CREATE TRIGGER proveraUnosa ON prodata_vozila 
instead of INSERT 
AS
BEGIN
	declare @cena int
	declare @datum datetime
	declare @idKupca int 
	declare @idVozila int 

	declare kursorVozilo cursor for 
	select * from inserted
	
	open kursorVozilo 
	fetch next from kursorVozilo 
	into @idVozila, @idKupca, @cena, @datum 

	while @@FETCH_STATUS = 0
	begin
		if exists (select *
					from prodata_vozila
					where idVozila = @idVozila)
		begin
			update prodata_vozila set prodajnaCena = @cena, datumProdaje = @datum, idKupca = @idKupca
			where idVozila = @idVozila
		end
		else 
		begin
			insert into prodata_vozila values (@idVozila,@idKupca,@cena,@datum)
		end 
		fetch next from kursorVozilo
	end
	deallocate kursorVozilo
END

INSERT into prodata_vozila VALUES (2,1,4700,'11-12-2020')
INSERT into prodata_vozila VALUES (1,2,5000,'11-12-2020')
INSERT into prodata_vozila VALUES (1,2,4700,'11-12-2020')

--ZADATAK 5
CREATE PROCEDURE proveriOglase
	@idVozila int 
AS
BEGIN
	declare @prodatoVozilo int
	SET @prodatoVozilo = dbo.proveriVozilo(1)
	--print(@prodatoVozilo)
	declare @idKupca int
	declare @cena int 
	declare @datum datetime 

	if(@prodatoVozilo>0)
	begin
		exec proveriCenu @idVozila = @idVozila, @idKupca = @idKupca output, @prodajnaCena = @cena output, @datumProdaje = @datum output
		INSERT into prodata_vozila VALUES (@idVozila, @idKupca, @cena, @datum)
		
		SELECT o.*, p.*
		FROM oglasi o INNER JOIN ponude p ON o.idOglasa = p.idOglasa
		WHERE o.idVozila = @idVozila  
	end 
END
GO

DELETE  from prodata_vozila where 1 = 1

exec proveriOglase @idVozila = 1

SELECT * from prodata_vozila