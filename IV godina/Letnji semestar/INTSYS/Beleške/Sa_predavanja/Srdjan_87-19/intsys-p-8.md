# Genetski algoritam

Relativno jednostavan koncept / algoritam / mehanizam.

Nudi siroku oblast primene, razni problemi mogu da se rese
pomocu genetskih algoritama.

Kompleksnost lezi u samoj toj primeni, tj. u prevodjenju
problema iz neke oblasti na nesto sto ce moci biti reseno
koriscenjem genetskog algoritma.


Kao sto se moze zakljuciti iz naziva, inspirisan je
procesom u prirodi.

Predstavlja jedan primer optimizacionog algoritma.

Takvi algoritmi (inspirisani prirodom) za optimizaciju se
nazivaju **metaheuristickim algoritmima**.


Tvorac: Dzon Holand (John Holland) i njegov tim

Ideja je da se radi sa nekom kolekcijom kandidata za 
resavanje problema.


Krene se od mogucih resenja pa se onda proverava koliko su
dobra, a ona koja su pribliznija resenju dobijaju priliku 
da se dalje poboljsavaju, interativno, iz generaciju u 
generaciju, sve dok se ne dodje do najboljeg moguceg resenja
za problem.

## Inspiracija

Svi zivi organizmi se sastoje od celija.

Svaka celija ima skup hromozoma i on je isti u svakoj celiji.

Svaki **hromozom** je niz DNK (en. DNA) i od njih je formiran
citav organizam.

Svaki hromozom se sastoji od gena.

**Geni** kodiraju odredjene osobine.

Svaki gen ima poziciju u hromozomu i ona se naziva **lokus**

**Alel** je konkretna vrednost gena, tj. konkretna osobina
koja je iskodirana.

Hijerarhija:  
organizam > celija > hromozom > gen -> alel (varijacije/moguce vrednosti)


Genetski algoritmi su jedan tip evolucionih algoritama.

Svi evolucioni algoritmi se zasnivaju na prirodnom procesu
evolucije, ali su se genetski algoritmi pokazali kao najrobusniji
i najlakse primenljivi u resavanju realnih problema.


Proces evolucije podrazumeva da se od nekih jedinki
stvaraju druge jedinke kroz proces ukrstanja.

Time neka populacija postepeno prilagodjava svoje osobine
okruzenju u kome se nalazi, tako sto one jedinke koje su
se bolje snasle u tom okruzenju (imaju osobine koje im 
omogucavaju prezivljavanje) imaju vecu sansu da stvore 
potomstvo, cime se te osobine sire kroz populaciju


Pored ukrstanja i prilagodjavanja sredini, bitna je i
pojava mutacija. To su slucajne promene na genima koje 
dovode do neocekivanih osobina koje prethodnici odredjene
jedinke nisu imali. Time ta jedinka mutacijom dobija neku
novu osobinu. Ako se ona pokaze kao korisna onda ce se
ona preneti na potomstvo.

**Prilagodjenost organizma** predstavlja stepen prilagodjenosti
tog organizma sredini u kojoj se nalazi.


Pojedinci koji su najbolje prilagodjeni dobijaju najvecu
sansu da se uparuju i daju nove dobre jedinke

## Terminologija

**Populacija** predstavlja skup mogucih resenja problema

Recimo da problem mozemo da kodiramo pomocu `0` i `1`.

Nizom `0` i `1` mozemo da opisemo resenje tog problema. 
Ti nizovi moraju da imaju da imaju neko znacenje u 
kontekstu problema koji se resava. 

Taj niz se naziva **genotipom**, predstavlja skup svih gena.

**Fenotip** predstavlja preslikan genotip kome je dodeljeno
znacenje. 

Moramo da znamo kako potencijalno resenje problema 
predstaviti u nesto sto racunar moze da razume.

U primeru sa nizovima `0` i `1` gde svaki element
niza predstavlja nesto, svaki taj niz / resenje predstavlja
jedan hromozom. Hromozomi koji samo te vrednosti mogu da 
imaju za elemente se nazivaju binarnim hromozomima.

Jedna jedinka nam je jedan hromozom

U genetrskom algoritmu je jedna jedinka jedno resenje
problema (**kodirano**). 

