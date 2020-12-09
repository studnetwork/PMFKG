# Sadržaj
* DML ( **D**ata **M**anagment **L**anguage )
    * [DISTINCT][distinct]
    * [BETWEEN][between]
    * [IN][in]
    * [LIKE][like]
    * [ORDER BY][order by]
    * [EXISTS][exists]
* DDL ( **D**ata **D**efinition **L**anguage )
* DQL ( **D**ata **Q**uery **L**anguage )
* Funkcije
* Tipovi podataka
* Komande koje ne pripadaju SQL-u
    * [GO][go]
* Ostalo


**Zapis** - red  
**Polje** - kolona  

Ovi pojmovi su pravilniji iz razloga što, pored osobina koje imaju red i kolona, imaju i podatke o njihovom kontekst - **metapodatke**. 

# DML komande

## USE
Koristi se promenu aktivnog kataloga nad kojim će se raditi. U našem slučaju to je bio katalog `Studije`

Primer:
Neka je baza podataka sadrži dva kataloga - `Organizacija` i `Studije` i neka je trenutno aktivan / odabran katalog `Organizacija`. Tada:
```
USE Studije
SELECT *
FROM Statistika
```
Postavlja `Studije` kao trenutno aktivni katalog. Sada će se upiti odavljati nad ovim katalogom.

Microsoft u svojoj implementaciji SQL-a ( T-SQL ) za katalog koristi reč baza podataka iako to ne predstavlja celu bazu, već samo jedan od njenih delova.

Nakon ove komande se često može pojaviti i komanda [GO][go].

Više o komandi `USE` možete pročitati na sledećem [linku][use ms docs].


## DISTINCT  
Koristi se za izbacivanje duplikata. Može se na naći kod komande `SELECT` ili unutar agregatnih funkcija.

Primer pojavljivanja u `SELECT`-u:
```
SELECT DISTINCT column_name1, column_name2
    FROM table_name;
```
Iz tabele `table_name` uzima se po jedan primerak svakog zapisa (n-torke).  

Primer pojavljivanja u agregatnim funkcijama:  
```
SELECT COUNT( DISTINCT Mesto ) AS 'Broj razlicitih mesta stanovanja'
FROM Studenti
```
![Poredjenje upita sa i bez distinct][distinct-agr]

***

## BETWEEN  
Ekvivalentno sledećem izrazu:
```
leva_granica >= vrednost AND vrednost <= desna_granica
```
**Napomena**: korišćenje ovde komande nije preporučljivo kada se radi sa podacima `DATETIME` tipa

Primer:
```
SELECT column_name
	FROM table_name
	WHERE column_name BETWEEN value1 AND value2;
```
Iz tabele `table_name` uzima sve zapise čija se vrednost polja `column_name`
nalazi između vrednosti `value1` i vrednosti `value2`

***

## IN  
Ima istu funkciju kao i skupovni operator `in`. Proverava da li se neka vrednost nalazi u nekoj listi vrednost ( ili u vrednostima tabele podupita ).

```
SELECT column_name
FROM table_name
WHERE column_name IN (value1,value2,...)
```
Iz tabele `table_name` uzima sve zapise cija se vrednost za polje `column_name` nalazi u listi `(value1, value2,...)`

`IN` radi tako što vrednost izraza koji se nalazi pre njega (u navedenom primeru to je `column_name`) upoređuje, korišćenjem operatora `=` sa svakom vrednošću iz liste vrednosti. Iz tog razloga, ako se u listi nalazi barem jedna `NULL` vrednost, zapis neće biti vraćen (čak i ako dođe do upoređivanja `NULL = NULL`)

Kada se koristi za proveru vraćenih vrednosti iz podupita, `IN` vrši upoređivanje i, u skladu sa rezultatom, filtrira zapise spoljašnjeg upita.

Iako je u nekim situacijama ekvivalent komandi `EXISTS`, ona se ipak razlikuju. Opis razlike možete pročitati [ovde][exists].

