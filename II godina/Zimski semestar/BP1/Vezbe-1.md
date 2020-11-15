# Vežbe
<details>
  <summary><b>NAPOMENA</b></summary>
  Zadaci sa ekstenzijama se ne odnose na realnu situaciju. Posmatra se samo data tabela, nije bitno da li ključ neće biti zadovoljen u drugim slučajevima kada se dodaje novi red i slično. Bitno je samo proveriti da li važe uslovi za <b>datu</b> tabelu. 
</details>

## Ime fajla: Baze podataka 1 - Vežbe 1

### Zadatak 1
Data je relacija **DNEVNIK(ucenik,predmet,ocena,datum)** sa sledećom ekstenzijom:

![BP1-vezbe-slide1-z1](https://user-images.githubusercontent.com/65137355/99150597-9427be00-264a-11eb-8b58-bae1a9664817.png)

Ako imaš u vidu isključivo datu ekstenziju ispitaj osobine jedinstvenosti i neredudantnosti na datim kolekcijama i navedi da li neka od kolekcija posedujeosobine ključa ili nadključa. Svaki odgovor obrazložiti!

<details>
  <summary><b>a) (ucenik, predmet)</b></summary>
  <b>Rešenje:</b> Nadključ
  
  <b>Objšnjenje:</b> Atribut "Ucenik" je suvišan, tj. možemo jedinstveno odrediti bilo koji red samo sa atributom "Predmet" 
</details>

<details>
 <summary><b>b) (ocena, datum)</b></summary>
 <b>Rešenje:</b> Nadključ 
  
 <b>Objašnjenje:</b> Nema osobinu <i>neredudantnosti</i>. Moguće je jedinstveno odrediti svaki red samo pomoću atributa "Ocena".  
 Atribut "Datum" je suvišan u ključu.
</details>

***
### Zadatak 2

Data je relacija sledećom ekstenzijom:

![BP1-vezbe-slide1-z2](https://user-images.githubusercontent.com/65137355/99151651-8fb2d380-2651-11eb-85af-e8da86c924b0.png)

Navedene kolekcije atributa imaju osobine ključa, nadključa ili ni jedno ni drugo?Dati obrazloženje odgovora!!!
<details>
  <summary><b>a) (zadatak, broj_dana)</b></summary>
 <b>Rešenje:</b> Nadključ
  
 <b>Objašnjenje:</b> Nema osobinu <i>neredudantnosti</i>. Atribut "Zadatak" je suvišan. Moguće je jedinstveno odrediti odgovarajući red na osnovu vrednosti broja dana. Npr. ako je Broj_dana 25 mi možemo biti sigurni da je reč o 4. redu jer samo taj red ima vrednost atributa "Broj_dana" jednaku broju 25.
</details>

<details>
  <summary><b>b) (projekat, zadatak)</b></summary>
  <b>Rešenje:</b> Nije ni ključ ni nadključ
  
  <b>Objašnjenje:</b> Postoji više redova koji imaju jednake vrednosti za atribute "Projekat" i "Zadatak" pa iz tog razloga ne možemo odrediti o kom redu je reč. Npr. za vrednosti atributa "Projekat"=pr2 i "Zadatak"=z2 mi ne možemo znati o kojem redu je reč jer prvi, treći i četvrti red imaju te vrednosti za odgovarajući atribut.
</details>
    
<details>
  <summary><b>c) (radnik)</b></summary>
  <b>Rešenje:</b> Ključ
  
  <b>Objašnjenje:</b> Vrednosti atributa "Radnik" su jedinstvene pa iz tog razloga važi osobina <i>jedinstvenosti</i>. Ključ čini samo jedan atribut što znači da ne postoje atributi koji bi bili suvišni pa odatle sledi da važi i osobina <i>neredudantnosti</i>. Kako važi i osobina jedinstvenosti i osobina neredudantnosti možemo zaključiti da je data kolekcija atributa ključ.
</details>

***
### Zadatak 3
  
Neka je data relacija 
       **promet(barKod,datumPrometa,kupac,kolicina)**
  
Ako je u datoj relaciji ključ 
  1. PK(barKod,kupac)
  2. PK(barKod,datumPrometa)
  
