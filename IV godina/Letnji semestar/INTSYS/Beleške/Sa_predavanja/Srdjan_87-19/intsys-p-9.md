Nasumicno generisana pocetna populacija ne moze da se koristi pri resavanju
svih realnih problema.

Litizam - prenos najboljih jedinki (one se i prenose u narednu populaciju i
ucestvuju u ukrstanju)


Funkcija cilja je za pojedine probleme isto sto i fitness funkcija, a za
neke nije.

Funkcija cilja govori o tome koliko smo blizu resenju problema. Trudimo se
da je minimizujemo ili maksimizujemo kako bismo dosli do resenja. 

 
Do sada smo radili sistematicno pretrazivanje prostora pretrage. Kod njih 
smo isli od stanja do stanja, primenom nekih akcija, i usput pamtili put
kojim smo dosli do resenja. Nisu svi problemi takvi. Za neka nam nije 
bitno da znamo koji smo tok resavanja imali, vec samo sta je konacno resenje.


Pocetno stanje ne mora da bude odredjeno. Zelimo da nadjemo samo jedno resenje.

"Imate probleme koji nemaju tacno jedno resenje, vec imaju masu dobrih resenja, a
vas zanima da pronadjete samo 1."

Ciljna funkcija je funkcija koja procenjuje kvalitet resenja, tj. koliko je
dobro to nase resenje. 


Pri primeni genetskog algoritma mi u svakoj iteraciji moramo da procenimo koliko
su nam dobra resenja. Ciljna funkcija moze da bude i isto sto i fitnes.

Kada gornja i donja granica nisu jasno uocljive, genetski algoritam prekidamo 
kada u nekom broju uzastopnih generacija mi ne pronadjemo bolje resenje.

Drugi nacin je da se iskustveno predefinise broj generacija do kojeg ce da se
dodje, ali to je nekada dobro, nekada nije.

Kada evaluiramo performanse genetskog algoritma mi kroz generacije pratimo
vrednost najboljeg resenja, vrednost najgoreg resenja i prosecnu vrednost 
fitnesa u generaciji.


Kada se pravi implementacija genetskog algoritma najcesce se radi tako sto 
se trazi ili minimum ili maksimum u generaciji (jedno moze da se svede na drugo).

Fitnes nije uvek isto sto funkcija cilja. U implementaciji mozemo npr. da uzmemo
kao funkciju cilja uzmemo reciprocnu vrednost fitnes funkcije i tako maksimizujemo
fitnes, a minimizujemo ciljnu funkciju.

S obzirom da se manje-vise ista stvar koristi postavlja se pitanje zasto postoji
potreba sa obe funkcije. Takva jeste situacija kod vecine jednokriterijumskih
problema. U realnosti postoji mnogo problema koji su visekriterijumski i oni su
obicno takvi da se optimizacija izvrsi tako da zelimo da maksimizujemo (ako je
vise == bolje) sve kriterijume pa je tada obicno potrebno doci do sto vece koristi
preko nekog kompromisnog resenja.

 

Jedan od najjednostavnijih problema koji moze da se resi genetskim algoritam je
max-one problem u kome zelimo da odredimo maksimalan broj jedinica u binarnom
stringu. Najcesce se koristi za testiranje implementacije genetskog algoritma.


Racunanje verovatnoce ukrstanja na osnovu fitnesa jedinke:
```
p_i = fitness(i) / suma_svih_fitnessa
```

Kada ovako raspodelimo opsege jedinki mi osiguravamo da ce one jedinke koje su 
bolje imati vecu verovatnocu za ukrstanjem od onih koje su losije, koje ce
imati zauzimati manji opseg pa u skladu sa tim imati i manju verovatnocu.

---

Sada kada imamo izabrane jedinke za ukrstanje mi necemo odmah samo izvrsiti
njihovo ukrstanje vec ce se to odraditi sa odredjenom verovatnocom, tj.
na osnovu crossover rate-a. Uzima se nasumican broj pa se proverava da li
je veci ili ne u odnosu na crossover rate.


