
use STUDIJE;
go

-- zadatak 1

select imes 'Ime studenta'
from Studenti
where Imes like '%a'
order by Upisan, datepart( year, Datr );



-- zadatak 2

select sm.Nazivs 'Naziv smera', count(*) 'Broj upisanih studenata'
from smer sm
	left join studenti st
		on sm.Ssmer = st.Ssmer
-- posto sm.Ssmer jedinstveno identifikuje svaki zapis sm.Nazivs nece uticati na grupisanje
group by sm.Ssmer, sm.Nazivs;




-- zadatak 3

select n.Imen 'Prezime nastavnika', p.NAZIVP 'Naziv predmeta'
from Nastavnici n
	left join Angazovanje a
		on n.Snast = a.Snast
	left join PREDMETI p
		on a.Spred = p.SPRED;


-- potrebno je prvo obrisati triger
-- insert into Prijave values( 24, 99, 2000, null, getdate(), 10 )
-- rez: 99	2000	Stevan                   	Racunarstvo III
-- delete from prijave where indeks	= 99 and upisan = 2000 and spred = 24

-- zadatak 4

select p.Indeks, p.Upisan, s.Imes, pr.NAZIVP
from Prijave p
	join Studenti s								-- zbog imena studenta
		on 
			p.Indeks = s.Indeks and
			p.Upisan = s.Upisan
	join PREDMETI pr							-- zbog naziva predmeta
		on p.Spred = pr.SPRED
where ocena > 5 and exists						-- polozen i nema polozen uslovni
(
	select *
	from USLOVNI u
	where								
		p.Spred = u.Spred and					-- postoji uslovni predmet
		not exists								-- uslovni nije polozen
		(
			select *
			from Prijave
			where 
				p.Indeks = Indeks and 
				p.Upisan = Upisan and
				u.UslPredmet = Spred and
				ocena > 5
		)
);
go


-- zadatak 5

-- izlaz:
-- Indeks	Upisan
-- 3		2002
-- 8		2003

create view Broj_Studenata_Po_Smerovima_View as
select sm.Ssmer 'Ssmer', count(s.Ssmer) 'Broj_studenata'
from Smer sm
	left join studenti s
		on sm.Ssmer = s.Ssmer
group by sm.Ssmer;
go

select p.Indeks, p.Upisan, avg( 1.0 * p.Ocena ) 'Prosek'
from Prijave p
	join Studenti s
		on p.Indeks = s.Indeks and p.Upisan = s.Upisan
where ocena > 5 and s.Ssmer in
(
	select t1.Ssmer
	from Broj_Studenata_Po_Smerovima_View t1
		left join Broj_Studenata_Po_Smerovima_View t2
			on t1.Broj_studenata < t2.Broj_studenata
	where t2.Ssmer is null
)
group by p.Indeks, p.Upisan
having avg( 1.0 * ocena ) > 8.0;


-- zadatak 6

select
	s.Indeks, 
	s.Upisan, 
	( ps.Semestar + 1 ) / 2 'Godina studija',
	count(*) 'Broj nepolozenih'
from Planst ps
	join Studenti s
		on s.Ssmer = ps.Ssmer
	left join Prijave p
		on 
			s.Indeks = p.Indeks and
			s.Upisan = p.Upisan and
			ps.Spred = p.Spred and
			p.Ocena > 5
where p.Ocena is null
group by ( ps.Semestar + 1 ) / 2, s.Indeks, s.Upisan;


-- zadatak 7

select
	indeks,
	upisan, 
	(
		case 
			when not exists						-- ako ne postoji prijava ispita na predmet iz 2. , 3. ili 4. godine
			(
				select *
				from Prijave p
					join Planst ps
						on p.Spred = ps.Spred
				where 
					p.Indeks = s.Indeks and
					p.Upisan = s.Upisan and
					ps.Semestar > 2
			)  then 'Prva'
			
			when not exists						-- ako ne postoji prijava ispita na predmet iz 3. ili 4. godine
			(
				select *
				from Prijave p
					join Planst ps
						on p.Spred = ps.Spred
				where 
					p.Indeks = s.Indeks and
					p.Upisan = s.Upisan and
					ps.Semestar > 4
			) then 'Druga'

			when 
				not exists						-- ako ne postoji prijava ispita na predmet iz 4. godine
				(
					select *
					from Prijave p
						join Planst ps
							on p.Spred = ps.Spred
					where 
						p.Indeks = s.Indeks and
						p.Upisan = s.Upisan and
						ps.Semestar > 6
				) 
				and not exists					-- ako ne postoji nepolozen ispit u 1. ili 2.
				(
					select *
					from Planst ps
						join Studenti s2
							on 
								s2.Indeks = s.Indeks and
								s2.Upisan = s.Upisan and
								ps.Ssmer = s2.Ssmer and
								ps.Semestar in (1,2,3,4)
						left join Prijave p
							on 
								s2.Indeks = p.Indeks and
								s2.Upisan = p.Upisan and
								ps.Spred = p.Spred and
								p.Ocena > 5
					where p.Indeks is null
				)  then 'Treca'

			when 
				exists							-- ako postoji prijava ispita na predmet iz 4. godine
				(
					select *
					from Prijave p
						join Planst ps
							on 
								p.Indeks = s.Indeks and
								p.Upisan = s.Upisan and
								p.Spred = ps.Spred and
								ps.Semestar in ( 7, 8 )
				)
				and not exists					-- ako ne postoji nepolozen ispit u 1. , 2. ili 3.  godine
				(
					select *
					from Planst ps
						join Studenti s2
							on 
								s2.Indeks = s.Indeks and
								s2.Upisan = s.Upisan and
								ps.Ssmer = s2.Ssmer and
								ps.Semestar in (1,2,3,4,5,6)
						left join Prijave p
							on 
								s2.Indeks = p.Indeks and
								s2.Upisan = p.Upisan and
								ps.Spred = p.Spred and
								p.Ocena > 5
					where p.Indeks is null
				) then 'Cetvrta'
			else 'Neregularno'
		end
	) 'Godina studija'
from Studenti s;
go




-- BONUS

create table "Studenti-DIPL"
(
	Indeks smallint not null,
	Upisan smallint not null,
	Imes char(25) null,
	Mesto char(30) null,
	Datr datetime null,
	Ssmer smallint foreign key references Smer(Ssmer),
	primary key( Indeks, Upisan )
);
go


insert into "Studenti-DIPL"
select s.* from DIPLOMIRANI d
	join Studenti s
		on
			d.Indeks = s.Indeks and
			d.Upisan = s.Upisan and
			d.Ssmer = s.Ssmer;
go

