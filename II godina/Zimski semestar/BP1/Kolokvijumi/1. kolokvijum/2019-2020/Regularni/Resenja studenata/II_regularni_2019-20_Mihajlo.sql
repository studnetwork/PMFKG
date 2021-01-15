--Kolokvijum 2019/20 II Put

--1. Zadatak
select idOsobe,ime,count(*) as brojVozila
from vozila V join osobe O on V.idVlasnika = O.idOsobe
group by idOsobe,ime

--2. Zadatak
select count(*) as 'Broj jedinstvenih'
from vozila V1 left join vozila V2 on V1.godinaProizvodnje = V2.godinaProizvodnje and V1.idVozila != V2.idVozila
where V2.idVozila is NULL

--3. Zadatak
select idOglasa, max(p1.ponudjenaCena) as 'Najveca jedinstvena'
from ponude p1
where p1.ponudjenaCena not in(
									select p2.ponudjenaCena
									from ponude p2
									where p1.idOglasa = p2.idOglasa and p1.idPonude != p2.idPonude
							 )
group by p1.idOglasa

--4. Zadatak
alter view kupili_vozilo as
select p1.idOglasa, min(p1.datumPonude) as datum, max(p1.ponudjenaCena) as ponuda
from ponude p1
where p1.ponudjenaCena in (
								select max(ponudjenaCena)
								from ponude p2 join oglasi O on p2.idOglasa = O.idOglasa
								where p1.idOglasa = p2.idOglasa and p2.datumPonude between O.datumPostavljanja and O.datumZavrsetka
								group by p2.idOglasa
						   )
group by p1.idOglasa

create view prosecna_kubikaza as
select P.idPonudjaca, avg(V.kubikaza) as prosecna_kubikaza
from ponude P join kupili_vozilo K on P.idOglasa = K.idOglasa and P.datumPonude = K.datum and P.ponudjenaCena = K.ponuda
			  join oglasi O on P.idOglasa = O.idOglasa
			  join vozila V on O.idVozila = V.idVozila
group by P.idPonudjaca

select p1.idPonudjaca
from prosecna_kubikaza p1 left join prosecna_kubikaza p2 on p1.idPonudjaca != p2.idPonudjaca and p1.prosecna_kubikaza < p2.prosecna_kubikaza
where p2.idPonudjaca is NULL

--5. Zadatak
create view spojeni_kupci as
select P.*
from ponude P join kupili_vozilo K on P.idOglasa = K.idOglasa and P.datumPonude = K.datum and P.ponudjenaCena = K.ponuda
order by P.idPonudjaca

select S1.idPonudjaca
from spojeni_kupci S1 left join spojeni_kupci S2 on S1.idPonudjaca = S2.idPonudjaca
and S1.datumPonude < S2.datumPonude and S1.ponudjenaCena > S2.ponudjenaCena
group by S1.idPonudjaca 
having sum(S2.ponudjenaCena) is NULL