Pri kodiranju se moze dogoditi da imamo viskove, tj. vrednosti koje nisu
prihvatljive (npr. imamo binarne vrednosti za brojeve od 1-8 i tada
nam sve vece vrednosti nisu prihvatljive jer nisu ispravne opcije za dati
problem). Takvim resenjima se daje najgori moguci fitnes kako se ne bi
uzimala u obzir.
 
Ukrstanje moze i da se vrsi tako da se pozicija ukrstanja slucajno 
odabira za svaki par. To zavisi od problema, kod nekih je moguce, kod 
nekih nije.


Binarno kodirani hromozomi ne moraju da se dekodiraju u cele brojeve, mogu 
i u realne pomocu sledece formule:
```
C_i = C_min + b / (2^L - 1) * (C_max_i - C_min_i)
```

`i` - i-ta jedinka populacije (hromozom)  
`C_i` - realni broj koji je dat binarnim zapisom  
`C_min` - donja granica za ono sto se dekodira  
`b` - dekadna vrednost binarnog broja  
`L` - duzina dela hromozoma koji predstavlja realni broj koji je binarno 
      kodiran (nije duzina celog hromozoma)  
`C_max_i` - maksimalna vrednost  


Primer:  
Neka su 2 realna broja, `8` i `10`, kodirana binarnim hromozom od 10 gena: `01000 01010`

Prevodjenje prvog broja:
```
L = 5                 # jer 01000
C_min = C_min_i = 5   # pretpostavimo da je to minimum za ono sto opisujemo ovim delom
C_max_i = 10          # maksimalna vrednost za to sto opisujemo
b = 8                 # (0100)_2 => (8)_10

C_x = 5 + 8 / (2^5 - 1) * (10 - 5) = 5 + 8/31 * 5 = 6.29
```


Ako jedinka ne zadovoljava ogranicenja ona mora da se kazni preko fitnesa. To 
moze da se uradi tako sto se da maksimalna vrednost za taj opseg ukoliko se vrsi
minimizacija, ili minimalnu vrednost za dati opseg ako se vrsi maksimizacija
(npr. kada se radi sa realnim vrednostima onda se dodeli `MAX_DOUBLE` ili `MIN_DOUBLE`).
Time osiguravamo da je jedinka sigurno kaznjena. 


Kod turnirskog selektovanje takodje ima necega slicnog kao roulette wheel-a. Koristi
se stohasticko univerzalno uzorkovanje. To bi moglo da se zamisli isto kao tocak, ali 
bi u ovom slucaju bila postavljena 2 "pokazivaca" koji ce da odaberu ucesnike u nekom
"mecu" turnira.


# Odredjivanje funkcije pripadnosti fazi skupa iz podataka koriscenjem GA

Pretpostavimo da imamo podatke primera sa 1 atributom i labelom. Neka atribut i labela 
imaju po 2 terma (`S + L` za atribut i `S + VL` za labelu) i neka su oni trougani fuzzy skupovi.

U tom slucaju mozemo iskoristiti genetski algoritam za odredjivanje funkcije pripadnosti
tako sto bismo odredili osnovice tih trouglova (za svaki fuzzy skup po jednu pravu/duzinu).

To znaci da zelimo da odredimo duzinu svake od 4 osnovica. Zapisujemo ih kao binarno kodirane 
realne brojeve.

Potom generisemo nasumicno jedinke.

Dekodiramo ih po formuli za dekodiranje realnih brojeva koji su binarno kodirani.

Dobijene vrednosti koristimo kao duzine spomenutih osnovica i na osnovu toga skiciramo 
fuzzy skupove.

Za svaku vrednost x-a iz podataka koje koristimo da generisemo funkcije pripadnosti
mi dobijamo u preseku fuzzy skupova atributa pripadnost kojom dalje secemo
fuzzy skupove labele i projekcijom, tj. povlacenjem normale, dobijamo vrednost izlaza
za datu jedinku.

Preracuna se greska, tj. odstupanje od realnog izlaza za dati ulaz na odredjeni nacin.
To moze da bude suma kvadrat te razlike ili nesto slicno.

Cilj bi bio da se smanji ta suma.

Kroz generacije bi trebali da dobijamo sve bolja resenja, tj. manje greske sve dok
ne dodjemo do toga da vise ne pravimo napredak ili mozda na osnovu nekog drugog uslova
za zavrsetak koji smo izabrali.
