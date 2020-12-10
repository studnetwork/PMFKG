# Sadržaj

* [DML ( Data Managment Language )][dml]
    * [DISTINCT][distinct]
    * [BETWEEN][between]
    * [IN][in]
    * [LIKE][like]
    * [ORDER BY][order by]
    * [CASE][case]
    * [EXISTS][exists]
* [DDL ( Data Definition Language )][ddl]
* [DQL ( Data Query Language )][dql]
* [Funkcije][funkcije]
    * [CONCAT][concat]
    * [CAST][cast]
    * [Datumske funkcije][datumske funkcije]
        * [DATEPART][datepart]
        * [DATEDIFF][datediff]
        * [DATENAME][datename]
        * [GETDATE][getdate]
    * [Agregatne funkcije][agregatne funkcije]
        * [COUNT][count]
        * [AVG][avg]
        * [MIN][min]
        * [MAX][max]
        * [SUM][sum]
* [Tipovi podataka][tipovi podataka]
* [Komande koje ne pripadaju SQL-u][nonsql komande]
    * [GO][go]
* [Ostalo][ostalo]


**Zapis** - red  
**Polje** - kolona  

Ovi pojmovi su pravilniji iz razloga što, pored osobina koje imaju red i kolona, imaju i podatke o njihovom kontekst - **metapodatke**. 

SQL naredba je kompletan skup klauzula koji vraća vrednost i završava se sa `;`

Primer:  
```
SELECT Imes AS 'Ime studenta'
FROM Studenti
WHERE Mesto = 'Kragujevac';
```
Ceo ovaj kod predstavlja jednu SQL naredbu. Ova naredba je sačinjena od sledećih klauzula:  

1. `SELECT Imes`
2. `AS 'Ime studenta'`
3. `FROM Studenti`
3. `WHERE Mesto = 'Kragujevac'`

**Napomena**: termini *naredba* i *klauzula* u nastavku teksta nisu ispravno korišćeni

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

Potrebno je da vrednost `leva_granica` bude veća od vrednosti `desna_granica`. Ukoliko taj uslov nije ispunjen, kao rezultat se dobija prazna tabela. 

**Napomena**: korišćenje ovde komande nije preporučljivo kada se radi sa podacima `DATETIME` tipa jer može doći do pogrešnog tumačenja. Razlog tome je što desna granica obuhvata samo trenutak u kome je započet novi dan `yyyy-mm-dd 00:00:00.000`, ali vreme koje protekne od tog trenutnka pa do kraja tog dana `yyyy-mm-dd 23:59:59.999` nije uključeno u ovaj interval.


Sintaksa:
```
SELECT column_name
	FROM table_name
	WHERE column_name BETWEEN value1 AND value2;
```
Iz tabele `table_name` uzima sve zapise čija se vrednost polja `column_name` nalazi između vrednosti `value1` i vrednosti `value2`

***

## IN

Ima istu funkciju kao i skupovni operator `in`. Proverava da li se neka vrednost nalazi u nekoj listi vrednost ( ili u vrednostima tabele podupita ).

Sintaksa:  
```
SELECT column_name
FROM table_name
WHERE column_name IN (value1,value2,...)
```
Iz tabele `table_name` uzima sve zapise cija se vrednost za polje `column_name` nalazi u listi `(value1, value2,...)`

`IN` radi tako što vrednost izraza koji se nalazi pre njega (u navedenom primeru to je `column_name`) upoređuje, korišćenjem operatora `=` sa svakom vrednošću iz liste vrednosti. Iz tog razloga, ako se u listi nalazi barem jedna `NULL` vrednost, zapis neće biti vraćen (čak i ako dođe do upoređivanja `NULL = NULL`)

Kada se koristi za proveru vraćenih vrednosti iz podupita, `IN` vrši upoređivanje i, zavisno od rezultata, filtrira zapise spoljašnjeg upita.

Ekvivalentan je klauzuli `= ANY`

