-- 1 

create table arhiva_prolaznih_vremena
(
	id int identity(1,1),
	id_vozaca int,
	id_etape int,
	redni_broj_staze int,
	vreme_starta datetime,
	vreme_prolaska_kroz_cilj datetime,
	primary key (id),
	foreign key (id_vozaca) references vozaci(id_vozaca),
	foreign key (id_etape, redni_broj_staze) references etape(id_etape, redni_broj_staze),
) 


create trigger upis_u_prolazna_vremena on prolazna_vremena
instead of insert
as
begin

	declare @id_vozaca int
	declare @id_etape int
	declare @redni_broj_staze int
	declare @vreme_starta datetime
	declare @vreme_prolaska_kroz_cilj datetime

	-- Napravi kursor kroz vrednosti koje je potrebno upisati u tabelu
	declare kursorKrozProlazna_vremena cursor for
	select id_vozaca, id_etape, redni_broj_staze, vreme_starta, vreme_prolaska_kroz_cilj from inserted
	
	open kursorKrozProlazna_vremena -- Otovri kursor za citanje

	FETCH NEXT FROM kursorKrozProlazna_vremena INTO @id_vozaca, @id_etape, @redni_broj_staze, @vreme_starta, @vreme_prolaska_kroz_cilj

	-- za svaki red u tabeli "inserted"
	WHILE @@FETCH_STATUS = 0
	BEGIN
		
		-- Ako nove vrednosti koje treba upisati za vozaca, etapu i stazu VEC postoje u tabeli "prolazna vremena"
	 	if exists (select * from prolazna_vremena where id_vozaca = @id_vozaca and id_etape = @id_etape and redni_broj_staze = @redni_broj_staze)
		begin 
			
			-- stare vrednosti upisi u arhivu
			insert into arhiva_prolaznih_vremena 
			select * from prolazna_vremena where id_vozaca = @id_vozaca and id_etape = @id_etape and redni_broj_staze = @redni_broj_staze
			
			--stare vrednosti promeni novim vrednostima
			update prolazna_vremena set vreme_starta = @vreme_starta, vreme_prolaska_kroz_cilj = @vreme_prolaska_kroz_cilj 
			where  id_vozaca = @id_vozaca and id_etape = @id_etape and redni_broj_staze = @redni_broj_staze
		end
		else
		begin -- Ako nove vrednosti koje treba upisati za vozaca, etapu i stazu NE postoje u tabeli "prolazna vremena" samo ih upisi u tabelu
			insert into prolazna_vremena values (@id_vozaca, @id_etape, @redni_broj_staze, @vreme_starta, @vreme_prolaska_kroz_cilj)
		end
		
		FETCH NEXT FROM kursorKrozProlazna_vremena INTO @id_vozaca, @id_etape, @redni_broj_staze, @vreme_starta, @vreme_prolaska_kroz_cilj
	END

	CLOSE kursorKrozProlazna_vremena
	DEALLOCATE kursorKrozProlazna_vremena

end


-- 2.

create function Plasman (@id_vozaca int, @id_etape int, @redni_broj_staze int, @godina int)
returns int
as
begin
	declare @plasman int
	
	/*
		Pronadji tip vozila za prosledjenog vozaca
	*/
	
	declare @id_tipa int
	
	select @id_tipa = v2.id_tipa from vozaci v1 join vozila v2 on v1.id_vozila = v2.id_vozila
	where v1.id_vozaca = @id_vozaca 

	/*
		Pronadji ostvareno vreme za prosledjenog vozaca, etapu i stazu
	*/
	
	declare @ostvareno_vreme int

	select @ostvareno_vreme = datediff(MILLISECOND, vreme_starta, vreme_prolaska_kroz_cilj)
	from prolazna_vremena
	where id_etape = @id_etape and redni_broj_staze = @redni_broj_staze and id_vozaca = @id_vozaca

	/*
		Ideja je da pronadjemo koliko vozaca na prosledjenoj etapi sa id-em @id_etape i stazi sa rednim brojem @redni_broj_staze imaju bolje vreme od vozaca sa id-em @id_vozaca

	
		Ugnjezdeni upit TMP (videti seldeci upit) sadrzi sva prolazna vremena ostvarena u prosledjenoj godini @godina, za tip vozila koji je isti kao tip vozila prosledjenog vozaca (@id_tipa oredjenog iznad)
		na prosledjenoj etapi @etapa i na stazi @redni_broj_staze. Ako pogledamo where deo, vidimo da ce u rezultatu ostati oni vozaci koji su brzi od @ostvareno_vreme koje predstavlja
	    vreme za prosledjenog vozaca, zato je dovoljno prebrojati koliko takvih vozaca ima, sto predstavlja generalni plasman.
	*/
	select @plasman = count(*) + 1 from
	(
		/*
			-- Pronadji prolazna vremena za sva vozila koja su @id_tipa i ostavi samo ona prolazna vremena koja su
			-- ostvarena za prosledjeni @id_etape i na stazi @redni_broj_staze

			-- u rezultujucem upitu ostavljamo samo id_vozaca i ostavreno vreme jer smo u where delu filtrirali 
			-- rezultate samo za trazenu etapu i stazu
		*/

		select pv.id_vozaca, datediff(MILLISECOND, pv.vreme_starta, pv.vreme_prolaska_kroz_cilj) ostvareno_vreme
		from prolazna_vremena pv join vozaci v on pv.id_vozaca = v.id_vozaca -- prolazna vremena spajamo za vozacima jer se kod vozaca nalazi id_vozila pomocu kojeg mozemo vozaca spojiti sa njegovim vozilom
		join vozila on v.id_vozila = vozila.id_vozila -- kada vozaca spojimo sa njegovim vozilom, mozemo doci do tipa njegovog vozila, kako bi u where delu mogli da ostavimo samo ona vremena koja su ostvarila vozila sa tipom @id_tipa koji smo gore odredili 
		where datepart(year, pv.vreme_prolaska_kroz_cilj) = @godina and vozila.id_tipa = @id_tipa and pv.id_etape = @id_etape and redni_broj_staze = @redni_broj_staze 

	) as TMP
	where TMP.id_vozaca != @id_vozaca and @ostvareno_vreme > TMP.ostvareno_vreme

	return @plasman