Odgovori na sledeća pitanja:
<details>
  <summary><b>a) Koliko najviše različitih kupaca može da kupi isti proizvod u jednom danu? </b></summary></br>
  1. PK(barKod,kupac)</br>
  <b>Rešenje:</b> Beskonačno mnogo
  
  <b>Objašnjenje:</b> Iako atribut "barKod" ima istu vrednost, atribut "kupac" će imati različite vrednosti pa će i ključevi tih redova biti različiti što znači da možemo imati beskonačno različitih kupaca. Naravno svaki kupac će moći samo jednom da kupi dati proizvod</br>
  </br>
  2. PK(barKod,datumPrometa)</br>
  <b>Rešenje:</b> Samo jedan</br>
  <b>Objašnjenje:</b> Pita se koliko kupaca može biti u bazi ako su barKod i datumPrometa fiksni. Pošto su to atributi ključa, u bazi se može nalaziti samo jedan red za dati dan i proizvod tako da je najveći broj kupaca koji mogu kubiti isti prozivod u istom danu jedan. 
</details>
    
<details>
  <summary><b>b) Koliko najviše različitih proizvoda jedan kupac može kupiti u istom danu?</b></summary></br>
  1. PK(barKod,kupac)</br>
  <b>Rešenje:</b> Beskonačno mnogo
  
  <b>Objašnjenje:</b> Isto kao u slučaju 1. Vrednost atributa "kupac" je fiksna, a za vrednosti atributa "barKod" možemo imati neograničen broj različitih vrednosti.</br>
  </br>
  2. PK(barKod,datumPrometa)</br>
  <b>Rešenje:</b> Beskonačno mnogo</br>
  <b>Objašnjenje:</b> Fiksiran je datumPrometa i kupac koji je nekljucni atribut. Posto barKod nije fiksan to znaci da ce red biti jedinstven pa postoji beskonacno mnogo kljuceva
</details>


***
## Zadatak 4
Neka je data relacija: 
      **osoba(matBroj,ime,prezime,adresa)**

Posmatrajmo relaciju 
      **roditelj_dete(matBrojRod,matBrojDete)**
Ako je ključ relacije roditelj_dete: 
    1.PK(matBrojRod)
    2.PK(matBrojDete)
    3.PK(matBrojRod,matBrojDete)

Odgovori na sledeća pitanja uz obrazloženje:
<details>
  <summary><b>a) Da li je moguće upisati odnos gde je osoba sama sebi roditelj?</b></summary>
  <b>Rešenje:</b></br> 
  1. Da</br> 
  2. Da</br> 
  3. Da</br> 
</details>

<details>
  <summary><b>b) Da li jedan roditelj može imati više dece? </b></summary>
  <b>Rešenje:</b></br>  
  1. Ne</br> 
  2. Da</br> 
  3. Da</br> 
</details>

<details>
  <summary><b>c) Da li se o jednom detetu mogu čuvati informacije o oba rodtelja?</b></summary>
  <b>Rešenje:</b></br>
  1. Da</br> 
  2. Ne</br> 
  3. Da</br> 
</details>

<details>
  <summary><b>d) Da li je moguće upisati odnos gde je osoba sama sebi deda (baba :) )?</b></summary>
  <b>Rešenje:</b></br> 
  1. Da</br> 
  2. Da</br> 
  3. Da</br> 
</details>



***
### Zadatak 5
Data je relacija **R(Radnik, Projekat, Zadatak, Broj_dana)**. Ako je primarni ključ</br>
    1.PK(Radnik, Projekat)</br>
    2.PK(Projekat, Zadatak)</br>

Odgovoriti na sledeća pitanja:
<details>
  <summary><b>a) Da li radnici mogu raditi na više projekata?</b></summary>
  <b>Rešenje:</b> 
  
  <b>Objašnjenje:</b> 
</details>

<details>
  <summary><b>b) Koliko radnika može raditi na jednom projektu?</b></summary>
  <b>Rešenje:</b> 
  
  <b>Objašnjenje:</b> 
</details>

Ima li nekih posebnih ograničenja?

**OBAVEZNO DATI PRIMER EKSTENZIJE, OBRAZLOŽENJE I NAVESTI OGRANIČENJA (AKO POSTOJE)!!!**


Dropdown Template
---
<details>
  <summary><b>pitanje</b></summary>
  <b>Rešenje:</b> 
  
  <b>Objašnjenje:</b> 
</details>
