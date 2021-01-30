/*
	Resenje redovnog kolokvijuma 2015-2016
*/


use socialNetwork


-- 1. zadatak

select max(p.datumObjave)
from Post p join tipPosta tp on p.idTipa = tp.idTipa and tp.tip = 'slika'

-- 2. zadatak

select k.ime , ( 
					select count(*)
					from Prijatelji p
					where k.id = p.idKorisnika1
				) as broj_prijatelja
from Korisnik k

-- 3. zadatak

-- Korelisani
select k.ime
from korisnik k
where exists ( select *
				from prijatelji p
				where p.idkorisnika1=k.id and datepart(month,p.datum)=datepart(month,getdate()) )

-- Bez korelisanog upita
 create view PrijateljstvaUTekucemMesecu as
 select k.ime,k.id
 from korisnik k
 where k.id in (select p.idkorisnika1
				from prijatelji p
				where datepart(month,p.datum)=datepart(month,getdate()))




-- 4. zadatak

/*
	Za svaku postovanu sliku nekog korisnika izracunaj koliko je dobio lajkova za nju.

*/

create view LajkoviPoSlici as
select p.idvlasnika, l.idposta,count(*) BrLajkova
from post p join tipposta tp on p.idtipa=tp.idtipa and tp.tip like 'slika' 
			join lajk l on l.idposta=p.id
group by p.idvlasnika, l.idposta


/*
	Za svakog korisnika izracunaj koliko ima ukupno lajkova i to podeli sa brojem slika, 
	a to je ekvivalentno trazenju srednje vrednosti broja lajkova za sve njegove slike.
*/

select idvlasnika,avg(brlajkova * 1.0) 'ProsekLajkova'
from LajkoviPoSlici
group by idvlasnika
having avg(brlajkova * 1.0) > 3




-- 5. zadatak

/*
	Svakog korisnika povezi sa prjateljima njegovih prijatelja.

	id_korisnika1, id_korisnika2_koji_je_prijatelj_sa_1, id_korisnika_koji_je_prijatelj_sa_2___1
	id_korisnika1, id_korisnika2_koji_je_prijatelj_sa_1, id_korisnika_koji_je_prijatelj_sa_2___2
	id_korisnika1, id_korisnika2_koji_je_prijatelj_sa_1, id_korisnika_koji_je_prijatelj_sa_2___3

	...

*/


create view SviDovedeni as
select p1.idkorisnika1 as 'id_korisnika1', p1.idKorisnika2 as 'id_korisnika2_koji_je_prijatelj_sa_1', p2.idkorisnika2 as 'id_korisnika_koji_je_prijatelj_sa_2___1'
from prijatelji p1 join prijatelji p2 on p1.idkorisnika2=p2.idkorisnika1 and p1.idkorisnika1<>p2.idkorisnika2

/*
	Prethodni upit svakog prijatelja 'id_korisnika2_koji_je_prijatelj_sa_1' povezuje sa 'id_korisnika1'. Dakle 'id_korisnika2_koji_je_prijatelj_sa_1' je
	posrednik u upoznavanju 'id_korisnika1' i svih njegovih prijatelja.
*/

/*
	NAPOMENA:

	U rezultatima ce se naci i:
	id_korisnika1, id_korisnika2_koji_je_prijatelj_sa_1, id_korisnika1
*/



/*
	Za svakog korisnika1 iz rezultata prethodno definisanog pogleda pronadji broj mogucih prijateljstva
	iskljucujuci one koji su mu vec prijatelji.

*/

select dp.id_korisnika1, count(*) as 'BrojMogucihPrijatelja'
from prijatelji p right join SviDovedeni dp on p.idkorisnika1=dp.id_korisnika1 and p.idkorisnika2=dp.id_korisnika2_koji_je_prijatelj_sa_1
where p.idkorisnika1 is null -- u rezultat ulaze samo oni koji nisu prijatelji
group by dp.id_korisnika1




-- 6. zadatak

/*
	Za svaka dva korisnika pronadji broj njegovih zajednickih prijatelja
*/

create view BrZajednickihPrijatelja as
select p1.idkorisnika1 as 'prvi', p2.idkorisnika1 as 'drugi', count(*) as 'BrZajednickih'
from prijatelji p1 join prijatelji p2 on p1.idkorisnika2=p2.idkorisnika2 and p1.idkorisnika1<>p2.idkorisnika1
group by p1.idkorisnika1,p2.idkorisnika1

/*
	Iz rezultata prethodno definisanog pogleda eliminisi one koji su vec prijatelji
*/

create view NisuPrijatelji as
select brz.prvi,brz.drugi,brz.BrZajednickih
from BrZajednickihPrijatelja brz left join prijatelji p on brz.prvi=p.idKorisnika1 and brz.drugi=p.idKorisnika2
where p.datum is null


/*
	Za svakog korisnika pronadji osobu sa kojom on ima najvise zajednickih prijatelja
*/

select n1.prvi,n1.drugi,n1.BrZajednickih
from nisuprijatelji n1 left join nisuprijatelji n2 on n1.drugi=n2.drugi and n1.prvi<>n2.prvi and n1.BrZajednickih<n2.BrZajednickih
where n2.prvi is null

 -- 7. zadatak

 create view ProsekPre30 as
 select idVlasnika, AVG(broj_lajkova * 1.0) as prosek
 from
 (select p.id, p.idVlasnika, COUNT(*) as broj_lajkova
 from post p join lajk l on p.id = l.idPosta
						 and DATEDIFF(DAY,p.datumobjave, GETDATE()) > 30
 group by p.id, p.idVlasnika) a
 group by idVlasnika


 create view ProsekPosle30 as
 select idVlasnika, AVG(broj_lajkova * 1.0) as prosek
 from
 (select p.id, p.idVlasnika, COUNT(*) as broj_lajkova
 from post p join lajk l on p.id = l.idPosta
						 and DATEDIFF(DAY,p.datumobjave, GETDATE()) <= 30
 group by p.id, p.idVlasnika) a
 group by idVlasnika



 select p1.idVlasnika, case 
					   when p1.prosek > p2.prosek then 'opada'
					   when p1.prosek < p2.prosek then 'raste'
					   else 'ista'
					   end as popularnost
 from ProsekPre30 p1 join ProsekPosle30 p2 on p1.idVlasnika = p2.idVlasnika
 order by p1.idVlasnika 