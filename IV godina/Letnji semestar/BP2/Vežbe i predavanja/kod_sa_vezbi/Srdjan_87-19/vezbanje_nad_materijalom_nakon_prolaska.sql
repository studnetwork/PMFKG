use indeksi;

alter table person
add constraint pk_businessEntityId
primary key (businessEntityId);
-- alter table person drop constraint pk_businessEntityId 


create nonclustered index idx_ncl_businessEntityId
on person(businessEntityId);
-- drop index person.idx_ncl_businessEntityId

create nonclustered index idx_ncl_first
on person(firstname);
-- drop index person.idx_ncl_first

create nonclustered index idx_ncl_first_include_lastname
on person(firstname) include(lastname);
-- drop index person.idx_ncl_first_include_lastname

-- ---------------------------------------------------------------

exec sp_helpindex person;
exec sp_spaceused person;

-- ---------------------------------------------------------------

select * from person

select * from person
where firstname like 'Diane';

select lastname
from person
where firstname like 'Diane';

-- ---------------------------------------------------------------

select * from person
where firstname like 'Richard';

-- # bez indeksa [najbolja opcija; naravno, za ovaj slucaj.U  realnosti to bi zavisilo od ostalih upita]
-- cost: .173
-- opis: heap je u pitanju pa se radi radi table scan

-- # cl(bizEntId)
-- cost: .173
-- data|is: 1600|16
-- opis: radi se scan;
-- u where se koristi firstname, a ne bizEntId pa onda nema ubrzanja

-- # ncl(firstname)
-- cost: .173
-- data|is: 1600|616
-- opis: u select-u se zahtevaju sve informacije, a to bi zahtevalo pristup
-- skladistu sto nije isplativo pa se koristi table scan

-- # cl(bizEntId) + ncl(firstname)
-- cost: .173
-- data|is: 1600|544
-- opis: ovaj upit ne ubrzava jer se vrednost 'Richard' pojavljuje dosta puta
-- pa execution engine procenjuje da je isplativije koristiti Table Scan

-- ---------------------------------------------------------------

select BusinessEntityID
from Person
where BusinessEntityID=1000;

-- # bez indeksa
-- cost: .173
-- opis: heap je u pitanju pa se radi radi table scan

-- # cl(BusinessEntityID) [najbolja opcija]
-- cost: .0033
-- data|is: 1600|16
-- opis: na osnovu BusinessEntityID (koji je search key indeksa) se lako dolazi do 
-- zapisa koji ima vrednost za taj atribut jednaku 1000. 

-- # ncl(BusinessEntityID)
-- cost: .0033
-- data|is: 1600|384
-- opis: BusinessEntityID se nalazi unutar indeksa jer je nad tom atributu
-- definisan sam indeks. Stoga, nije potrebno pristupati skladistu. Ono sto je
-- mana ovog pristupa je to sto zauzima mnogo vise memorije nego sto je neophodno, a
-- i posto je rec o koloni koja identifikuje zapis onda je bolja opcija da se nad
-- njim definise klasterovani indeks (sto resava i problem sa memorijom)

-- # cl(BusinessEntityID) + ncl(BusinessEntityID)
-- opis: ignorise postojanje ncl i koristi samo cl(BusinessEntityID)

-- ---------------------------------------------------------------

select BusinessEntityID
from Person
where BusinessEntityID<100;

-- # bez indeksa
-- cost: .173
-- opis: heap je u pitanju pa se radi radi table scan

-- # cl(BusinessEntityID) [najbolja opcija]
-- cost: .0033
-- data|is: 1600|16
-- opis: na osnovu BusinessEntityID (koji je search key indeksa) se lako dolazi do 
-- opsega zapisa koji zadovoljavaju zahtev

-- # ncl(BusinessEntityID)
-- cost: .0033
-- data|is: 1600|384
-- opis: posto se sve sto je neophodno nalazi u indeksu onda dolazi do ubrzanja, ali
-- imamo problem koji je inace prisutan kod klasterovanih indeksa. To je uvecanje 
-- velicine indeksa. Rec je o koloni koja identifikuje zapis onda je bolja opcija da 
-- se nad njim definise klasterovani indeks (sto resava i problem sa memorijom)

-- # cl(BusinessEntityID) + ncl(BusinessEntityID)
-- data|is: 1600|384
-- opis: ignorise cl i bira ncl(BusinessEntityID); pretpostavljam zato sto
-- cl ucitava celu stranicu iz lista dok ncl radi samo sa podacima koji su
-- podskup svih atributa definisanih nad tabelom (u ovom slucaju BusinessEntityID je
-- jedini atribut koji se nalazi u indeksu). Rec je o koloni koja identifikuje zapis 
-- onda je bolja opcija da se nad njim definise klasterovani indeks 
-- (sto resava i problem sa memorijom)

-- ---------------------------------------------------------------

select firstname, count(*)
from person
group by firstname;

-- # bez indeksa
-- cost: .372
-- opis: heap je u pitanju pa se radi radi table scan

