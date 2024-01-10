-- Informacioni sistemi 1 - 2023/24 --
-- Vezbe - 9. termin --

--

-- Primer 1
select Customers.ContactName
from Customers
where Customers.CompanyName like "*Alfred*";

-- Primer 2
select Employees.FirstName, Employees.LastName, Employees.BirthDate
from Employees
where Employees.BirthDate between #5/6/1933# and #6/26/1960#;

-- Primer 3
select Employees.FirstName & " " & Employees.LastName as Ime
from Employees
where Employees.BirthDate between #5/6/1933# and #6/26/1960#;

-- Primer 4
select top 10 *
from Products
order by Products.UnitPrice desc;

--

-- Zadatak 3

-- Banke iz Srbije. Sortirane po naizvu
select banka.naziv, banka.sedište, banka.brzaposlenih
from banka
where banka.sedište = "SRBIJA"
order by banka.naziv;

-- Klijenti. Kreditno sposobni
select klijent.klijent_id, klijent.ime, klijent.adresa, klijent.kreditnosposoban
from klijent
where klijent.kreditnosposoban = True
order by klijent.adresa;

-- Klijenti. Ime na "M". Sortirani po imenu
select klijent.ime, klijent.adresa
from klijent
where klijent.ime like "M*"
order by klijent.ime;

-- Klijenti. Kreditno sposobni. Iz Beograda
select klijent.klijent_id, klijent.ime, klijent.adresa, klijent.kreditnosposoban
from klijent
where klijent.kreditnosposoban = True and klijent.adresa = "BEOGRAD"
order by klijent.adresa;

--

-- Zadatak 4

-- Klijenti Postanske stedionice
select banka.naziv, klijent.ime, klijent.adresa, klijent.kreditnosposoban
from klijent
inner join banka on klijent.banka_id = banka.banka_id
where banka.naziv = "POŠTANSKA ŠTEDIONICA";

-- Krediti. Placeno vise od 12 rata. Sortirani po iznosu opadajuce
select *
from krediti
where krediti.placeno_rata > 12;

-- Krediti u postanskoj stedionici manji od 50k. Ispisati i podatke o klijentu i banci
select banka.naziv, klijent.ime, krediti.iznos, krediti.placeno_rata
from (krediti 
inner join klijent on klijent.klijent_id = krediti.klijent_id)
inner join banka on banka.banka_id = klijent.banka_id
where (banka.naziv = "POŠTANSKA ŠTEDIONICA" or banka.naziv = "ERSTE") and krediti.iznos < 50000
order by klijent.ime;