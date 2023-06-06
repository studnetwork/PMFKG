Dekartov proizvod skupova `A` i `B` je skup uredjenih parova takvih da je
prvi element para iz `A`, a drugi element para iz `B`.

Npr:
```
A = {a, b, c}
B = {1, 2}

Dekartov_proizvod = A x B = { 
                      (a, 1), (a, 2),
                      (b, 1), (b, 2),
                      (c, 1), (c, 2)
                    }
```

Moze i da se uopsti pa da se radi sa uredjenim n-torkama umesto parovima.

Npr. `A x B x C x D`

Imati u vidu da nije komutativno, tj. `A x B != B x A`

Moze se raditi i nad istim skupom, npr. `A x A`

# Jasne relacije

Klasicna ili jasna relacija je podskup Dekartovog proizvoda. 

Jos moze da se kaze da su crisp relacije.

Kaze se da su odredjene n-torke u relaciji `R`

Kod ovakvih relacija elementi ili jesu ili nisu u relaciji:
```
hi_R(x, y) = {1 ako (x,y) pripada R; 0 ako (x, y) ne pripada R}
```

Ovo predstavlja **jacinu relacije**. Kada n-torka pripada relaciji onda
njeni elementi imaju jacinu relacije `1`, a ako ne pripada (ako nisu u relaciji) `0`


## Kompozicija jasnih relacija

Neka je `R` relacija koja slika skup `X` u skup `Y`, tj. `R: X->Y`. 
Neka je i `S` relacija koja slika skup `Y` u skup `Z`, tj. `S: Y->Z`.

Kompozicija relacije je relacija koja se dobija kada se uspostavi
veza izmedju elemenata skupa `X` i elemenata skupa `Z`.


Komponuju se relacije `R` i `S` kako bi se pronasla nova relacija koja ce
da slika elemente skupa `X` u skup `Z`

Obradicemo 2 nacina za vrsenje kompozicije relacija:
1. Max-min kompozicija
2. Max-proizvod kompozicija

### Max-min kompozicija

Definise se preko jacine kompozicije (kompozicija je isto relacija).

Jacina dobijene relacije nakon sto se izvrsi kompozicija je jednaka
maksimumu minimuma jacina relacija `R` i `S`, tj.
```
T = R kruzic S

hi_T(x, z) = max( min( hi_R(x,y), hi_S(y,z) ) )  # radi se za svaku kombinaciju
```

Ako imamo vise paralelno spojenih lanaca u jedan i krenemo da vucemo jedan
kraj u suprotnom smeru od drugog onda ce prvo doci do pucanja najslabije
karike u najslabijem lancu, pa do sledeceg najslabijeg lanca sve do
poslednjeg kod koga ce takodje doci do pucanja na najslabijoj karici.

Ako bismo zeleli da vidimo koliko ce izdrzati taj lanac, mi bismo prvo
odredili za svaki koliko je jaka njegova najslabija karika (u formuli je to deo 
gde se trazi `min`), a onda bismo pronasli koja ce od svih njih najduze izdrzati
(u formuli `max` deo) i to bi predstavljalo ujedno i izdrzljivost citavog slozenog lanca.


Relacije se mogu prikazati na 3 nacina, kao:
1. **skupovi** (uredjenih n-torki)
2. **matrice** (gde vrste predstavljaju el. jednog skupa, a kolone el. drugog skupa
   dok se u njihovom preseku nalazi jacina relacije izmedju tih elemenata)
3. **medjusobno povezane tacke** (lici na graf)


Ovaj metod izvodjenja kompozicije lici na postupak mnozenja matrica, s tim sto 
se umesto mnozenja trazi minimum izmedju tih vrednosti, a umesto sabiranja
se trazi maksimum tih minimuma. Ta vrednost se na kraju pise na odgovarajuce
mesto u rezultujucom matrici, isto kao i kod mnozenja matrica.


Ovo dodje i kao neka tranzitivnost, sto moze bolje da se primeti na prikazu
relacija u vidu medjusobno povezanih tacaka.

### Max-proizvod kompozicija

Isto kao max-min, samo se umesto trazenja minimuma vrsi mnozenje

# Fuzzy Dekartov proizvod

Kao sto je Dekartov proizvod klasicnih relacija takodje relacija tako je i
Dekartov proizvod fuzzy skupova takodje fuzzy skup, a kao takav onda mora 
da ima definisan i stepen pripadnosti za svaki element.

Stepen pripadnosti elementa fuzzy Dekartovog proizvoda se moze izracunati kao:
```
mi_AxB(x,y) = min(mi_A(x), mi_B(y))
```

odnosno, kao minimum izmedju stepena pripadnosti svakog elementa n-torke
njegovom domenu, tj. fuzzy skup kome pripada.

Fuzzy skupovi se uvek mogu zapisati u matricnom obliku.

Definisanjem Dekartovog proizvoda fuzzy skupa mi dobijamo u stvari fuzzy relaciju.

# Fuzzy relacija

Fuzzy relacija slika Dekartov proizvod u segment `[0,1]`. Za razliku od
klasicnih relacija kod kojih je jacina relacije takva da su torke ili u relaciji
ili nisu (`0` ili `1`) ovde imamo spektar vrednosti, tj. stepen pripadanja
relaciji zbog neodredjenosti koju imamo u fuzzy logici.


Cim se formira Dekartov proizvod fuzzy skupova formira se i relacija izmedju njih.

Zasto?  
Kod crisp relacija potrebno je da se definise koje n-torke su deo relacije,
one imaju jacinu relacije `1` dok sve ostale n-torke imaju jacinu relacije `0`.
Kod fuzzy relacija mi vec imamo to definisano. Stepen pripadnosti Dekartovog
proizvoda (ima ga jer je fuzzy skup) je u stvari i jacina relacije izmedju
datih elemenata n-torke.


# Kompozicija fuzzy relacija

Isto kao i kod crips relacija.

Moze da se koristi npr. kada hocemo da iskoristimo postojecu relaciju
za predvidjanje necega (pretpostavimo da ta relacija postoji pa onda na
osnovu toga za jedan deo podataka dobijemo druge jer bi trebali da budu u 
istoj relaciji kao i podaci na osnovu kojih se doslo prvobitno do relacije)

Redosled navodjenja skupova moze da se laske prepozna ako se ima u vidu sledece:
```
X_axb     # matrica `X` sa `a` vrsta i `b` kolona
Y_cxd     # matrica `Y` sa `c` vrsta i `d` kolona

mora da vazi: b == c
```
