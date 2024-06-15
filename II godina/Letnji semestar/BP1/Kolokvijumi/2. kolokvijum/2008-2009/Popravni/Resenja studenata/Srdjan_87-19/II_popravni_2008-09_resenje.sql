
use STUDIJE;
go

-- zadatak 1

select * 
from studenti
where 
	upisan - datepart( year, datr ) = 18 and
	mesto like '%k%';



-- zadatak 2

select pr.NAZIVP, count(*) 'Broj studenata'
from Prijave p
	join PREDMETI pr
		on pr.SPRED = p.Spred
group by pr.SPRED, pr.NAZIVP;


-- zadatak 3

select 
	s.Nazivs 'Naziv smera',
	p.NAZIVP 'Naziv predmeta',
	(ps.Semestar+1)/2 'Godina studija'
from Planst ps
	join Smer s
		on ps.Ssmer = s.Ssmer
	join PREDMETI p
		on p.SPRED = ps.Spred;


-- zadatak 4

select Nazivs
from Smer sm
where not exists
(
	select *
	from Studenti s
	where 
		sm.Ssmer = s.Ssmer and
		s.mesto = 'Užice'
);


-- zadatak 5
select *
from Studenti s
where indeks in
(
	select Indeks
	from Prijave p1
	where s.Upisan = Upisan
	group by Indeks, Upisan
	having avg( 1.0 * ocena ) > all
	(
		select avg( 1.0 * ocena )
		from Prijave p2
		where ocena > 5 and p1.Upisan < Upisan
		group by indeks, Upisan
	)
);


-- zadatak 6
select
	t1.NAZIVP 'predmet', 
	t2.NAZIVP 'uslovnipredmet2'
from 
(
	select u.Spred, p.NAZIVP, u.UslPredmet
	from USLOVNI u
		join PREDMETI p
			on u.Spred = p.SPRED
) t1,
(
	select u.Spred, u.UslPredmet, p.NAZIVP
	from USLOVNI u
		join PREDMETI p
			on u.UslPredmet = p.SPRED
) t2
where t1.UslPredmet = t2.Spred;


-- Zadatak 7

select 
	Upisan,
	Imes, 
	case
		when not exists
		(
			select *
			from
				(
					select p.SPRED
					from PREDMETI p
						join Planst ps
							on 
								p.SPRED = ps.Spred and
								s.Ssmer = ps.Ssmer
				) svi_predmeti
				where not exists
				(
					select *
					from Prijave
					where 
						Indeks = s.Indeks and 
						Upisan = s.Upisan and
						svi_predmeti.SPRED = Spred and
						ocena > 5
				) 
				
		) then 'Polozio sve'
		else 'Nije polozio sve'
	end 'Polozio sve?'
from Studenti s;
go

-- BONUS

create view polozili_sve_View as
select *
from Studenti s
where not exists
(
	select *
	from Planst ps
	where 
		ps.Ssmer = s.Ssmer and
		not exists 
		(
			select *
			from Prijave p
			where 
				s.Indeks = p.Indeks and
				s.Upisan = p.Upisan and
				ps.Spred = p.Spred and
				p.Ocena > 5 

		)
);
go


create view datum_kada_su_svi_polozeni_View as
select ps.Indeks, ps.Upisan, max(datump) 'Datum poslednjeg polaganja'
from polozili_sve_View ps
	join Prijave p
		on 
			ps.Indeks = p.Indeks and
			ps.Upisan = p.Upisan
group by ps.Indeks, ps.Upisan;
go


create view prvi_u_generaciji_polozio_sve_View as
select *
from datum_kada_su_svi_polozeni_View t
where t.[Datum poslednjeg polaganja] <= all
(
	select [Datum poslednjeg polaganja]
	from datum_kada_su_svi_polozeni_View
	where t.Upisan = Upisan
);
go

select 
	s.Upisan 'Generacija',
	s.Imes 'Ime studenta',
	concat( s.indeks, '/', s.upisan ) 'Broj indeksa'
from Studenti s
where exists
(
	select *
	from prvi_u_generaciji_polozio_sve_View pug
	where
		s.Indeks = pug.Indeks and
		s.Upisan = pug.Upisan
);