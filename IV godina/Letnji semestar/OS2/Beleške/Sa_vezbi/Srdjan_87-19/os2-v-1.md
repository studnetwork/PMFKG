# C i prevodjenje

1. kol niti
2. kol klasteri
parametarski posao

nece biti "ispitivano na vezbama": prevodnjenje
(mozda na usmenom bude pitano)

denis riche  
motivacija - napisatu jezik koji bi bio pogodam za operativni sisten unix

jezici u to vreme nisu bilo pogodni zbog performansi

sve "vremenski zahtevne" aplikacije su pisane u asembleru

verovalo se da efikasnost moze da se postigne samo sa asemblerom, a da prevodioci sluze za manje zahtevni programi za koje performanse nisu mnogo bitne

proces razvoja os u asembleru bi bio veoma tezak, sklon gresenju i nezgodan za debugovanje

ideja za C je bila: visi jezik moze lako da se pise i prevodi u masinski kod i ostvari performanse slicne asembleru

on je i sam bio iznenadjen performansama u prvim testovima

uveo je sintaksu koju koristi mnogo modernih jezika, nacin rada sa memorijom (pointerska aritmetika, ...), ...

Pod C-om se podrazumva C standard.

ISO i ANSI brinu o standardu c-a

pracenje standarda od strane onih koji implementiraju kompajler omogucava portabilnost izmedju razlicitih kompajlera

preporucljivo je da se isprati

obicno se ne stignu nesto iz standarda ne bude implementirano zbog nedostatka vremena

---

napisani program koji je na visem nivou, razumljiv coveku, treba da se prevede na najnizi nivo, masinski kod, 
kako bi se izvrsio na procesoru

u tom procesu ima vise faza:
1. preprocesiranje
2. prevodjenje
3. montaza
4. povezivanje

.c - c fajl
.i - procesuiran kod
.s - asemblerski kod
.o - objektni fajl

.h - heder fajl (ne kompajlira se; ne povezuje se)

kompajler optimizuje kod pri prevodjenju, ali nije uvek uspesan u tome. Zbog toga treba biti svestan posledica onoga sto se pise 

npr. navodnjenje promenljivih tamo gde su potrebne vs navodjenje promenljivih na pocetku fajla

## Preprocesuiranje

makroi

prolazi kroz kod i zameni neke stvari, ali kod uglavnom ostaje onakav kakav je bio

1-1 prevodjenje
jednostavno

## Prevodjenje

najbitniji i najkompleksniji deo

prevodjenje viseg jezika u nizi
(asembler)

asembler - nije masinski kod, ali moze da se preslika 1-1 u masinski kod; razliciti procesori imaju razlicit masinski kod
(instrukcije). Asembler moze vrlo lako da se pretvori u bilo koji masinski kod

prevodjenje moze da se uradi na mnogo nacina, ali cilj je da bude sto optimalnije moguce, tj. da se sa minimalnim brojem
instrukcija opise kod

postoji vise nivoa otimizacije

pri standardnom kompajliranju koristi se defaultnu, ali to moze da se promeni

default-ni je o2

o1 pravi cistiji kod
o3 daje bolje performanse


najbitnije je da sto manje mesta (npr kod iot uredjaja)

sto je veci nivo optimizacije to je i proces prevodjenja (skoro uvek) duzi

veliki programi zahtevaju jako puno vremena (za prevodjenje)

## Montaza

prevodjenje asemblera u masinski kod

objektni fajlovi daju uputstva os-u kako ce procesi sa diska biti prebaceni u radnu memoriju i kako ce se izvrsavati

postoju vise standarda
na linux-u je to ELF

## Povezivanje

Do ovog trenutka je zavrseno prevodjenje

Ovo je veoma bitan deo, na njemu se zasnivaju unix sistemi

win iso zauzima mnogo vise mesta nego linux

postoje dva nacina kojima se moze uvesti neki eksterni kod:
1. ugradjivanje svega u jedan fajl (staticko povezivanje)
2. dinamicke veze 

### staticko povezivanje

nalik kontejnerima

sve zavisnosti se smeste u jedan fajl

Prednosti:
* stabilnost
* sve je na jednom mestu 
* nece doci do problema zbog spoljnih zavisnosti

### dinamicko povezivanje

ne ugradjuju se zavisnosti u izvrsni kod

standardni lib ne mora da se ugradjuje jer se podrazumeva da je svaki sistem ima

posto ih vise programa koristi i posto se ne menjaju te biblioteke onda one mogu da budi izvrsni fajlovi koji su vec 
spremni za upotrebu. Pored toga su readonly

prednosti:
* manje prostora na disku
* racionalniji odnos prema memoriji (100 procesa moze da koristi isti izvrsni fajl biblioteke umesto da u ram dovodi 
  taj kod zajedno sa programom)