Zasto je potrebno dekodiranje?  
Zato sto ne mozemo da utvrdimo koliko je resenje dobro.

Potrebno je izvrsiti tu procenu. Kvalitet resenja, odnosno
to koliko se jedinka dobro snasla u okruzenje je prilagodjenost
jedinke, tj. **fitness** (na en.).

To nam sluzi na za odredjivanje toga da li ce jedinka 
da siri svoj gen.

Taj fitnes se prevodi u verovatnocu.

Zatim vrsimo selekciju na osnovu te verovatnoce. Biraju
se jedinke koje ce da odu u proces reprodukcije.


Reprodukcija / ukrstanje / crossover se vrsi tako sto se
hromozomi roditelja podele na neke delove i onda zamene
mesta, cime se dobijaju nove jedinke koja predstavljaju
decu tih jedinki.

Imaju deo od prvog i deo od drugog roditelja.

Time se dobija resenje koje ima osobine oba roditelja.

U procesu selekcije postoji mogucnost i da se definise
prag koji treba da se predje da bi se islo u reprodukciju.
To se zove **crossover probability** i predstavlja jedan
hiperparametar ovog algoritma koji treba da se odredi 
(trial & error se primenjuje)

Nakon kreiranja novih jedinki moze da dodje do mutacije.
To u ovom primeru znaci da se neki bit izmenio (`1` u `0` ili
obrnuto). To se naziva **bit flip mutacija**. 

Mutacije povecavaju raznovrsnost populacije i povecavaju
beg iz lokalnih minimuma, tj. obezbedjuje da se ne desi
da citava populacija kroz proces selekcije i ukrstanja
konvergira ka jednoj tacki.
 
Kod mutacija takodje mozemo nesto da biramo, a to je 
verovatnoca kojom ce se mutacija desiti. Najcesce je to
`1 / broj_jedinki_populacije`. Ovo je drugi hiperparametar
genetskog algoritma.
 
Postoji deo jedinki koje idu direktno u narednu populaciju,
ne ukrstaju se i ne mutiraju. To se naziva **litizam**.
Time se zadrzavaju najbolje jedinke i ne dozvoljava se 
da one propadnu kroz te procese.

Nakon zavrsetka procesa mutacije mi smo formirali novu
generaciju.

Sada se vraca na pocetak kako bi se ocenila prilagodjenost
nove generacije i sve tako u krug.

Koraci:
1. generisanje slucajno odabranih (?) jedinki
2. odredjivanje fitnesa
3. selekcija
4. ukrstanje
5. mutacija
6. dodavanje potomaka u populaciju potomaka
7. -> 2.


Kada se staje?  
Najcesce kada se dodje do predefinisanog broja generacija.
Moze i kada se dodje do resenja (kod problema za koje se 
moze jasno odrediti sta je tacno resenje) ili kada
se u poslednjih n generacija resenje nije poboljsalo
za x%


Funkcija cilja je nesto sto zelimo da nasim resenjem 
bude zadovoljeno.


Populacija je skup jedinki, tj. skup mogucih resenja 
problema. Generacija je jedan prolaz kroz petlju 
algoritma.

## Primena GA

###  Kodiranje i dekodiranje

Pri prevodjenju problema u hromozom mi vrsimo kodiranje.

Obrnuti proces, tumacenje hromozoma, je dekodiranje. 

Kodiranje u kome se koriste samo `0` i `1` se naziva
birano kodiranje. To nije jedini nacin kodiranja.


Unapred se definise duzina hromozoma tako se se proceni
heuristicki kolika bi bila maksimalna duzina za dati problem.


Drugi nacin za kodiranje je da se koriste celi brojevi.
On se koristi npr. kod problema trgovackog putnika.

U tom slucaju bi koristili permutacijski hromozom kod koga se
isprobavaju razlicite permutacije konacnog broja celih brojeva.

Treci vid kodiranja je realni hromozom. On se sastoji od
odredjenog niza realnih brojeva. Ta vrsta hromozoma se 
najcesce primenjuje kod realnih problema i inzinjerstvu.


Kada kodiramo resenje / problem moramo da znamo sta koji
gen predstavlja.

Gen dodje kao neka promenljiva, a alel kao vrednost koja
moze da bude dodeljena toj promenljivoj.

### Fitness funkcija

