Zapis - red  
Polje - kolona

Ovi pojmovi su pravilniji iz razloga što, pored osobina koje imaju red i kolona, imaju i podatke o njihovom kontekst - metapodatke. 

**DISTINCT**  
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

**BETWEEN**  
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

**IN**  
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

Ekvivalentna je klauzuli `= ANY`


[//]: # (Also be aware that NOT IN is not equivalent to NOT EXISTS when it comes to null. )

[see later]: https://sqlinthewild.co.za/index.php/2010/02/18/not-exists-vs-not-in/

***

**LIKE**  
Služi za pretraživanje stringova. Za njega se vezuju 2 [wildcard-a][wildcard]: `%` i `_`.

`%` - predstavlja nula, jedan ili više karaktera  
`_` - predstavlja jedan karakter


Primer:
```
SELECT *
FROM Customers
WHERE CustomerName LIKE 'a_%' 
```
Iz tabele `Customers` uzima podatke o svim zapisima koji za polje `CustomerName` imaju string koji započinje sa slovom `a` i moraju biti dugi barem 2 karaktera ( jedan za `a` i drugi koji za `_` koji predstavlja slovo )

***

**ORDER BY**
Sortira zapise po vrednostima kolona. Način sortiranja može biti rastući `ASC` ili opadajući `DESC`. Podrazumevana vrednost je `ASC`, tako da nije potrebno njeno navođenje.

Primer:
```
SELECT * 
FROM Customers
ORDER BY Country DESC;
```
Iz tabele `Customers` prikazuje sve podatke sortirane po vrednosti za polje `Country` u opadajućem poretku.


***

**EXISTS**  
Upoređuje vrednosti podupita i filtrira ih unutar samog podupita. Prebrojava redove i ignoriše vrednosti podupita, **čak i ako se radi o `NULL` vrednosti**.

[distinct]: 
[between]: 
[in]: 
[like]: 
[order by]: 
[exists]: 


[distinct-agr]: ./distinct-agr.png
[wildcard]: https://www.computerhope.com/jargon/w/wildcard.htm