Iako je u nekim situacijama ekvivalentan sa `EXISTS`, razlike ipak postoje. 

Više o razlici `IN` i `EXISTS` možete pročitati na sledećem [linku][exists].


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

Klauzula `ORDER BY` je jedna od retih klauzula naredbe `SELECT`, ako ne i jedina, koja  može koristiti nazive (*alias*) definisane u selekcionoj listi klauzule `SELECT`

Primer:  
```
SELECT Imes AS 'Ime studenta'
FROM studenti
order by 'Ime studenta'
```

***

## CASE

Postoje dva načina korišćenja ove naredbe, `Simple CASE` i `Searched CASE`

Obično se može naći u:  

* naredbi `SELECT`
* naredbi `DELETE`
* naredbi `UPDATE`
* klauzuli `SELECT`
* klauzuli `ORDER BY`
* klauzuli `HAVING`


### Simple CASE

Sintaksa:  
```
CASE expression
WHEN when_expression_1 THEN
	result_1
WHEN when_expression_2 THEN
	result_2
...
ELSE
	else_result
END
```
`CASE` upoređuje izraz `expression` sa izrazima koji se nalaze između `WHEN` i `THEN` korišćenjem operatora `=` i ukoliko dođe do podudaranja, vraća se kao rezultat vrednost iz klauzule `THEN` ( odnosno jedan od `result_1`, `result_2`, ... )

`ELSE` klauzula je opciona.

Ukoliko nije došlo do podudaranja ni sa jednim izrazom, vraća se vrednost `ELSE` klauzule ukoliko je ona navedena, ukoliko nije vraća se `NULL`.

Može se i dogoditi da dođe do podudaranja sa više izraza. U tom slučaju, vraća se vrednost prvog po redu izraza sa kojim je došlo do podudaranja.

![CASE sa vise podudaranja][simple case podudaranje]

Primer primene:  
Pretpostavimo da je trenutna godina 2000. Tada za upit  
```
SELECT 
    first_name,
    last_name,
    hire_date,
    CASE (2000 - YEAR(hire_date))
        WHEN 1 THEN '1 year'
        WHEN 3 THEN '3 years'
        WHEN 5 THEN '5 years'
        WHEN 10 THEN '10 years'
        WHEN 15 THEN '15 years'
        WHEN 20 THEN '20 years'
        WHEN 25 THEN '25 years'
        WHEN 30 THEN '30 years'
    END aniversary
FROM
    employees
ORDER BY first_name;
```
dobijamo rezultat  
![Rezultat primera][simple case primena]  
Možemo uočiti da poslednja tri radnika za vrednost polja `aniversary` imaju `NULL`. Kao što je već prethodno pomenuto, ukoliko ne dođe ni do jednog podudaranja i pritom klauzula `ELSE` nije definisana, naredba `CASE` će vratiti vrednost `NULL`.


### Searched CASE

Sintaksa:  
```
CASE
WHEN boolean_expression_1 THEN
	result_1
WHEN boolean_expression_2 THEN
	result_2
WHEN boolean_expression_3 THEN
	result_3
ELSE
	else_result
END;
```

Ponaša se isto kao i `Simple CASE`, jedina razlika je to što umesto poređenja, `Searched CASE` ispituje da li je neki uslov ispunjen i ukoliko jeste, vraća vrednost koja je određena za takvu sitaciju.

Ukoliko se ne navede `ELSE` klauzula i ne dođe do ispunjavanja nekog uslova, vraća se `NULL`

Ukoliko postoji više od jednog ispunjenog uslova, vraća se vrednost prvog po redu uslova koji je zadovoljen.

Primer:  
```
SELECT 
    first_name,
    last_name,
    CASE
        WHEN salary < 3000 THEN 'Low'
        WHEN salary >= 3000 AND salary <= 5000 THEN 'Average'
        WHEN salary > 5000 THEN 'High'
    END evaluation
FROM
    employees;
```
Rezultat navedenog primera:  
![Rezultat primera searched case-a][searched-case-primena]