Ekvivalentan je klauzuli `= ANY`

***

## LIKE  
Služi za ispitivanje stringova korišćenjem regularnih izraza (regex). Neki od [wildcard-ova][wildcard] su:

`%`   predstavlja nula, jedan ili više karaktera  
`_`   predstavlja jedan karakter  
`[]`  predstavlja bilo koji karakter koji se nalazi između `[` i `]`  
`^`   predstavlja bilo koji karakter se ne nalazi u `[]`  
`-`   predstavlja bilo koji karakter koji se nalazi u nekom opsegu. Koristi se unutar `[]`

Primer:
```
SELECT *
FROM Customers
WHERE CustomerName LIKE 'a_%' 
```
Iz tabele `Customers` uzima podatke o svim zapisima koji za polje `CustomerName` imaju string koji započinje sa slovom `a` i moraju biti dugi barem 2 karaktera ( jedan za `a` i drugi koji za `_` koji predstavlja slovo )

Više o pomenutim pojmovima možete pročitati na sledećim linkovima:  
* [SQL Wildcards][wildcards w3schools]  
* [SQL Like][like w3schools]

***

## ORDER BY 
Sortira zapise po vrednostima kolona. Način sortiranja može biti rastući `ASC` ili opadajući `DESC`. Podrazumevana vrednost je `ASC`, tako da nije potrebno njeno navođenje.

Primer:
```
SELECT * 
FROM Customers
ORDER BY Country DESC;
```
Iz tabele `Customers` prikazuje sve podatke sortirane po vrednosti za polje `Country` u opadajućem poretku.


***

## EXISTS  
Upoređuje vrednosti podupita i filtrira ih unutar samog podupita. Prebrojava redove i ignoriše vrednosti podupita, **čak i ako se radi o `NULL` vrednosti**.

***

# Funkcije
## CONCAT
Pretvara argumente u string i nakon toga ih spaja. Može imati najviše 254 argumenta. `NULL` argumente pretvara u prazan string. Argumenti koji predstavljaju brojeve se automatski pretvaraju u string. Obično se koristi za spajanje vrednosti kolona ili za spajanje nekog stringa na vrednost određene kolone.

Primer:  
```
SELECT CONCAT( 'Jedan','==', 1 ) AS 'Jednačina'
```
Rezultat izvršavanja:  
![CONCAT primer][concat primer]  

Više o funkciji `CONCAT` možete pročitati na sledećem [linku][concat ms docs].

***

## CAST
Pretvara jedan tip podatka u drugi.

Sintaksa:  
```
CAST(expression AS datatype(length))
```

Primer:  
```
SELECT CAST(25.65 AS varchar); 
```
Za tipove  

* char
* varchar
* nchar
* nvarchar
* binary
* varbinary


je moguće navesti unutar zagrada `()` još jedan dodatni parametar koji predstavlja dužinu rezultujućeg tipa podatka

Više o funkciji `CAST` možete pročitati na sledećem [linku][cast ms docs].

***

# Tipovi podataka


## Razlike između tipova char, nchar, varchar i nvarchar
`char` predstavlja *Non-Unicode* stringove fiksne dužine

`nchar` predstavlja i *Unicode* i *Non-Unicode* stringove fiksne dužine. Duplo više mesta zauzima od `char` pa iz tog razloga ima duplo manju dužinu od njega

`varchar` predstavlja *Non-Unicode* stringove promenljive dužine

`nvarchar` predstavlja i *Unicode* i *Non-Unicode* stringove promenljive dužine, pa zbog pokrivenosti *Unicode-a* zauzima duplo više memorije od tipa `varchar`

Tipovi fiksne dužine zauzimaju dužinu koja je navedena kao maksimalna, bez obzira stvarnu veličinu stringa, dok tilovi promeljive dužine zauzimaju samo onoliko memorije koliko je potrebno za skladištenje datog stringa.

