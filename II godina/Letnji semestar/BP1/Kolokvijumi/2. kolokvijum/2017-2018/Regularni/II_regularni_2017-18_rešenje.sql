-- Source: https://knezevicmarko.github.io/bp1/2017/215-kolokvijum_2017_2018.html

-- 1. Zadatak


select id_etape, sum(duzina_staze) 
from etape
group by id_etape 

-- 2. Zadatak


select ime
from vozaci
where id_vozaca in (
						select distinct id_vozaca
						from prolazna_vremena
						where DATEDIFF(MINUTE, vreme_starta, vreme_prolaska_kroz_cilj) < 60
					)

-- 3. Zadatak


create view vozaci_sa_stazama as
select *
from vozaci v, etape e

select ime
from vozaci_sa_stazama vss left join prolazna_vremena pv on
	vss.id_vozaca = pv.id_vozaca 
	and vss.id_etape = pv.id_etape 
	and vss.redni_broj_staze = pv.redni_broj_staze
where pv.id_etape is null

-- 4. zadatak


select ime
from vozaci
where id_vozaca in (
						select id_vozaca
						from prolazna_vremena
						where vreme_prolaska_kroz_cilj is null
						group by id_vozaca
						having count(*) > 1
					)

-- 5. zadatak


/*
	Za svako prolazno vreme odredi tip vozila i izracunaj prolazno vreme.
	Kolona vreme_prolaska_kroz_cilj je dodata zbog 7. zadatka.
*/
create view vremena as
select vozila.id_tipa, 
		pv.id_etape, 
		pv.redni_broj_staze,
		pv.id_vozaca,
		vozaci.ime,
		DATEDIFF(MILLISECOND, pv.vreme_starta,
			pv.vreme_prolaska_kroz_cilj) prolaznoVreme, pv.vreme_prolaska_kroz_cilj
from prolazna_vremena pv join vozaci on
	pv.id_vozaca = vozaci.id_vozaca join vozila
	on vozaci.id_vozila = vozila.id_vozila
where pv.vreme_prolaska_kroz_cilj is not null

/*
	Za svaku stazu pronadji pobednika, a zatim za svakog vozaca, po tipu, izracunaj koliko ima pobeda.
*/

create view Pobede as
select v1.ime, v1.id_tipa, count(*) brojPobeda
from vremena v1 left join vremena v2
	on v1.id_tipa = v2.id_tipa
		and v1.id_etape = v2.id_etape
		and v1.redni_broj_staze = v2.redni_broj_staze
		and v1.prolaznoVreme > v2.prolaznoVreme
where v2.id_etape is null
group by v1.id_tipa, v1.id_vozaca, v1.ime


/*
	U postavci zadatka stoji naznaceno da jedan vozac moze voziti jednu stazu => vozac je deo resenja ako ima
	pobeda koliko ima staza.
*/

select *
from Pobede
where brojPobeda = (select count(*) from etape)

-- 6. zadatak


/*
	Za svako prolazno vreme pronadji koliko ima boljih prolaznih vremena 
	za dati tip vozila, etapu i stazu
*/

create view plasmaniSesti as
select *, ( 
				select count(*) + 1
				from vremena v2
				where v1.id_tipa = v2.id_tipa
				and v1.id_etape = v2.id_etape
				and v1.redni_broj_staze = v2.redni_broj_staze
				and v1.prolaznoVreme > v2.prolaznoVreme
		  ) as Plasman
from vremena v1

select ime, id_tipa, id_etape, redni_broj_staze, id_vozaca, Plasman
from plasmaniSesti
order by id_tipa, id_etape, redni_broj_staze, Plasman

-- 7.


/* Vozaci koji NISU deo resenja
	Za svaki plasman pl1 nekog vozaca, pokusaj da nadjes njegov losiji plasman pl2 koji
	je ostvaren posle pl1
*/

create view NisuResenje as
select distinct id_vozaca
from plasmaniSesti pl1
where exists 
(
	select *
	from plasmaniSesti pl2
	where pl1.id_vozaca = pl2.id_vozaca 
	and pl1.vreme_prolaska_kroz_cilj < pl2.vreme_prolaska_kroz_cilj
	and pl1.Plasman < pl2.[Plasman]
)

/*
	Vozaci koji su deo resenja
*/
select *
from vozaci
where id_vozaca not in (select id_vozaca from NisuResenje)


-- 8. Zadatak


select ime, sum(
					case Plasman
					when 1 then 10
					when 2 then 7
					when 3 then 5
					when 4 then 3
					else 0
					end
				) as brojPoena
from plasmaniSesti
where id_tipa = (select id_tipa from tip_vozila where naziv = 'automobil')
group by id_vozaca, ime