end


-- 3.

/*
	Ukoliko je rekord oboren funkcija vraca 1, u suprotnom vraca -1
*/
create function DaLiJeOborenRekord (@id_vozaca int, @id_etape int, @redni_broj_staze int)
returns int
as
begin
	
	/*
		Prvo cemo pronaci kada je ostvareno vreme za prosledjenog vozaca, etapu, stazu i vreme kada je ostvareno
	*/
	declare @ostvareno_vreme int -- ostvareno vreme prosledjenog vozaca
	declare @kada_je_ostvareno_vreme datetime -- kog datum je ostvario prolazno vreme

	select @ostvareno_vreme = datediff(MILLISECOND, vreme_starta, vreme_prolaska_kroz_cilj), @kada_je_ostvareno_vreme = vreme_prolaska_kroz_cilj
	from prolazna_vremena
	where id_etape = @id_etape and redni_broj_staze = @redni_broj_staze and id_vozaca = @id_vozaca

	/*
		Pronadji tip vozila za prosledjenog vozaca
	*/
	
	declare @id_tipa int
	
	select @id_tipa = v2.id_tipa from vozaci v1 join vozila v2 on v1.id_vozila = v2.id_vozila
	where v1.id_vozaca = @id_vozaca 

	/*
		Ako je ostvareno vreme null, znaci da vozac nije zavrsio trku pa cemo vratiti -1
	*/
	if @ostvareno_vreme is null
	begin
		return -1
	end

	/*
		Provericemo koliko vozaca ima bolje vreme od @ostvareno_vreme sli da je ostvareno pre @kada_je_ostvareno_vreme
	*/

	declare @koliko_njih_je_bolje_u_proslosti int

	/*
		Spajamo prolazna vremena za vozacima a zatim sve sa vozilima, sa ciljem da za svako prolazno vreme dobijemo informaciju koji tip vozila je ostvario prolazno vreme.
		Ovo spajanje ima za cilj da u prolaznim vremenima ostavimo samo ona koja su ostvarila vozila sa tipom @id_tipa koji smo odredili iznad
	*/

	select @koliko_njih_je_bolje_u_proslosti = count(*)
	from prolazna_vremena pv join vozaci v on pv.id_vozaca = v.id_vozaca join vozila on v.id_vozila = vozila.id_vozila
	where vozila.id_tipa = @id_tipa and pv.id_etape = @id_etape and pv.redni_broj_staze = @redni_broj_staze and 
		  datediff(MILLISECOND, vreme_starta, vreme_prolaska_kroz_cilj) < @ostvareno_vreme and
		  pv.vreme_prolaska_kroz_cilj < @kada_je_ostvareno_vreme
	
	-- Ako nema boljih vremena vrati 1, u suprotnom vrati -1
	if @koliko_njih_je_bolje_u_proslosti = 0
	begin
		return 1
	end

	return -1

end


-- 4.

/*
	Procedura ce kursorom proci kroz sva prolazna vremena, i za svako prolazno vreme proveriti da li je ono najbolje u godini kada je ostvareno, kao i da li je njime oboren rekord
*/

create procedure ApsolutniPobednik
as
begin
	
	declare @id_vozaca int
	declare @id_etape int
	declare @redni_broj_staze int
	declare @vreme_starta datetime
	declare @vreme_prolaska_kroz_cilj datetime

	-- Napravi kursor kroz vrednosti koje je potrebno upisati u tabelu
	declare kursorKrozProlazna_vremena cursor for
	select id_vozaca, id_etape, redni_broj_staze, vreme_starta, vreme_prolaska_kroz_cilj from prolazna_vremena
	
	open kursorKrozProlazna_vremena -- Otovri kursor za citanje

	FETCH NEXT FROM kursorKrozProlazna_vremena INTO @id_vozaca, @id_etape, @redni_broj_staze, @vreme_starta, @vreme_prolaska_kroz_cilj

	-- za svaki red u tabeli prolazna_vremena proveri da li je ono vozacu dolelo prvo mesto u generalnom plasmanu i da li je to ujedno i rekord staze
	WHILE @@FETCH_STATUS = 0
	BEGIN

		-- Ako si prvi i ako si ostvario rekord
		if
		(
				dbo.Plasman(@id_vozaca, @id_etape, @redni_broj_staze, datepart(year, @vreme_prolaska_kroz_cilj)) = 1 
				and 
				dbo.DaLiJeOborenRekord(@id_vozaca, @id_etape, @redni_broj_staze) = 1
		)
		begin

			-- pronadji ime za @id_vozaca
			declare @ime varchar(50)
			select @ime = ime from vozaci where id_vozaca =  @id_vozaca

			print concat(@ime, ',', @id_etape, ',', @redni_broj_staze, ', ', datepart(year, @vreme_prolaska_kroz_cilj))
		end

		FETCH NEXT FROM kursorKrozProlazna_vremena INTO @id_vozaca, @id_etape, @redni_broj_staze, @vreme_starta, @vreme_prolaska_kroz_cilj
	END

	CLOSE kursorKrozProlazna_vremena
	DEALLOCATE kursorKrozProlazna_vremena

end

-- Poziv 

exec ApsolutniPobednik