Detaljnije informacije i navedene primere možete naći na sledećem [linku][case info]  
Dokumentacija naredbe `CASE` se može naći na sledećem [linku][case ms docs].

***

## EXISTS

Broji koliko se zapisa nalazi u nekoj tabeli ( najčešće rezultatu podupita ) i ukoliko u njoj postoji barem jedan zapis vraća `TRUE`, u suprotnom vraća `FALSE`. 

Obično se koristi se u sitacijama kada uz pomoć podupita selektujemo neke zapise. Tada se u podupitu pravi uslov po kome će biti filtrirani zapisi. Ako se vrati `FALSE` znači da uslov nije zadovoljen i tada ne dolazi do selekcije zapisa iz **spoljašnjeg** upita.

Filrtiranje zapisa se vrši unutar podupita.

Vrednosti koje se vrate podupitom za `EXISTS` **nisu bitne**. Jedino što je bitno je da li postoji barem jedan red ili ne. To znači da i `NULL` vrednost posmatra kao i bilo koju drugu, jer mu one svakako ništa ne znače.

**Važna napomena:** greška koja se često pravi pri korišćenju ove komande je da se unutar podupita ne postavki nikakav uslov koji se odnosi sa jedan secifičan zapis, pa se prilikom svake iteracije proverava jedan te isti uslov: da li u rezultatu podupita postoji neki zapis. Zbog izostavljanja takvog uslova, za svaki zapis će razultat biti isti. Obično se to rešava tako što se osigura da su identifikatori entiteta jednaki ( tj. da se radi o istom entitetu ) pa se nakon toga zadaje uslov.

***

# DDL komande
***

# DQL komande
***

# Funkcije

## CONCAT

Pretvara argumente u string i nakon toga ih spaja. Može imati najviše 254 argumenta. `NULL` argumente pretvara u prazan string. Argumenti koji predstavljaju brojeve se automatski pretvaraju u string. Obično se koristi za spajanje vrednosti kolona ili za spajanje nekog stringa na vrednost određene kolone.

**Nije deo SQL standarda**

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

# Datumske funkcije

### DATEPART

Koristi se za dobijanje određenog podatka nekog datuma. Kao rezultat vraća vrednost tipa `int`. 

**Nije deo SQL standarda**

Sintaksa:
```
DATEPART ( datepart , date )  
```

Argument `datepart` može biti neka od sledećih ključnih reči:


* `YEAR`
* `QUARTER`
* `MONTH`
* `DAYOFYEAR`
* `DAY`
* `WEEK`
* `WEEKDAY`
* `HOUR`
* `MINUTE`
* `SECOND`
* `MILLISECOND`
* `MICROSECOND`
* `NANOSECOND`
* `TYOFFSET`
* `ISO_WEEK`

( pored navedenih ključnih reči postoje i neki skraćeni oblici )

Više o `DATEPART` funkciji možete pročitati na sledećim linkovima:  
[sqltutorial DATEPART][datepart sqltutorial]  
[MS dokumentacija funkcije][datepart ms docs]

***

### DATEDIFF

Uzima kao argumente interval po kome će se vršiti upoređivanje, datum kada je nešto započeto i datum kada je to završeno i vraća kao rezultat razliku intervala ta dva datuma.

**Nije deo SQL standarda**

Sintaksa:
```
DATEDIFF(interval, date1, date2)
```

Može se naći u sledećim klauzulama:

* `SELECT`
* `WHERE`
* `HAVING`
* `GROUP BY`
* `ORDER BY`

Interval može biti neka od sledećih ključnih reči:

* `YEAR`
* `QUARTER`
* `MONTH`
* `DAYOFYEAR`
* `DAY`
* `WEEK`
* `HOUR`
* `MINUTE`
* `SECOND`
* `MILLISECOND`
* `MICROSECOND`
* `NANOSECOND`

