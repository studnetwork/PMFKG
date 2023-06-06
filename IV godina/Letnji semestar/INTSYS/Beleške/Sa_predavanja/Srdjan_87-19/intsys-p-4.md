core, support i boundary su klasicni skupovi

> fuzzy skupove koristimo da bi smo definisali lingvisticke vrednosti

# Zakljucivanje

Za razliku od ekspertskih sistema, ovde nije neophodno da se tvrdnja bukvalno poklapa sa pravilom

Na osnovu delimicno tacnih tvrdnji mozemo da dodjemo do zakljucka koji je tacan u nekoj meri (delimicno vazi)

Umesno egzaktnog poklapanja kao kod ekspertskih sistema mi imamo poklapanje pravila i tvrdnje **u nekoj meri**. 
To poklapanje je u stvari njihov presek


**Stepen vazenja zakljucka je visina preseka ova 2 skupa** (skupa pravila i tvrdnje)


Zakljucivanje se najcesce radi tako sto se rezultat, koji predstavlja fuzzy skup, defazifikuje i time dobije crisp vrednost koja predstavlja zakljucak


Kada nadjemo visinu preseka onda je koristimo za presecanje fuzzy skupa zakljucka na 2 dela. Deo ispod te linije predstavlja rezultujuci skup.

---

Zakljucak moze da sadrzi vise fuzzy skupova, tj. vise terma. Kada vrsimo zakljucivanje onda presecanje zakljucka vrsimo **samo** nad onim skupovima/termima koji su **deo** zakljucka u pravilu. Oni koji nisu deo pravila se ignorisu.

Ako postoji vise pravila onda se za svako odsecanjem zakljucka dolazi do rezultujuceg skupa za dato pravilo, a zatim se svi ti rezultati spoje unijom u jedan skup cime bi se dobio konacan rezultat zakljucivanja


Kada je vise pravila povezano sa logickim veznikom:
* `AND` onda se uzima **minimalni** stepen ispunjenosti
* `OR` onda se uzima **maksimalni** stepen ispunjenosti
i na osnovu njega se vrsi odsecanje



**Baza znanja** je sastavljena od pravila i definicija svih fazi skupova (i univerzalnih skupova) koji se koriste u uslovima i zakljuccima pravila

MOM i COG daju slican rezultat ako nema nekih peak-ova

Ovaj opisani proces zakljucivanja predstavlja **Mamdanijev proces zakljucivanja**.

Pored njega postoje i neki drugi, npr. Sugeno i Cukamoto tehnike

# Sugeno tehnika zakljucivanja (TSK)

Pravilo je oblika:
```
IF x is A AND y is B THEN z; z is f(x,y)
```

U pravilu se moze naci i vise uslova.

`z` nije fuzzy skup, vec f-ja.

Koristi se kada mozemo da pronadjemo funkciju koja moze da poveze ulaze `x` i `y`.  
Najcesce se koristi ANN za pronalazenje ove f-je

Nastala je iz potrebe da se vrsi fuzzy zakljucivanje nad podacima koji su u formi ulaz-izlaz
(?)

Ako je f konstantna f-ja onda je to **Sugenov model nultog reda**.  
On odgovara Mamdanijevom modelu. Zakljucak je u oba slucaja skup singltona

Ako je f linearna f-ja onda je to **Sugenov model prvog reda**


Stepeni poklapanja tvrdnji sa uslovima pravila nemaju nikakvu ulogu u definisanju zakljucka, 
**ne uticu direktno** na zakljucak pravila. On je definisan mat. f-jom. 
Oni imaju ulogu pondera u kombinovanju zakljucaka svakog pojedinacnog uslova (antecedenta) pravila.

Za jedan uslov se izracuna apsolutna vrednost razlike stepena pripadnosti preseka fuzzy skupova koji su definisani u uslovu i crisp vrednosti
(svaka crisp vrednost "sece" odgovarajuci fuzzy skup nekog uslova i u toj tacki dobijamo pripadnost). 
Time se dobija jedan ponder (ponder == umnozak necega)

Za svaki uslov dobijemo ponder. Preracuna se rezultat funkcije `z` za dato pravilo i pondira (pomnozi) sa odgovaraujcim ponderom. Te proizvode sumiramo i
podelimo sa zbirom svih pondera. Time se dobija konacan rezulat zakljucivanja.

Formula kojom dobijamo stepen tacnosti zakljucka `z`:
```
z = (w1*z1+w2*z2) / (w1+w2)
```

`z1` je rezultat koji se dobije kada se funkciji koja je spomenuta na pocetku ove sekcije proslede date crisp vrednosti, a `z2` 
je takodje rezultat takve neke funkcije koja prihvata iste vrednosti (funkcije za `z1` i `z2` su razlicite)

`w1` i `w2` predstavljaju pondere koje smo dobili kao apsolutnu razliku pripadnosti prvog i drugog uslova

# Cukamoto metoda

Zakljucci pravila su `S` i `Z` f-je

Zakljucivanje se vrsi slicno kao u Mandanijevoj tehnici

Malo podseca na kombinaciju Mandanijeve i Sugeno tehnike

Odsecanje se vrsi na isti nacin kao i kod Mandanijeve tehnike. Te dobijene pripadnosti (`w1`, `w2`, ...) koje kod Mamdanijeve tehnike 
dele fuzzy skup zakljucka na 2 dela sada preseca funkciju koja se koristi umesto tog skupa. 

Od te tacke preseka se povlaci normala na osu koja sadrzi vrednosti univerzalnog skupa i time se dobija rezultat, npr. `z1` 

To se uradi za svako pravilo i onda te rezultate (`z1`, `z2`, ...) spajamo tako sto vrsimo ponderisanje (sa `w1`, `w2`, ...)

Formula:
```
z = (w1*z1 + w2*z2) / (w1+w2)
```
