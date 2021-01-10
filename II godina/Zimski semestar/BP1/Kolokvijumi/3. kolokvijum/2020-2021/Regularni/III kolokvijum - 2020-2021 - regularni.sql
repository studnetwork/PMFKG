use utakmice

-- 1. zadatak

create table Tabela
(
	id int primary key identity(1,1),
	id_sezone int foreign key references sezona(id),
	id_tima int foreign key references timovi(id),
	broj_bodova int
)


-- 2. zadatak

create trigger upisUTabelu on Tabela
instead of insert
as
begin

	declare @id_sezone int
	declare @id_tima int
	declare @broj_bodova int
	
	declare kursorKrozInserted cursor
	for select id_sezone, id_tima, broj_bodova from inserted 

	open kursorKrozInserted

	fetch next from kursorKrozInserted into  @id_sezone, @id_tima, @broj_bodova

	while @@FETCH_STATUS = 0
	begin

		print concat(@id_sezone, @id_tima, @broj_bodova)

		if exists (select * from Tabela where id_sezone = @id_sezone and id_tima = @id_tima)
		begin
			print 'update'
			update Tabela
				set broj_bodova = @broj_bodova
			where id_sezone = @id_sezone and id_tima = @id_tima
		end
		else
		begin
			print 'insert'
			insert into Tabela values (@id_sezone, @id_tima, @broj_bodova)
		end
		

		fetch next from kursorKrozInserted into  @id_sezone, @id_tima, @broj_bodova
	end

	close kursorKrozInserted
	deallocate kursorKrozInserted
end


go

-- 3. zadatak

create FUNCTION dajBodoveNaUtakmici
(
	@idUtakmice int, 
	@idTima int
)
RETURNS int
AS
BEGIN
	DECLARE @brGolovaTima int
	DECLARE @brGolovaProtivnickogTima int

	set @brGolovaTima = (	select count(*) 
							from golovi 
							where id_utakmice = @idUtakmice and id_tima = @idTima
						)
	set @brGolovaProtivnickogTima = (	
										select count(*) 
										from golovi 
										where id_utakmice = @idUtakmice and id_tima != @idTima
									)

	if @brGolovaTima > @brGolovaProtivnickogTima -- ako je @idTima pobedio
	begin
		RETURN 3
	end
	else if @brGolovaTima = @brGolovaProtivnickogTima --ako je nereseno
	begin
		RETURN 1
	end

	-- Ako je @idTima izgubio
	return 0
END
GO

-- Prmimer poziva
select dbo.dajBodoveNaUtakmici(1,2)


go


-- 4. zadatak

create FUNCTION dajBodoveTimaUSezoni
(
	@idSezone int, 
	@idTima int
)
RETURNS int
AS
BEGIN

	return (
				select sum(dbo.dajBodoveNaUtakmici(id, @idTima))
				from utakmice
				where id_sezone = @idSezone and (id_domacina = @idTima or id_gosta = @idTima)
			)

	
END
GO

select dbo.dajBodoveTimaUSezoni(1,1)

-- 5. zadatak
go
alter procedure popuniTabelu
as
begin

	insert into Tabela
	select s.id, t.id, dbo.dajBodoveTimaUSezoni(s.id, t.id)
	from timovi t, sezona s
	
end
go

exec popuniTabelu

go