( pored navedenih ključnih reči postoje i neki skraćeni oblici )

Više o `DATEDIFF` funkciji možete pročitati na sledećim linkovima:  
[w3schools DATEDIFF()][datediff w3schools]  
[MS dokumentacija funkcije][datediff ms docs]

***

### DATENAME

Najčešće se koristi za predstavljanje imena meseca ili dana u nedelji na osnovu njihovog rednog broja. Ima slične mogućnosti kao i `DATEPART`, s tim što kao rezultat vraća string vrednost izabranog dela koja je tipa `nvarchar`. Jedna od specifičnijih mogućnosti jeste i vraćanje formata vremenske zone u obliku stringa.

**Nije deo SQL standarda**

Sintaksa:
```
DATENAME ( datepart , date )  
```
Primer:  
![Primer korišćenja funkcije DATENAME][datename primer]

Više o `DATENAME` funkciji možete pročitati na sledećem [linku][datename ms docs].

***

### GETDATE

Vraća trenutni datum koji je dobijen pomoću operativnog sistema računara na kome je pokretnua instanca SQL Servera.

**Nije deo SQL standarda**. 
Sintaksa:
```
GETDATE()
```

Može se koristiti kao argument funkcije `DATEDIFF` za određivanje nekih vrednosti što se može videti u sledećem primeru:
```
SELECT Imes AS 'Ime studenta',
	   DATEDIFF( YEAR, datr, GETDATE() ) AS 'Starost'
FROM Studenti
```

Više o `GETDATE` funkciji možete pročitati na sledećem [linku][getdate ms docs].

***

## Agregatne funkcije

Na osnovu kolekcije vrednosti vrše neki proračun i kao rezultat vraćaju jednu vrednost.

Zbog toga što rade nad kolekcijom vrednosti često se koriste sa klauzulom `GROUP BY` naredbe `SELECT` jer `GROUP BY` deli rezultujuću kolekciju u grupe, nakon čega agregatna funkcija vraća jednu vrednost za svaku grupu. Naravno, mogu se koristiti i bez njih.

Primer:  
```
SELECT COUNT(*)
FROM employees
WHERE job_id = 9;
```

Kao izrazi se mogu koristi samo u selekcionoj listi naredbe `SELECT` u unutrašnjem ili spoljašnjem upitu i u klauzuli `HAVING`

Sve agregatne funkcije osim `COUNT` ignorišu `NULL` vrednosti.

***

### COUNT

Ova funkcija broji zapise koji su vraćeni upitom (tj. nekog skupa zapisa ). Povratna vrednost je tipa `int`

Sintaksa:  
```
COUNT([ALL | DISTINCT] expression);
```
Ključna reč `ALL` je podrazumevna opcija pa iz tog razloga nije neophodno njeno navođenje.

Kao argument funkcije se može navesti i `*`, čime se označava da će se brojiti svi zapisi, nezavisno od njihove vrednosti. To podrazumeva i `NULL`. Broje se i duplikati jer se brojanje ne vrši po vrednostima, već se samo prebrojavaju zapisi.

Ukoliko se navede ključan reč `DISTINCT`, vrši se prebrojavanje zapisa na osnovu njihovih vrednosti. Kako `NULL` predstavlja vrednost koja nije poznata, utvrđivanje da li je vrednost nekog zapisa jedinstvena nije moguće. Dakle, ukoliko je navedena reč `DISTINCT`, prebrojavaju se sve jedinstvene vrednosti koje nisu `NULL`.

`COUNT( ime_kolone )` broji zapise čije vrednosti nisu `NULL`

`expression` ne može biti podupit ili agregatna funkcija

Izrazi `COUNT(*)` i `COUNT(1)` su semantički isti i imaju isto vreme izračunavanja.

Može se naći u klauzulama `SELECT`, `ORDER BY` i `HAVING`

