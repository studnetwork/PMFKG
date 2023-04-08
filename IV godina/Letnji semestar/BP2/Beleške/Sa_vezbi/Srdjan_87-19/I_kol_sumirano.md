# Vezbe 1

## Heap

Gomila se ponasa kao gomila:
* "stvari" se "nabacaju" na gomilu
* nema nekog rasporedjivanja
* stedi prostor jer se ne zauzima vise prostora
  nego sto je potrebno zbog nekakve organizacije
* lako se prosiruje (jer se samo "dobaci" nova
  stvar koja dodje)
* tesko se nalaze "stvari" jer je sve "nabacano"
* sortiranje je sporo jer je sve "nabacano "
* koristi se samo kada nesto sa organizacijom
  treba slicno da uradi (ucita sve zapise)
  
 
## Indeksi

Ubrzavaju pretragu jer koriste B-stablo

Imaju kljuc po kom se pretrazuje i pointer koji vodi
do podataka. Kljuc predstavlja podatke jednog ili vise 
atributa iz tabele.

### Klasterovani

U listovima su podaci iz tabele, tj. same stranice

Uglavnom se postavljaju na PK

Podaci su fizicki sortirani po kljucu pretrage

Najvise 1 moze da se postavi nad tabelom

Pretraga dovodi do neke stranice. Ako ta stranica
nije trazena onda se od ove do koje smo dosli ide
sekvencijalno

### Neklasterovani

sadrzi u listovima pokazivace

pokazivaci su uredjeni

ne utice na fizicku organizaciju i zbog toga moze 
da ih ima vise 


## Ostalo

Operator Cost i Subtree Cost predstavljaju vreme
izvrsenja upita

Rows per Execution predstavlja broj redova koji je
ucitan u radnu memoriju (broj redova koji ce se naci
u rezultatu)


# Vezbe 2

Izgled neklasterovanog indeksa:
1. klasterovani    postoji => `kljuc_pretrage, kljuc_pretrage_klasterovanog`
2. klasterovani ne postoji => `kljuc_pretrage, RID`

Neklasterovani indeks povecava performanse u slucajevima
kada se u upitu ne koriste atributi koji nisu deo
kljuca pretrage. Zasto? Zato sto ne mora da se dobavlja nedostajuci
podatak iz skladista.

Ovo je bitno. Neklasterovani se isplati samo kada podaci iz 
njega mogu da se iskoriste tako da se ne pristupa skladistu.

Takodje, `count(*)` moze da koristi samo podatke iz indeksa 
za svoje izvrsenje, ne mora da se ide do skladista 


Mozemo da kombinujemo oba tipa indeksa. Npr. neklasterovani koristimo
pri pronalazenju onoga sto ispunjava uslvo iz `WHERE`-a, a klasterovani 
za dolazak do same stranice na koju neklasterovani pokazuje i 
ucitavanje svih potrebnih podataka koji se ne nalaze u neklasterovanom
indeksu

Primer: `SELECT * FROM person WHERE firstname LIKE 'Diane';`

Key Lookup je brzi od RID Lookup-a


# Vezbe 3

`GROUP BY` zahteva uredjenje (sortiranje ili hashing (?))

`ORDER BY` moze da se ubrza ako nad datim kolonama postoji 
indeks (naravno, ako u `SELECT`-u postoje i podaci kojima 
se ne moze pristupiti iz indeksa onda do ubrzanja nece doci)


**BITNO: neklasterovani indeks se ne koristi ako treba da se 
ucita veci broj zapisa**

Kada se radi sa klasterovanim indeksima nije bitno kakav je 
`SELECT` (sta se selektuje od atributa) jer se svi podaci 
svakako ucitavaju pri pristupu stranici na kraju pretrage.

Za sortiranje svih kolona:
Klasterovani > neklasterovani

Za sortiranje kolona koje su deo kljuca pretrage:
Klasterovani < neklasterovani

## Kompozitni indeks

Vise kolona cini jedan kljuc pretrage

Koristi se obicno zbog `GROUP BY` i `ORDER BY`

Sporije radi u odnosu na jednostavan indeks ili indeks sa 
pravim podskupom kolona koje cine njegov kljuc pretrage.
Zasto? Zato sto je sam indeks veci pa je vise vremena 
potrebno za ucitavanje, a takodje je i vreme pristupa sporije. 