Slovo `n` u ovim tipovima ima značenje *national*.

Više o tipovima podataka možete pročitati na sledećem [linku][tipovi podataka]

***

# Komande koje ne pripadaju SQL-u
## GO
Ova komanda **nije** ključna reč SQL-a, već se koristi od klijentskih programa kao što je SQL Management Studio Editor. Predstavlja podrazumevani *batch separator* T-SQLa.  

*Batch* je kolekcija od dve ili više SQL naredbe.
Svaki `.sql` fajl je uglavnom jedan batch, ali kada korišćenjem komande `GO` dolazi do podele u više batch-ova. 

`GO` signalizira SQL Serveru da je kraj nekog batch-a dostignut.

Batch se sastoji od naredbi koje predstavljaju sve naredbe koje su unete između prethodne i trenutne `GO` komande, između početka skripte i komade `GO` ili između ove komande i kraja skripte.

`GO` mora biti jedina ključna reč u liniji u kojoj se koristi.

Može biti neophodan u situacijama kada je potrebno da se neke naredbe izvrše u više batch-ova, naročito sa `ALTER` komandama, gde je moguće samo jedno izvršavanje po batch-u.

Pored komande `GO` može se naći i broj koji predstavlja koliko će se puta batch, završen ovom komandom, izvršiti

Na primer:
```
PRINT 'Test';  
GO 7
```
Ovaj batch koji je završen linijom `GO 7` će se sedam puta izvršiti. Kako se u njemu nalazi samo naredba `PRINT 'Test'`, kao rezulrat ćemo dobiti sedam poruka sa sadržajem `Test`  

![Rezultat izvrsavanja][go count]

Više o komandi `GO` možete pročitati na sledećim likovima:  
* [Stackoverflow post][go stackoverflow]  
* [Microsoft dokumentacija][go ms docs]

***

# Ostalo
Stringovi navode na dva načina:
* između apostrofa `'string'`
* između uglastih zagrada `[string]`

Stringovi se mogu pisati i bez ikakvog navođenja, ali samo ukoliko se radi o jednoj reči, pa ukoliko želite da napravite string koji se sastoji od dve ili više reči potrebno je da koristite neki od navedenih načina.



[//]: # (---------------------------------------------------------)

[//]: # (-------------U ovom delu se nalaze reference-------------)

[//]: # (---------------------------------------------------------)



[//]: # ( DML reference )

[distinct]: ./SQL_skripta.md#distinct
[between]: ./SQL_skripta.md#between
[in]: ./SQL_skripta.md#in
[like]: ./SQL_skripta.md#like
[order by]: ./SQL_skripta.md#order%20by
[exists]: ./SQL_skripta.md#exists




[//]: # ( Ostalo reference )

[go]: ./SQL_skripta.md#go



[//]: # ( Reference iz teksta )

[distinct-agr]: ./distinct-agr.png
[concat primer]: ./concat.png
[go count]: ./go-count.png
[wildcard]: https://www.computerhope.com/jargon/w/wildcard.htm

[wildcards w3schools]: https://www.w3schools.com/sql/sql_wildcards.asp

[like w3schools]: https://www.w3schools.com/sql/sql_like.asp

[concat ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/functions/concat-transact-sql?view=sql-server-ver15

[cast ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/functions/cast-and-convert-transact-sql?view=sql-server-ver15

[tipovi podataka]: https://www.mssqltips.com/sqlservertip/4322/sql-server-differences-of-char-nchar-varchar-and-nvarchar-data-types/

[go stackoverflow]: https://stackoverflow.com/questions/20711326/sql-server-what-are-batching-statements-i-e-using-go-good-for

[go ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/language-elements/sql-server-utilities-statements-go?redirectedfrom=MSDN&view=sql-server-ver15

[use ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/language-elements/use-transact-sql?view=sql-server-ver15