-- # cl(BusinessEntityID)
-- cost: .372
-- data|is: 1600|16
-- opis: nema poboljsanja jer je indeks definisan nad BusinessEntityID, a u upitu 
-- figurise firstname. Bice samo uradjen Scan

-- # ncl(firstname)
-- cost: .092
-- data|is: 1600|616
-- opis: dolazi do poboljsanja jer se u potpunosti koriste podaci iz indeksa;
-- count(*) prebrojava na osnovu pointera u indeksu (proveriti) pa time nema
-- potrebe da se pristupa memoriji

-- # cl(BusinessEntityID) + ncl(firstname) [najbolja opcija]
-- cost: .0844
-- data|is: 1600|544
-- opis: iz nekog razloga je Index Scan brzi za 0.0074 kada su oba indeksa prisutna
-- iako obavljaju iste operacije (SELECT <- Computer Scalar <- Stream Agregate <- Index Scan).
-- -- pretpostavka: index size je manji jer RID vise zauzima od kljuca pretrage klasterovanog indeksa
-- -- pa time sve radi brze jer se manje podataka prenosi

-- ---------------------------------------------------------------

select * from person
order by firstname;

-- # bez indeksa [najbolja opcija]
-- cost: 1.494
-- data|is: 1600|8 (uvek 8 kada indeksi nisu definisani)
-- opis: heap je u pitanju pa se zbog toga prvo radi Table Scan, a onda takon toga sortira
-- cela tabela; sort je dosta spor (88% vremena izvrsenja)

-- # cl(BusinessEntityID)
-- cost: 1.494
-- data|is: 1600|16
-- opis: nema poboljsanja jer je indeks definisan nad BusinessEntityID, a u upitu 
-- figurise firstname. Bice samo uradjen Scan

-- # ncl(firstname)
-- cost: 1.494
-- data|is: 1600|616
-- opis: nema poboljsanja jer je se zahtevaju svi podaci, a u indeksu se nalazi samo firstname
-- pa je neophodno pristupati skladisu. Posto bi imalo dosta pristupa onda se koristi Table Scan

-- # cl(BusinessEntityID) + ncl(firstname)
-- cost: 1.494
-- data|is: 1600|544
-- opis: nema poboljsanja izvrsenja jer je se zahtevaju svi podaci, a u indeksu se nalazi samo 
-- firstname pa je neophodno pristupati skladisu. Posto bi imalo dosta pristupa onda se koristi Table Scan.
-- Ali, iako nije doslo do ubrzanja ipak dolazi do stednje memorije

-- ---------------------------------------------------------------

select firstname from person
order by firstname;

-- # bez indeksa 
-- cost: 1.494
-- data|is: 1600|8 (uvek 8 kada indeksi nisu definisani)
-- opis: heap je u pitanju pa se zbog toga prvo radi Table Scan, a onda takon toga sortira
-- cela tabela; sort je dosta spor (88% vremena izvrsenja)

-- # cl(BusinessEntityID) 
-- cost: 1.494
-- data|is: 1600|16
-- opis: nema poboljsanja jer je indeks definisan nad BusinessEntityID, a u upitu 
-- figurise firstname. Bice samo uradjen Scan

-- # ncl(firstname)
-- cost: .0793
-- data|is: 1600|616
-- opis: dolazi do poboljsanja jer su pointeri u indeksu uredjeni po tom atributu i takodje
-- sadrze njegove vrednosti pa ne mora da se pristupa skladistu

-- # cl(BusinessEntityID) + ncl(firstname) [najbolja opcija]
-- cost: .0719
-- data|is: 1600|544
-- opis: dolazi do poboljsanja jer su pointeri u indeksu uredjeni po tom atributu i takodje
-- sadrze njegove vrednosti pa ne mora da se pristupa skladistu. Iz nekog razloga je ova opcija
-- brza od ncl(firstname)
-- -- pretpostavka: index size je manji jer RID vise zauzima od kljuca pretrage klasterovanog indeksa
-- -- pa time sve radi brze jer se manje podataka prenosi

-- ---------------------------------------------------------------

select businessEntityID, firstname, lastname
from person
order by firstname;

-- # bez indeksa 
-- cost: 1.494
-- data|is: 1600|8 (uvek 8 kada indeksi nisu definisani)
-- opis: heap je u pitanju pa se zbog toga prvo radi Table Scan, a onda takon toga sortira
-- cela tabela; sort je dosta spor (88% vremena izvrsenja)

-- # cl(BusinessEntityID) 
-- cost: 1.494
-- data|is: 1600|16
-- opis: nema poboljsanja jer je indeks definisan nad BusinessEntityID, a u potrebno nam je
-- da tabela bude sortirana po atributu firstname (ona je sortirana fizicki po BusinessEntityID)

-- # ncl(firstname) 
-- cost: 1.494
-- data|is: 1600|616
-- opis: nema poboljsanja jer je se zahtevaju i vrednosti koje se ne nalaze u kljucu (businessEntityID i
-- lastname), a broj zapisa za koje bi to bilo potrebno je mnogo velik (svi zapisi iz tabele)

