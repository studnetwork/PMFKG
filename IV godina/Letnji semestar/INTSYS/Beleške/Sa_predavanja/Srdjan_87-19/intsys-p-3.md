Kao ulaz u neki fuzzy sistem mogu da se koriste crisp vrednosti

Ako bismo zeleli da omogucimo toleranciju na gresku onda
bi bilo potrebno da dozvolimo mala odstupanja od neke
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
   a nakon toga kao stepen pripadnosti uzimamo maksimum (visinu)
   preseka tog fazifikovanog skupa i nekog drugog skupa 
   
   
# Lambda odsecak 

Skupu `lambda_A` pripadaju svi x-ovi za koje je 
`funkPrip_A(x) >= lambda`


Stepen pripadnosti je vrednost izmedju `0` i `1`


Svaki fazi skup ima beskonacno mnogo lambda-odsecaka


Lambda odsecak dodje kao skup svih x-ova takvih
da je njegova slika (stepen pripadnosti) veca od lambda.
Manje-vise dodje kao odsecak originalnog tako
da se uzima samo njegov deo od lambde kao najmanje vrednosti
pa tako sve do kraja

Neka uproscena definicija bi bila:  
Lambda odsecak skupa `A` predstavlja fuzzy skup koji se dobije
kada se svakom `x` za koje je stepen pripadnosti veci od `lambda`
dodeli stepen pripadnosti `0` (i time se odstrani deo boundary-a)

![alpha cut](https://www.researchgate.net/profile/Niladri-Dash-2/publication/331035257/figure/fig2/AS:725358710116356@1549950401485/Triangular-form-and-alpha-cut-of-membership-function-The-classification-method-proposed.ppm)


`+` u lambda `0+` predstavlja neku malu pozitivnu vrednost blisku nuli

`(!A)_lambda = !(A_lambda)` samo za `lambda = 0.5`


Ako imamo neku vrednost `t` takvo da je `t >= lambda` i da 
`t` pripada `[0, 1]` onda vazi da je `A_t` podskup od `A_lambda`

To u stvari znaci da je lambda odsecak sa vecom vrednoscu podskup 
lambda odsecka sa manjom vrednoscu.

# Definisanje delova fazi skupa sa lambda odseckom

`core(A) = A_1`

`support(A) = A_0+`

`boundary(A) = [A_0+, A_1)`


# Defazifikacija

Proces u kome se fazi skup prevodi u jednu numericku vrednost

Postoji vise razlicitih metoda, nije svaka pogodna za
svaki oblik fazi skupova jer mogu da daju pogresnu vrednost
ako se ne biraju pazljivo


## Srednja vrednost maksimuma (Mean of Maxima - MOM)

Koristi se kada postoje peak-ovi (ugl. kada ih ima vise)

> "Metod defazifikacije koji se vodi maksimumom"

Posmatra samo one vrednosti iz `U` (univ. skupa) ciji je stepen pripadnosti 
jednak **visini** datog fuzzy skupa

Ako postoji samo 1 takva vrednost onda je ona rezultat
defazifikaciju, a ukoliko ih ima vise onda se trazi
prosecna vrednost svih tih tacaka

Kada fuzzy skup nije simetrican daje istu vrednost nakon defazifikacije
kao i metode koje "vuku" ka centru

## Centroid (Center Of Gravity - COG)

Racunamo tako sto radimo odredjeni integral od jedog dela fuzzy skupa
do drugog (od tacke do tacke za svaki deo), u sustini za svaku figuru
koja ga cini. Unutar integrala se nalazi `x * df`, gde je `df` dobijena
funkcija koja predstavlja dati deo fuzzy skupa (uglavnom su to
prave linije, kose ili paralelne sa osom univerzalnog skupa, pa 
mozemo da dodjemo do njihove funkcije koriscenjem jednacine prave
sa 2 tacke). Mi u sustini imamo fuzzy skup koji mozemo da posmatramo kao 
funkciju i onda tu funkciju podelimo na delove (po jednostavnim figurama)
i onda integraljenjem tih delova funkcije dobijamo citavu povrsinu ispod
tog dela.

Formula:  
Z<sup>*</sup> = integral_za_svakog_dela(x * df(x) * dx)
/ 
integral_za_svakog_dela(df(x) * dx)

---

Pojednostavljena verzija:  
Z<sup>*</sup> = 
zbir proizvoda tezista i povrsine svake figure 
/
zbir povrsina svake figure


Ova verzija se koristi **samo** kada fazi skup moze da se podeli na vise figura
za koje mozemo lako da nadjemo teziste


## Metoda ponderisanog proseka (Weighted Average Method)

Zahteva postojanje simetricnosti 

ponderise == mnozi

Vrednost se dobija tako sto se prvo odradi suma
proizvoda x-a u odnosu na koji postoji simetricnost i
njegove pripadnosti, a zatim ta suma podeli sa
sumom pripadnosti tih x-ova


Ako imamo 2 skupa, A i B koji su simetricni u odnosu na
x vrednosti a i b respektivno, i ako je 
`fun_prip_A(a)=0.5; fun_prip_B(b)=0.9` onda se rezultat
dobija na sledeci nacin:  
Z<sup>*</sup> = (a*0.5 + b*0.9) / (0.5 + 0.9)

# Lingvisticke promenljive

Najbitniji pojam u fuzzy logici posle fuzzy skupa

To su promenljive koje kao vrednost uzimaju reci ili
recenice prirodnog jezika
(domen su reci/recenice)


Da bi se definisala jedna ovakva promenljiva potrebno je
definisati:
- (njen) naziv
- terme (vrednosti; to su neki termini)
- "podskup vrednosti nekog skupa za koji se definisu termi" (sa predavanja) | univerzalni skup (pdf)



## Modifikatori lingvistickih vrednosti

Izrazi prirodnog jezika kojima se menjaju osnovne
lingvisticke vrednosti

Primeri: a little, slightly, very, extremly, more or less


## Slozeni termi

Omogucavaju povecanje ekspresivnosti 

Pomocu logickih veznika mozemo da povezujemo i kreiramo
slozenije terme
 