Više o `COUNT` funkciji možete pročitati na sledećim linkovima:  
[sqltutorial count][sqltutorial count]  
[MS dokumentacija funkcije][count ms docs]

***

### AVG

Računa prosečnu vrednost neke kolekcije vrednosti.

Sintaksa:
```
AVG([ALL|DISTINCT] expression)
```
Može se koristiti samo nad poljima koja imaju numeričke vrednosti.

`NULL` vrednostima se ignorišu.

Ključna reč `ALL` je podrazumevna opcija pa iz tog razloga nije neophodno njeno navođenje.

Ukoliko se navede ključan reč `DISTINCT`, duplikati ne koriste za izračunavanje prosečne vrednosti.

**Napomena**: ukoliko se koristi nad celobrojnim vrednostima, rezultat će takođe biti celobrojan. Decimalan rezultat možemo dobiti množenjem argumenta sa `1.0` kako bi se dobio decimalan argument, ili korišćenjem funkcije `CAST` kako bi se izvršilo njegovo pretvaranje u decimalan broj

Više o `AVG` funkciji možete pročitati na sledećem [linku][avg ms docs]

***

### MIN

Određuje najmanju vrednost neke kolekcije vrednosti. U slučaju da u kolekciji ne postoji ni jedna vrednost, vraća `NULL`

Sintaksa:
```
MIN(column | expression)
```
Ignoriše `NULL` vrednosti.

Ukoliko se traži najmanja vrednost za kolekciju koja je nekog karakter tipa, vraća onu vrednost koja se nalazi na poslednjem mestu u sortiranom nizu.

***

### MIN

Određuje najveću vrednost neke kolekcije vrednosti. U slučaju da u kolekciji ne postoji ni jedna vrednost, vraća `NULL`

Sintaksa:
```
MAX(column | expression)
```
Ignoriše `NULL` vrednosti.

Ukoliko se traži najveća vrednost za kolekciju koja je nekog karakter tipa, vraća onu vrednost koja se nalazi na najvišem mestu u sortiranom nizu.

***

### SUM

Sumira kolekciju vrednosti. Ukoliko je kolekcija prazna, vraća `NULL`

Sintaksa:
```
SUM([ALL|DISTINCT] expression)
```

Može se koristiti samo nad vrednostima numeričkih tipova podataka.

Ukoliko se navede ključna reč `DISTINCT`, duplikati ne ulaze u proračun sume.

# Tipovi podataka


## Razlike između tipova char, nchar, varchar i nvarchar

`char` predstavlja *Non-Unicode* stringove fiksne dužine

`nchar` predstavlja i *Unicode* i *Non-Unicode* stringove fiksne dužine. Duplo više mesta zauzima od `char` pa iz tog razloga ima duplo manju dužinu od njega

`varchar` predstavlja *Non-Unicode* stringove promenljive dužine

`nvarchar` predstavlja i *Unicode* i *Non-Unicode* stringove promenljive dužine, pa zbog pokrivenosti *Unicode-a* zauzima duplo više memorije od tipa `varchar`

Tipovi fiksne dužine zauzimaju dužinu koja je navedena kao maksimalna, bez obzira stvarnu veličinu stringa, dok tilovi promeljive dužine zauzimaju samo onoliko memorije koliko je potrebno za skladištenje datog stringa.

Slovo `n` u ovim tipovima ima značenje *national*.

Više o tipovima podataka možete pročitati na sledećem [linku][char tipovi]

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

Detaljnije informacije o razlikama u SQL dijalentima možete pronaći na ovom [linku][sql dialects].