-- # cl(BusinessEntityID) + ncl(firstname) 
-- cost: 1.494
-- data|is: 1600|544
-- opis: nema poboljsanja (brzine) jer je se vrednosti atributa lastname ne nalaze u indeksu pa bi bilo
-- potrebno pristupiti skladistu da bi se ti podaci dobavili, a posto je to potrebno uraditi za veliki
-- broj zapisa onda se bira Table Scan kao optimalnija opcija

-- # cl(BusinessEntityID) + ncl(firstname) include (lastname) [najbolja opcija]
-- cost: .0964
-- data|is: 1600|808
-- opis: dolazi do poboljsanja jer se u neklasterovanom indeksu nalaze svi potrebni podaci. Firstname
-- je deo njega jer je nad njim definisan, BusinessEntityID je takodje u neklasterovanom indeksu jer
-- postoji klasterovani indeks definisan nad tim atributom, a atribut lastname je naknadno dodat indeksu
-- kao podatak koji nije deo kljuca pretrage. Posto se sve nalazi u indeksu onda nema pristupa skladistu
-- i time dolazi do ubrzanja

-- # ncl(firstname) include (lastname) 
-- cost: 1.494
-- data|is: 1600|880
-- opis: ne dolazi do poboljsanja jer indeks ne sadrzi atribut BusinessEntityID, vec RID posto klasterovani
-- indeks cl(BusinessEntityID) nije definisan. Bilo bi potrebno da se pristupa skladistu, a posto je to
-- potrebno raditi za veliki broj zapisa onda se bira Table Scan kao optimalnija varijanta

-- # ncl(firstname) include (lastname) 
-- cost: 1.494
-- data|is: 1600|880
-- opis: ne dolazi do poboljsanja jer indeks ne sadrzi atribut BusinessEntityID, vec RID posto klasterovani
-- indeks cl(BusinessEntityID) nije definisan. Bilo bi potrebno da se pristupa skladistu, a posto je to
-- potrebno raditi za veliki broj zapisa onda se bira Table Scan kao optimalnija varijanta

-- ---------------------------------------------------------------

select businessEntityID, firstname, lastname
from person
order by firstname, lastname;

-- # bez indeksa 
-- cost: 1.494
-- data|is: 1600|8 (uvek 8 kada indeksi nisu definisani)
-- opis: heap je u pitanju pa se zbog toga prvo radi Table Scan, a onda takon toga sortira
-- cela tabela; sort je dosta spor (88% vremena izvrsenja)

-- # ncl(firstname, lastname) 
-- cost: 1.494
-- data|is: 1600|880
-- opis: ne dolazi do poboljsanja jer indeks ne sadrzi atribut BusinessEntityID, vec RID posto klasterovani
-- indeks cl(BusinessEntityID) nije definisan. Bilo bi potrebno da se pristupa skladistu, a posto je to
-- potrebno raditi za veliki broj zapisa onda se bira Table Scan kao optimalnija varijanta

-- # ncl(firstname, lastname) include (businessEntityID)
-- cost: .1111
-- data|is: 1664|1832
-- opis: dolazi do ubrzanja izvrsenja jer se svi potrebni podaci nalaze u indeksu: firstname i lastname su
-- deo kljuca pretrage, a businessEntityID je naknadno dodat. Ovo resenje nije idealno jer je velicina
-- indeksa dosta uvecana, a i businessEntityID je kandidat za kljuc (tj. u ovom slucaju je i projektovano
-- tako da on predstalja PK) pa je bolja opcija definisanje klasterovanog kljuca nad tim atributom, a ne
-- njegovo dodavanje u neklasterovani

-- # cl(businessEntityID) + ncl(firstname, lastname) [najbolja opcija]
-- cost: .0964
-- data|is: 1600|808
-- opis: dolazi do ubrzanja izvrsenja jer se svi potrebni podaci nalaze u indeksu: firstname i lastname su
-- deo kljuca pretrage, a businessEntityID je takodje deo neklasterovanog kljuca, ali kao pointer (umesto RID-a)
-- posto je klasterovan kljuc nad tabelom definisan. Ova opcija znacajno smanjuje velicinu indeksa (u odnosu
-- na opciju ncl(firstname, lastname) include (businessEntityID)) jer se ne cuvaju duge adrese RID-a. Ovo
-- utice i na ubrzanje jer se manje podataka prenosi

-- # cl(firstname, lastname, businessEntityID)
-- cost: .1786
-- data|is: 1664|32
-- opis: dolazi do ubrzanja izvrsenja jer su svi podaci sortirani na odgovarajuci nacin. Ono sto je mana
-- ovog pristupa je to sto podaci nisu sortirani po businessEntityID-u koji predstavlja PK. Naravno, to
-- samo po sebi nije nuzno mana ukoliko veoma cesce radimo sa firstname i lastname, tada je mozda u redu
-- da podaci ne budu sortirani po PK.

