# Prvi cas
jedan kol je ono sto se radi na predavanju  
drugi kol je ono sto bude radjeno na vezbama (u python-u)


fazi log na kol (preko nekog alata)
genetrski algoritam

treci deo je zasebna celina


zavrsni ispit: koncept + usmeno

za 9 i 10 ce se traziti projekat

---

Ljudima nije potrebno da se izrazavaju i komuniciraju 
preciznim "vrednostima"


Lofti Zadeh - moramo istraziti nasu toleranciju za nepreciznost
(moramo ispitati koliko smo sposobni da tolerisemo nepreciznost
u komunikaciji a da pri tome ne gubimo na rezultatima iz te 
komunikacije)


Mi u svakodnevnom zivotu komuniciramo preko vrlo nepreciznih jezickih
konstrukcija, ali opet se veoma dobro razumemo


Lofti je dobio ideju da tu nepreciznost ugradi u racunare

Ideja fuzzy logike je da se razumemo na prirodnom jeziku
(pretpostavljam sa racunarom)


Klasicna logika: ili je tacno nesto ili je netacno


Kod fuzzy logike postoji gradacija izmedju krajeva.

Granica izmedju 2 kategorije (npr) nije jasno definisana
vec se postepeno smanjuje efekat jedne osobine, i povecava
efekat druge (npr.)

U fuzzy logicki tacnost varira u zavisnosti od konteksta


Klasicna logika (preciznost u izrazavanju) je u nekim
oblastima neophodna.
Npr. hirurski roboti ili laserski zraci i sl.


Fuzzy logika moze jako da pomogne npr. kod autonomnog
upravljanja automobila

## Klasicna logika 

Klasicna (Bulovska) logika se jos naziva i **crisp**
(sto znaci jasan)

Bulovksa logika: tacno ili netacno (nema izmedju)

## Fuzzy logika

Fuzzy - nejasno / neodredjeno

Fuzzy logika ne znaci da je nejasna, vec je logika kojom
se opisuju neodredjenosti. U njoj je izraz tacan u
odredjenoj meri, ide od potpuno netacnog (0) do potpuno tacnog(1), 
dozvoljene su sve vrednosti izmedju


Problem kod Bulovske logike je to sto bi neki elementi pripadali
razlicitim kategorijama iako su dosta slicni (razlika izmedju njih
je veoma mala). To nije problem kod fuzzy logike jer je postoji
spektar vrednosti, odnosno koeficijenata pripadnosti ili tacnosti


Dosta se koristi u inzenjerstvu.

Fuzzy logika je jedna od oblasti vestacke inteligencije


Sistemi za podrsku u odlucivanju su jako bitan deo primene fuzzy 
logike jer omogucavaju podrsku na prirodnom jeziku

Ono sto modeli koji su zasnovani na fuzzy logici imaju kao prednost
u odnosu na modele koji su u masovnoj upoterebi jeste **explainability**,
tj. objasnjivost.

Neuronske mreze su npr. suprotno, blackbox, nema jasnog puta da se 
sazna kako je na osnovu ulaza doslo do izlaza.

Modeli fuzzy logike nisu samo explainable, vec su i dobro prilagodjeni
prirodnom jeziku, a takodje i omogucavaju da eksperti dodaju neka svoja
pravila do kojih su iskustveno dosli


Koristi se u detekciji outlier-a


## Kljucni delovi

Fuzzy logika se bavi ispitivanjem stepena tolerancije na nepreciznost
ishoda, tj. rezultata komunikacije

Opisuje nesto kroz stepen tacnosti, tj. vrednostima spektra koji ide od potpuno 
netacnog do potpuno tacnog

Ideju dao i opisao Lofti Zadeh 

Modeli fuzzy logike su explainable, a pored toga je korisno i to sto su prilagodjeni 
prirodnom jeziku


# Drugi cas

Kombinacijom fazi pravila moze da se rezonuje bez potrebe da se koristi potpuno
precizno znanje


Skupovi kod klasicne logike se crtaju kao venovi dijagrami


Za fuzzy skupove je karakteristicno to da ne postoji jasna granica koja odvaja
fuzzy skup od univerzalnog skupa, vec je granica "maglovita"


Kod klasicnih skupova se koristi **operator** pripadnosti. Kod fuzzy skupova on
ne moze da se koristi, vec se koristi **stepen** pripadnosti tom skupu.

Stepeni `0` i `1` mogu da se poistovete sa ponasanjem operatora pripadnosti.

Kod klasicnog skupa elementi koji mu pripadaju mogu da se nabroje, dok kod
fuzzy skupova to nije slucaj.

Pripadnost fuzzy skupu se odredjuje **funkcijom pripadnosti**. To se moze uraditi i
za klasican skup (ali to nije uobicajeno)

Elementi (prva koordinata) moraju da pripadaju univerzalnom skupu.


Univerzalni skup je skup svih mogucih vrednosti koje
posmatrana promenljiva moze da poprimi (da ima)

Funkcija pripadnosti se slika u skup `[0,1]`, tj.
`ni_A: U -> [0,1]`

Da bi se definisao fuzzy skup potrebno je da se definise
nad celim univerzalnim skupom.


Iako se koristi sintaksa za sumu i zbir ona nema originalno
znacenje vec predstavlja sintaksu kojom se opisuje grupisanje

Fuzzy skup se zapisuje kao:
- za diskretan i konacan domen
    `A = Sum_(x pripada U) ni_A(x)/x`

- za kontinualan i beskonacan domen
    `A = Int_(x pripada U) ni_A(x) / dx`

    

## Razlika izmedju stepena pripadnosti i verovatnoce

Stepen pripadnosti predstavlja stepen slicnosti necega
fuzzy skupu na osnovu njegovog opisa / svojstva


Kod verovatnoce se uzima **uzorak** i onda se na osnovu njega
vrsi brojenje elemenata/stvari sa tom osobinom
**"koliko cesto se pojavljuje neko svojstvo medju ispitanim
objektima"**

---

`>` - bolje  
`<` - gore (losije)

90% procenata sansa da je nesto sto nije opasno za pice (1.)  
<   
0.9 stepen pripadnosti necemu sto nije opasno za pice (2.)


(1.) od 90 flasa 10 flasa sadrze tecnost koja je opasna
za pice

(2.) tecnost izabrane flase je veoma blizu onome sto je potpuno bezopasno


50% verovatnoca > 0.5(stepen pripadnosti)
