kosa linija kod trapeznog oblika se racuna preko jednacine prave
(jer je to obicna prava linija)

singltoni su najjednostavniji oblik
potpuno diskretan domen
prikazuju se stubicima (kao barplot)

fuzzy logika se uglavnom koristi u kontrolerskim sistemima

**napomena**: kada imamo vise skupova oni ne moraju da pocinju tamo gde se prethodni zavrsavaju
(tj. da tacka u kojoj se zavrsava jedan bude tacka u
kojoj pocinje drugi skup)

u inzenjerskoj primeni najcesce se koriste **trougaone** f-je pripadnosti, npr. za gresku u merenju,
tj. toleranciju greske

Fazi skup obuhvata i vrednosti za koje je stepen pripadnosti `0`

# Karakteristike f-je pripadnosti (FP)

**core** (jezgro): svi `x`-ovi za koje je `FP(x) = 1`  
**support**: svi `x`-ovi za koje je `FP(x) > 0`  
**boundary** (granice): svi `x`-ovi za koje vazi `0 < FP(x) < 1`  

**visina fuzzy skupa** je vrednost za koju FP ima maksimalnu vrednost 

fuzzy skup nije normalan ako nema x takvo da vazi `FP(x) = 1`.

U fazi zakljucivanja se mogu dobiti skupovi koji nisu normalni

## Centar 

**centar fuzzy skupa** je srednja vrednost svih x-ova datog skupa za koje vazi `FP(x) = max(svih pripadnosti datog skupa)`   
**Napomena**: centar ne mora da bude deo core-a

ako jedna strana fazi skupa ide u beskonacnost onda se za centar uzima ona tacka koja
je najbliza kosoj liniji (tj. boundary-u)


## Konveksnost i konkavnost

suprotno od konveksnog fuzzy skupa nije konkavni fuzzy skup vec skup koju nije konvesan.

isto vazi i za konkavni.

konveksan ako za svake dve tacke postoji treca cija je pripadnost veca od pripadnosti neke od te 2 tacke

```
FP_A(lambda * x1 + (1-lambda) * x2) >= min(FP_A(x1), FP_B(x2))
```

ovo treba da vazi za svako `lambda` iz `[0,1]` i svako `x1`, `x2` iz univerzalnog skupa

za sta nam sluzi lambda?

za skaliranje ove 2 vrednosti tako da dobijemo vredonst izmedju njih  
(ovo nam je bitno zbog zapisivanje, a ne za prakticnu primenu)

## Operacije nad skupovima

**Unija** 2 fuzzy skupa se formira tako sto se uzima **veca** od 2 pripadnosti za svaku x vrednost 
(npr. za x=3 fazi skup A ima FP = 10, a fazi skup B FP = 11;
u tom slucaju ce skup koji predstavlja uniju imati pripadnost
11 za x=3)

Za **presek** je suprotno, uzi na se **minimum**

**Komplement**: `fp_k = 1 - fp(x)`

**Slicnost fuzzy skupova**: `S(A, B) = visina(preseka A i B) / visina(B)`