To usporenje postoji, ali opet nije toliko ni lose, npr. u 
situaiciji gde trebamo da ubrzamo upit pomocu kompozitnog kljuca,
ali i neki drugi upit koji sadrzi podskup kljuca pretrage kao 
svoj kljuc pretrage. Ovaj drugi upit ce raditi mozda malo sporije 
nego sto bi inace mogao da radi, ali generalno oba upita 
ubrzavamo jednim indeksom.


Ono sto je bitno kod kompozitnih indeksa jeste da se 
podaci sortiraju u redosledu u kom su definisane kolone
u samom kljucu. Kada postoje iste vrednosti one se onda 
sortiraju po narednoj koloni i tako do dalje za sve 
kolone kljuca 	pretrage.

# Vezbe 4

```TSQL
EXEC sp_helpindex person;
EXEC sp_spaceused person;
```

Velicina neklasterovanog indeksa je znacajno veca od 
velicine klasterovanog.

Neklasterovani bez definisanog klasterovanog indeksa nad 
tabelom zauzima vise memorije nego kada je klasterovani
definisan. To se desava zato sto je kljuc pretrage 
klasterovanog deo neklasterovanog 

Ako je klasterovani kljuc definisan nad kolonom koja 
nije auto-increment onda zauzima vise memorije jer 
ostavlja prazna mesta za slucaj da nesto treba da se umetne
pa time trosi i vise memorije.


## Include

Dodaje podatke u indeks, ali se time ne dodaju u 
kljuc pretrage (iz cega onda sledi i da ne uticu na sortiranje)


Sto je indeks manje to je brzina pretrage veca.

Ako je neki atribut potreban samo kao podatak, ali ne i 
kao nesto po cemu se vrsi filtriranje, grupisanje ili sortiranje
onda bi trebao da se doda include-om.

Ako je potreban i za ove operacije onda je mozda bolje koristi
kompozitni kljuc 

Nikada nema potrebe da se koristi include u kombinaciji sa
klasterovanim indeksom 


Velicina kompozitnog indeksa se uvecava onoliko puta koliko
je atributa sadrzi u kljucu pretrage.

Indeksi mogu i da uspore izvrsavanje nekih upita.
-- Takav ja slucaj sa INSERT, UPDATE i DELETE naredbama.
## Insert

Neklasterovani indeksi usporavaju `INSERT`

Ako se retko rade dodavanja onda to i nije toliki problem.

## Update

Moze se posmatrati kao visestruka operacija: `SELECT` + `INSERT` 

Neklasterovani indeksi usporavaju sam upit, ali za razliku od 
`INSERT` mogu da se optimizuje (zbog `WHERE`-a). 

Azuriranje je brze ukoliko se podaci ne nalaze u indeksu 
jer se onda azuriraju samo na jednom mestu (u suprotnom bi
morali da se azuriraju i u indeksu)

## DELETE 

Slicno kao `UPDATE`

## Joins

### Nested Loops Join 

Dosta spor. Koristi se samo kada ima malo podataka (tj. kombinacija)
jer tad i moze da bude isplativo

### Hash Join

Pravi Hash tabelu pa preko nje pristupa podacima.

Pravljenje te tabele je moze dugo da traje.

Ideja je da se obe tabele sortiraju i onda "prodje samo jednom"

Posto je neophodno sortiranje onda je zgodno da postoje indeksi 
nad tim vrednostima po kojima se spaja 
(jer nam je potrebno da te kolone budu sortirane).


## Koriscenje

Ukoliko podaci nisu uredjeni (nema indeksa) 
SQL Server ce uglvnom birati Hash Join.

Merge Join je povoljan u situaciji kada se spajanje vrsi po kolonama nad kojima 
je definisan klasterovni indeks (jer to pruza uredjenje koje je potrebno za merge)

Cak i kada druga tabela nije sortirana to moze da bude bolja opcija od izgradnje 
Hash tabele i tada bi se izvrsilo sortiranje te druge tabele pa onda Merge Join.

Kako bi smo dodatno optimizovali upit mozemo da definisemo neki indeks nad 
spoljasnjim kljucem. Ako se zahteva i neki podatak iz druge tabele koji nije
dostupan iz indeksa njega mozemo dodati include-om 

Neklasterovani indeksi mogu da zauzmu dosta memorije. To moze da se smanji
ako se zamene sa klasterovanim. Naravno, to nije uvek moguce, ali treba to imati
na umu za slucaj da njihova zamena ima smisla. Rezultat zamene bi bio znacajno
smanjenje velicine indeksa
