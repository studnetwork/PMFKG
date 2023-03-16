Kao ulaz u neki fuzzy sistem mogu da se koriste crisp vrednosti

Ako bismo zeleli da omogucimo toleranciju na greksu onda
bi bilo potrebno da dozvolima mala odstupanja od neke
vrednosti.  
Time bi se izvrsila fazifikacija

Najjednostavniji nacin fazifikacije jeste fazifikacija
sa trougaonom funkcijom pripadnosti. Za datu vrednost
se doda odstupanje i dobije se jednokraki trougao 


U ovom slucaju samo 1 vrednost ima stepen pripadnosti 1.
Realnija varijanta je mozda "zvonasta" / kriva funkcija,
odnosno distribucija ulaznih vrednosti


Ako imamo situaciju da merimo nesto sa nekim uredjajem
stepen pripadnosti se moze odrediti na 2 nacina

1. preko crisp vrednosti koja je ucitana, ta vrednost se samo
   slika na osnovu funkcije pripadnosti
2. ucitana vrednost se fazifikuje, npr. dodamo toleranciju
   a nakon toga kao stepen pripadnosti uzimamo maksimum
   preseka tog fazifikovanog skupa i nekog drugog skupa 
   
   
# Lambda odsecak 

Skupu lambda_A pripadaju svi x-ovi za koje je 
`funkPrip_A(x) >= lambda`


stepen pripadnosti je vrednost izmedju 0 i 1


Svaki fazi skup ima beskonacno mnogo lambda-odsecaka


lambda odskecak dodje kao skup svih x-ova takvih
da je njegova slika veca od lambda.
manje vise dodje kao odsecak originalnog tako
da se uzima samo njegov deo od lambde kao najmanje vrednosti
pa tako sve do kraja



`+` u lambda `0+` predstavlja neku malu vrednost blisku nuli

`(!A)_lambda = !(A_lambda)` samo za `lambda = 0.5`


Ako imamo neku vrednost x takvo da je `x >= lambda` i da 
x pripada `[0, 1]` onda vazi da je `A_x` podskup od `A_lambda`


# Definisanje delova fazi skupa sa lambda odseckom

`core(A) = A_1`

`support(A) = A_0+`

`boundary(A) = (A_0+, A_1)`


# Defazifikacija

Proces u kome se fazi skup prevodi u jednu numericku vrednost

Postoji vise razlicitih metoda, nije svaka pogodna za
svaki oblik fazi skupova jer mogu da daju pogresnu vrednost
ako se ne biraju pazljivo


## Srednja vrednost maksimuma (Mean of Maxima - MOM)

Koristi se kada postoje peak-ovi (ugl. kada ih ima vise)

"Metod defazifikacije koji se vodi maksimumom"

Posmatra samo one tacke iz U ciji je stepen pripadnosti 
jednak visini datog skupa

Ako postoji samo 1 takva tacka onda je ona rezultat
defazifikaciju, a ukoliko ih ima vise onda se trazi
prosecna vrednost svih tih tacaka


## Centroid (center of gravity)

Koristi se kada fazi skup moze da se podeli na vise figura
za koje mozemo lako da nadjemo teziste


Z^* = 
zbir proizvoda tezista i povrsine svake figure 
/
zbir povrsina svake figure


## Metoda ponderisanog proseka (weighted average method)

Zahteva postojanje simetricnosti 

ponderise == mnozi

vrednost se dobija tako sto se prvo odradi suma
proizvoda tacke u odnosu na koju postoji simetricnost i
njene slike (pripadnosti), a zatim ta suma podeli sa
sumom slika spomenutih tacaka


Ako imamo 2 skupa, A i B koji su simetricni u odnosu na
tacke a i b respektivno, i ako je 
`fun_prip_A(a)=0.5; fun_prip_B(b)=0.9` onda se rezultat
dobija na sledeci nacin:
```
z^* = (a*0.5 + b*0.9) / (0.5 + 0.9)
```

# Lingvisticke promenljive

Najbitniji pojam u fuzzy logici posle fuzzy skupa

To su promenljive koje kao vrednost uzimaju reci ili
recenice prirodnog jezika
(domen su reci/recenice)


Da bi se definisala jedna ovakva promenljiva potrebno je
definisati:
- (njen) naziv
- terme (vrednosti; to su neki termini)
- podskup vrednosti nekog skupa za koji se definisu termi



## Modifikatori lingvistickih vrednosti

Izrazi prirodnog jezika kojima se menjaju osnovne
lingvkisticke vrednosti

Primeri: a little, slightly, very, extremly, more or less


## Slozeni termi

Omogucavaju povecanje ekspresivnosti 

Pomocu logickih veznika mozemo da povezujemo i kreiramo
slozenije terme