* jako bitna prednost je update-ovanje modula/programa nezavisno od programa koji ih ukljucuju

mana je to sto zavisnost mozda nije prisutna pa je zbog toga manje stabilan pristup u odnosu na staticko

na linux-u se potencira na dinamickom linkovanju

## smernice za efikasan kod

* izbegavati globalne promenljive kad je to moguce
* povratne vrednosti f-ja trebaju da budu int-ovi (programi nece brze raditi ako se koriste short ili char)
* koristiti maksimalan stepen lokalnosti kod lokalnih promenljivih (definisu se samo u bloku u kom su neophodne)
* prenosenje vecih delova memorije (struktura, ...) treba prenositi preko pokazivaca

postoji mogucnost da se kompajleru daju neke direktive kako bi se bolje optimizovo kod, npr kolika je sansa da 
dodje do if-a (to se u os dev koristi veoma cesto)

dobre prakse vremenom postaju deo standarda

# POSIX threads (threads)

48:08

konkurentnos i paralelizam

konkurentni procesi imaju zajednicke resurse

konkurentni mogu da se izvrsavaju na jednom procesoru, dok je za paralelno neophodno da imamo vise procesora jer 
drugacije procesi ne mogu da se izvrsavaju paraleno (u isto vreme)

stariji koncept: rad sa vise procesa  
noviji koncept: rad sa nitima

niti su laki "procesi"
dok su procesi "teski procesi"

proces je prevedeni program koji je u izvrsavanju

os vodi racuna o tome koje resurse proces sme da zauzme, gde moze da pise, cita, cuva promenljive i kada ce da se izvrsa

teski procesi su nezavisni

laki proces je deo jednog teskog procesa i izvrsava se unutar njega

visenitni proces ima sve isto kao i jednonitni, ali ima i delove koji se izvrsavaju "samostalno". 
**Svi ti delovi imaju pristup resursima glavnog procesa (ovo je jako bitno).**

ako imamo 2 procesa na nekom zadatku, oni zahtevaju organizaciju i koordinaciju. 
Kod rada sa nitima nema problema koji postoje kod procesa jer one zajednicke resurse, odnosno globalne promeljive

mogu da ih koriste konkurentno ili nekonkurentno.

nema otvaranja deljenih memorija, nema pajpova za poruke

globalne promenljive vide sve niti

zbog toga je izuzetno pojednostavljena interprocesna komunikacija

zbog toga se prvi pristup izbegava

druga prednost u odnosu na koriscenje teskih procesora jesu performanse pri njihovom kreiranju.

niti mogu da se kreiraju lako i jednostavno.  To je vrlo jeftina procedura koja se obavlja dinamicki u okviru nekog procesa
koji se vec nalazi u memoriji. OS nema mnogo posla oko toga. Veci deo oko posla vezanog za niti je obavljen samim kreiranjem 
teskog procesa koji ce sadrzi niti.

kreiranje veceg broja teskih procesa znacajno opterecuje sistem. OS ce tesko uspevati da ih sve smesti u rasporedjivac. 
Mora da obezbedi memoriju za sve njih, resurse, ... bice vise swap-ovanja i slicnog

zbog cega se ne koriste onda samo niti?

kada pukne jedna nit onda puca ceo proces

(primer tab-ova brower-a ilustruje ovu problematiku)

---

procesima upravlja OS

> na win je potpuni haos sa nitima. Ima oko 20ak biblioteka koje na razlicite nacine implementiraju niti

vecina modernih jezika ima svoju implementaciju niti koje komuniciraju sa sistemskim bibliotemaka ili sa nekim 
njihovim bibliotekama

---

pthreads veoma razvijen i robustan standard

np oznaka oznacava da f-ja nije portable (ugl. rade samo na linux-u)  
njih ima veoma malo  
to cini programe veoma portabilnim  

poslednji argument funkcije `pthread_create` je nije prihvacen rest parametar, vec predstavlja `void` pointer koji moze 
da pokazuje na bilo sta (pa samim time i na niz argumenata)

kod threadova postoji koncept join-ovanja

nije isto kao sa fork-ovanjem, thread izvrsava samo prosledjenu funkciju dok glavna nit nastavlja sa radom

`thread_join` je blokirajuca funkcija koja ceka dok se ne zavrse svi tredovi.

Zasto je potreban? kada glavna nit zavrsi sa radom onda se oslobadjaju svi resursi procesa, a time i niti koje su 
takodje resurs procesa. One ce biti ubijene, a to najcesce nije zeljeni efekat koji hocemo da postignemo. Zbog toga 
glavna nit ceka niti zavrse svoj rad.


`pthread_exit(NULL)`
