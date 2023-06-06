 ```
 IF "weak stimulus" THEN NOT "severe response"
 ```
 
Moze da se zapise kao
```
IF x pripada W THEN y ne pripada S
```

`y ne pripada S` je u stvari `!S` (komplement od `S`)

 
Mozemo da zapisemo i kao `W => !S`

Implikacija bi izgledala ovako:
```
R = (W x !S) u (!W x Y)
```

`Y` je univerzalni skup za `S` (pa ujedno i za `!S`)


# Automatizacija generisanja pravila na osnovu podataka

Pod podacima se podrazumevaju se podaci koji su dati u obliku ulaz-izlaz, tj.
data set koji sadrzi atribute i labelu.

U supervised (nadgledanom) ucenju mi mozemo da resavamo probleme 
klasifikacije i regresije.

Generisu se i pravila i funkcije pripadnosti (fuzzy skupovi).
Moze da se kaze i da se uce na osnovu podataka.



Ako bi smo imali 2 ulaza sa po 3 terma ona bi smo imali 9 pravila.
Naravno, pozeljno je da se taj broj smanji ukoliko postoji mogucnost za to, tj.
da se napravi sto manja baza znanja sa kojom moze uspesno da se rezonuje.

**Standard Rule Base** - koristimo matricu u kojoj se u celijama nalaze
output-i za datu vrstu ili kolonu koje predstavljaju prvi u drugi ulaz, respektivno.

To je jedan od nacina (dogovora) na koji mogu da se zapisu fuzzy pravila
(alternativa za zapis preko recenica).

Ideja je da se nadje optimalan skup pravila od pravila koja su generisana.

Nisu nam potrebna redudantna pravila.

Jedna od metoda je **Wang-Mendel metoda**

## Wang-Mendel metoda

Postoje razna poboljsanja ove metode koja se mogu naci u literaturi.


Koraci:
1. krene se od skupa podataka
2. dele se univerzalni skupovi na fuzzy podskupove
3. za svaki atribut se utvrdjuju stepeni pripadnosti svakog njegovog primera
4. generise se pravilo od svakog primera/uzorka tako sto se uzme term sa maksimalnom vrednoscu 
   za svaki atribut/labelu posebno (`atr1 = max(...), atr2 = max(...), ..., label = max(...)`)

Ova metoda nalaze da broj tih podskupova, tj. terma **treba** biti neparan `2P +1`.

Univerzalni skupovi se obicno dobijaju kroz ekspertsko znanje. U najopstijem
pristupu generisanja iz podataka to se radi tako sto se uzmu min i max svih
vrednosti za dati atribut, ili da se dozvoli odstupanje od tih minimuma i maksimuma.

Broj termova je hiperparametara, tj. `P` je nesto sto treba eksperimentalno 
da se utvrdi.

U 3. koraku mi u sustini trazimo fuzzy skup kojem primer pripada u najvecoj meri.  

Kada to utvrdimo onda dobijene fuzzy skupove koristimo za formiranje pravila, npr.
ako imamo 2 atributa i labelu, i dobijene skupove `B1`, `S1` i `CE` respektivno, onda
mozemo da formiramo sledece pravilo:
```
IF x1 is B1 AND x2 is S1 THEN y is CE
```

Ako se dogodi da postoji 2 takva skupa, tj. ako ta najveca
vrednost nije jedinstvena onda se mogu generisati 2 pravila za svaki skup. Ono sto
je takodje moguce je da se napravi 1 pravilo (spajanjem) koje u antecedentu ima `OR` za
taj atribut u kome dolazi do pojave istih max vrednosti. Neki ne gotive ovu drugu opciju (`OR`)
jer smatraju da se time gubi razumljivost i lakoca tumacenja pravila, a takodje ne moze da se
koristi Standard Rule Base.


Ono sto se takodje moze desiti je da za neka pravila imamo istu levu stranu (antecedent), a razlicitu
desnu stranu (kosekvent). U tom slucaju imamo iste uslove koji vode ka 2 razlicita zakljucka, a to nam ne 
odgovara (jer ne mozemo da zakljucujemo).

Kako se u tom slucaju bira koje ce se pravilo zadrzati?  
Tako sto se izracuna stepen vazenja svakog pravila i onda se odabere ono pravilo koje ima veci stepen 
vazenja, a drugo pravilo izbacujemo iz baze znanja

To se radi tako sto se izmnoze sepeni pripadnosti atributa i labele (to su u stvari oni maksimumi primera).

Stepen vazenja se obelezava i kao `Degree` (npr. `Degree(Rule_1) = ...`)


Ono sto jos moze da se udradi je da se definise threshold tako da se sva pravila koja imaju stepen vazenja
manji od njega izbace iz baze znanja.


Proces generisanja pravila iz podatak zna da bude dosta problematican, tj. dosta je prisutan trial & error.

Najcesce se koriste genetski algoritam i neuronske mreze. Pored toga je moze da se odredi iskustveno 
(tj. da ekspert odredi), mogu da se koriste klasterizacione metode (na osnovu svakog atributa/labele se
vrsi klasterizacija i za to se obicno koristi FCM klaterizacija i ona obezbedjuje da 1 podatak ne mora
u potpunosti pripadati 1 klasteru vec moze biti pripadnik vise njih u nekoj meri)


Ono sto fuzzy sistem zakljucivanja ima sto ANN nema jeste objasnjivost. Pandan je stablu odlucivanja, po
pitanju objasnjivost, ali za razliku od njega ne koristi crisp numericke vrednosti koje mogu biti
problematicne za ljudsko rezonovanje jer jako bliski podaci mogu da se kategorisu u razlicite kategorije
pa nam omogucava da masinski rezonujemo onako kao to ljudi rade.

