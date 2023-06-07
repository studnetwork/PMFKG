Pri odredjivanju Dekartovog proizvoda moze doci do toga da nam ne odgovara 
matrica (zbog dimenzija). Ako dodje mi mozemo da je transponujemo i time
dobijemo odgovarajucu dimenziju za tu operaciju (nije neko pravilo vec 
se samo napominje kao mogucnost)

Relacija implikacije u fazi logici se definise isto kao i klasicna relacija.


# Predstavljanej fazi pravila preko fazi relacija

`A` je fazi skup definisan nad univerzalnim skupom `X`  
`B` je fazi skup definisan nad univerzalnim skupom `Y`

## Prvi tip

```
IF x is A THEN y is B
```

Fazi relacija implikacije se moze definisati sa:
```
R = (A x B) u (!A x Y)
```

`u` predstavlja uniju

Stepen pripadnosti za ovaj fuzzy skup (implikaciju) se racuna sa:
```
mi_R(x,y) = max[mi_A(x) ^ mi_B(y), 1 - mi_A(x)]
```

`^` predstavlja simbol/operator za minimum (`a ^ b` == `min(a,b)`)

## Drugi tip

`C` je definisano nad skupom `Y`

```
IF x is A THEN y is B ELSE y is C
```

Fazi relacija implikacije se u ovom slucaju moze definisati sa:
```
R = (A x B) u (!A x C)
```

Stepen pripadnosti za ovaj fuzzy skup (implikaciju) se racuna sa:
```
mi_R(x,y) = max[mi_A(x) ^ mi_B(y), (1 - mi_A(x)) ^ mi_C(y)]
```

# Kreiranje fazi implikacije i zakljucivanje

Posto u formulama imamo univerzalne skupove potrebno je da i njih
predstavimo kao fazi skupove.

To radimo tako sto svakom elementu dodelimo stepen pripadnosti `1`

Kada formiramo matricu na osnovu formula u prethodnim sekcijama
onda mozemo da iscitamo stepen vazenja implikacije za svaku kombinaciju
elemenata iz `A` i `B` (u celiji koja se nalazi u njihovom preseku
se nalazi ta vrednost)

Na osnovu te matrice implikacije dalje mozemo da rezonujemo.
U ovom slucaju u kome se na osnovu `A` implicira `B` mozemo da
definisemo drugi fazi skup nad `A` i da onda vrsimo nekakvu
predikciju odnosno zakljucivanje.

# Zakljucivanje sa diskretnim ulazima

U prethodnoj sekciji je spomenuto kako se vrsi zakljucivanje kada imamo
fuzzy skup kao ulaz (definisan nad `A`). Postavlja se pitanje sta se 
radi kada ulaz nije fuzzy skup vec diskretna (crisp) vrednost?

Radi se isto ono sto se radilo i vizuelno: za date vrednosti se
nadje njihov stepen pripadnosti odgovarajucem fuzzy skupu i onda se
trazi min (max) ukoliko se izmedju njih nalazi `AND` (`OR`) operator i
dobijeni stepen pripadnosti predstavlja stepen vazenja zakljucka

# Kraj 

Ovime smo obradili graivo koje opisuje citav sistem/proces za zakljucivanje.
Ono sto je preostalo da se obradi jeste to kako ovaj proces automatizovati.

Neki delovi se mogu automatizovati, npr. odredjivanje koji su fazi skupovi
potrebni i pravila, a neki ne mogu, npr. metod zakljucivanja i metod 
defazifikacije.

U sustini automatski moze da se generise baza znanja.

Genetski algoritam je jedna od metoda koja moze posluziti za to generisanje.