Nakon kodiranja sledi kreiranje fitness funkcije.

Ona treba da kaznjava resenja koja su losa, a nagradjuje
resenja koja su dobra.


### Odabir jedinki

Za svaku jedinku pre svega treba da se odredi verovatnoca 
kojom ce ona da ide u ukrstanje.

Ta verovatnoca treba da bude srazmerna fitnesu jedinke.

Da bi se to odradilo potrebno je da se fitnes na neki nacin
mapira u opseg `[0,1]` posto vrednosti fitnesa mogu
biti i izvan ovog opsega. To mozemo da odradimo deljenjem
sumom svih fitnesa. Zasto? Zato sto za svaku jedinku
trebamo da odredimo fitnes i koji je udeo svake u toj 
sumi. Time se moze izvesti ova verovatnoca. Dobijena
vrednost ce uvek biti u opsegu `[0,1]`.

To moze i da se zamisli kao skaliranje svakog fitnesa
na *spinning wheel*-u, gde suma svih tih fitnesa predstavlja
ceo tocak.

Proces selekcije moze da se zamisli kao okretanje ovakvog
tocka koji ima jednu strelicu koja ce pokazivati na 
odabranu jedinku kada se okretanje zaustavi. Svaki deo 
predstavlja jednu od jedinki. One koje imaju veci fitnes
ce time imati vecu sansu da budu izabrane jer ce okupirati
veci deo tocka.

Ovakva selekcija se naziva **roulette wheel** selekcija.

Kod ovog nacina izbora prostoji problem ukoliko sve 
jedinke imaju relativno iste vrednosti fitnesa.

To se resava rangiranjem na osnovu fitnesa. Time oni 
koji imaju veci rang ce imati vecu verovatnocu za 
ulazak u proces ukrstanja.

Pored ove 2 selekcije postoji i **turnir selekcija**.
Funkcionise kao turnir. Dve jedinke se "sukobljavaju" i
ocenjuje se koja ima veci fitnes. Ona koja ima veci fitnes
ce nastaviti dalje da ucestvuje u turniru, a ona koji ima 
manji fitnes ce ispasti iz turnira. Pobednik se dalje
sukobljava sa drugim pobednikom i to se tako ponavlja 
sve dok se ne dodje do 1 jedinke. 

Ovom selekcijom se postepeno odbacuju jedinke koje su manje
kvalitetne.

Ovaj proces se ponavlja vise puta dok se ne napravi pool 
roditelja za proces ukrstanja.

### Ukrstanje

Prethodno smo spomenuli ukrstanje u jednoj tacki koje 
se naziva **one-point crossover**. Ono podrazumeva izbor 
tacke u kojoj ce se izvrsiti ukrstanje. To zavisi od
problema koji se resava.

> Genetski algoritam je samo jedan nacrt kako da pristupite resavanju problema

Mozemo da imamo situaciju gde odredjeni broj gena predstavlja
jedan deo, jednu logicku celinu, a neki drugi deo neku drugu i tako dalje. Tada 
ne mozemo tek tako samo da odaberemo bilo koju tacku.

Ne mora postojati samo 1 tacka ukrstanja, moze ih biti i 
vise, ali ne treba preterivati sa time jer to onda dosta
lici na nasumicno kreiranje pa se gubi smisao procesa.

Ovaj crossover (ukrstanje) ne radi kod realnih hromozoma.

Pored tog ukrstanja postoji i **uniformno ukrstanje**. 
Ono podrazumeva da se za svaki gen razmotri od kog 
roditelja ce biti uzet.

### Mutacija

Obezbedjuje raznolikost populacije i to da ne dodje do
zaustavljanja u lokalnim minimuma.


Pored bit flip mutacije postoji i **swap mutacija**. Ona 
se koristi kod permutacijskih hromozoma jer mozemo da 
izgubimo neke informacije ili uvedemo nepravilnosti.
Na primer kod problema trgovackog putnika odredjuje se 
redosled kojim treba da obidje gradove. Ako se nasumicno
promeni neki broj moze da se dogodi da neki grad ne obidje,
a da neki drugi obilazi vise puta (`1234` se pretvori u 
`1232`). 

Kod swap mutacije promena bi izgledala ovako:
```
1234 -> 1324
```


 