[//]: # (---------------------------------------------------------)

[//]: # (-------------U ovom delu se nalaze reference-------------)

[//]: # (---------------------------------------------------------)



[//]: # ( Sadržaj reference )

[dml]: ./SQL_skripta.md#DML-komande
[ddl]: ./SQL_skripta.md#DDL-komande
[dql]: ./SQL_skripta.md#DQL-komande
[funkcije]: ./SQL_skripta.md#Funkcije
[tipovi podataka]: ./SQL_skripta.md#Tipovi-podataka
[nonsql komande]: ./SQL_skripta.md#Komande-koje-ne-pripadaju-SQL-u
[ostalo]: ./SQL_skripta.md#Ostalo


[//]: # ( DML reference )

[distinct]: ./SQL_skripta.md#distinct
[between]: ./SQL_skripta.md#between
[in]: ./SQL_skripta.md#in
[like]: ./SQL_skripta.md#like
[order by]: ./SQL_skripta.md#order%20by
[case]: ./SQL_skripta.md#case
[exists]: ./SQL_skripta.md#exists



[//]: # ( Funkcije reference )

[concat]: ./SQL_skripta.md#concat
[cast]: ./SQL_skripta.md#cast
[datumske funkcije]: ./SQL_skripta.md#Datumske-funkcije
[datepart]: ./SQL_skripta.md#datepart
[datediff]: ./SQL_skripta.md#datediff
[datename]: ./SQL_skripta.md#datename
[getdate]: ./SQL_skripta.md#getdate
[agregatne funkcije]: ./SQL_skripta.md#Agregatne-funkcije
[count]: ./SQL_skripta.md#count
[avg]: ./SQL_skripta.md#avg
[min]: ./SQL_skripta.md#min
[max]: ./SQL_skripta.md#max
[sum]: ./SQL_skripta.md#sum



[//]: # ( Ostalo reference )

[go]: ./SQL_skripta.md#go
[sql dialects]: https://en.wikibooks.org/wiki/SQL_Dialects_Reference



[//]: # ( Reference iz teksta )

[//]: # ( Reference slika )

[distinct-agr]: ./distinct-agr.png
[concat primer]: ./concat.png
[go count]: ./go-count.png
[simple case podudaranje]: ./simple-case-podudaranje.png
[simple case primena]: ./simple-case-primena.png
[searched-case-primena]: ./searched-case-primena.png
[datename primer]: ./datename.png


[//]: # ( Microsoft docs reference )

[use ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/language-elements/use-transact-sql?view=sql-server-ver15

[case ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/language-elements/case-transact-sql?view=sql-server-ver15

[concat ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/functions/concat-transact-sql?view=sql-server-ver15

[cast ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/functions/cast-and-convert-transact-sql?view=sql-server-ver15

[datepart ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/functions/datepart-transact-sql?view=sql-server-ver15

[datediff ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/functions/datediff-transact-sql?view=sql-server-ver15

[datename ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/functions/datename-transact-sql?view=sql-server-ver15

[getdate ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/functions/getdate-transact-sql?view=sql-server-ver15

[count ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/functions/count-transact-sql

[avg ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/functions/avg-transact-sql?view=sql-server-ver15

[go ms docs]: https://docs.microsoft.com/en-us/sql/t-sql/language-elements/sql-server-utilities-statements-go?redirectedfrom=MSDN&view=sql-server-ver15


[//]: # ( Vise informacija reference )

[wildcard]: https://www.computerhope.com/jargon/w/wildcard.htm

[wildcards w3schools]: https://www.w3schools.com/sql/sql_wildcards.asp

[like w3schools]: https://www.w3schools.com/sql/sql_like.asp

[case info]: https://www.sqltutorial.org/sql-case/

[datepart sqltutorial]: https://www.sqltutorial.org/sql-date-functions/sql-datepart/

[datediff w3schools]: https://www.w3schools.com/SQl/func_sqlserver_datediff.asp

[sqltutorial count]: https://www.sqltutorial.org/sql-aggregate-functions/sql-count/

[char tipovi]: https://www.mssqltips.com/sqlservertip/4322/sql-server-differences-of-char-nchar-varchar-and-nvarchar-data-types

[go stackoverflow]: https://stackoverflow.com/questions/20711326/sql-server-what-are-batching-statements-i-e-using-go-good-for
  
