# RAID

## Hardverski RAID

### RAID1 (mirror)

deo jednog diska je identicna kopija dela drugog disk

to znaci da je **kapacitet duplo manji** od raid0

zahtev za citanje moze da se opsluzi sa bilo kog diska. Jedan deo sa jednog, drugi sa drugog, itd

ako se izgube podaci na nekom disku podaci mogu da se vrate sa nekog drugog

### RAID 1-3

nivoi 2-4 se ne srecu cesto na kontrolerima sa (?) (-25:52)

u njima su trake veoma male, cesto 1B ili jedna rec


raid2 koristi vise diskova za racunanje (?) Hemingovog koda (koristi se obicno kod nepouzdanih mreza, koristi se za i ispavljanje
gresaka; bice **bitno za ispit**)

raid2 se danas vise **ne koristi** zato sto diskovi vise nisu nepouzdani

raid3 je slican, koriste se samo kodovi za detekciju greske; koristi se jedan redudantan bit za parnost  
jedan redudantni disk se koristi za cuvanje parnosti

za i najmanji fajl manje-vise svi diskovi ucestvuju u obradi zahteva jer je taj fajl uglavnom rasprostranjen po svim diskovima
(zbog male velicine trake)

to je **veoma dobro** za jednokorisnicki sistem jer ce za svaki zahtev da rade skoro sve glave, dok kod visekorisnickih to **nije**
bas zgodno jer ce i za najmanji zahtev da rade sve glave pa nece biti paralelizacije (nece 1 korisnik zauzeti jednu glavu diska,
drugi drugu i tako dalje, vec ce sve njih zaposliti 1 korisnik) koja se npr. javlja u raid0

ako otkaze disk za parnost onda se zameni novim i parnost se ponovo preracuna

ako otkaze disk sa podacima njegovi podaci mogu da se rekonstruisu na osnovu podataka drugih diskova i parnosti (preracuna se)

parnost se racuna XOR-om

### RAID 4

raid4 je isto kao raid3, samo su blokovi vec

na visekorisnickom sistemu se zbog toga postoji mogucnost da se performanse povecaju, dok na jednokorisnickim samo ukoliko se 
radi sa ogromnim fajlovima jer bi tada u obradu zahteva bio ukljucen svaki disk (u suprotnom su performanse nepromenjene)

---

Da li je potrebno svaki put racunati parnost na osnovu podataka sa data diskova kada se sadrzaj promeni?

Za izracunavanje parnosti citaju se podaci sa sa svakog diska. Ako se nesto promeni na nekom disku onda se citaju odgovarajuci
blokovi na svim (relevantnim) diskovima i parnost se preracunava.

To nije neopgodno raditi zato sto se isto moze izracunati samo pomocu prethodne vrednosti na tom mestu i odgovarajuce parnosti. 
To dosta stedi na performansama

prvi disk koji ce da otkaze (najverovatnije) je disk za parnost. 

raid3 se vise ne koristi, kao ni 2 i 4

koriste se 1, 5 i 6

### RAID5

slican kao raid4, samo sto su trake za parnost raspodeljene na vise diskova.

umesto 1 diska samo za parnost, parnost se cuva na vise diskova. Trake za parnost su rasporedjene na vise diskova (po principu
round-robin). To ne utice na pouzdanost jer i da otkaze jedan od diskova, podaci mogu da se rekonstruisu na osnovu podataka 
sa drugih diskova

### RAID6

nivo 6 dodatno povecava sigurnost, cak i da 2 diska otkazu podaci opet mogu da se povrate

ako je potrebno N diskova za podatke onda je potrebno obezbediti N+2 diska

koristi 2 nezavisna proracuna parnosti

upis utise na smanjenje zivotnog veka diska jer svaki moze da sadrzi po 2 trake za parnost, odnosno ako nesto zelimo da upisemo
onda to zahteva i azuriranje 2 bloka za parnost

raid 1+0 (u zargonu 10)  
hibridni nivo  
2 raid1 povezana kao raid0  
ima i redudansu i prednosti raid0  
koji god da otkaza disk moguce je izvrsiti njegov oporavak

postoji i raid 0 + 1  
2 raid0 povezana kao raid1 na visem nivou  
manje popularan od raid10 jer je teze za adminiatraciju i razumevanje

## Softverski RAID

to je driver

**FTDISK** na >Win 2000  

na linux-u je **MDADM**

# Kes diska

Kes radi kao i kes procesora.

Obicno kada se donosi blok mora i neki da se izbaci

**LRU (least recently used)**: izbacuje se onaj blok koji je najduze bio u kesu

**LFU (least frequently used)**: svakom bloku se pridruzuje brojac koji se uvecava svakim referenciranjem na taj blok

problem sa LRU-om je to sto neki blok koji je rano ubacen, npr blok modula os-a, moze da bude neopravdano izbacen iako bi 
mozda bio potreban odmah nakon izbacivanja. Ne cuva se broj referenciranja pa nema dovoljno informacija za donosenje odluke

kod LFU postoji problem kada se nekom bloku pristupa retko, ali sa velikom frekvencijom. Zasto je to problem? zato sto je zbog
retkog pristupanja on **kandidat za izbacivanje**, ali posto se u tim retkim trenucima mnogo puta pristupi onda ce brojac mnogo 
da se poveca pa bi se takav blok mnogo dugo zadrzao u kesu iako to ne bi trebalo da se dogodi (mogao bi da se izbaci pa da ga
zamene neki blokovi koji ce za to vreme biti korisceni za obradu nekih drugih zahteva, a ovaj prvi blok bi mogao ponovo da se ucita 
kasnije kada bude bio potreban)

Da bi se ovi problemi izbegli koristi se varijanta LFU-a. 

Kes se deli na 2 sekcije: sa novim i sa starim blokovima

stara sadrzi blokove koji su kadnidati za izbacivanje

Nova sadrzi blokove koji su nedavno dosli. Blokovima koji su u njoj ne raste brojac pri referenciraju.
Kada se referencira neki blok on dolazi na vrh sekcije.

Pri izbacivanju izbacuje se blok sa najmanjim counter-om


Ovime se resava problem koji ima LFU jer se time counter nece naglo uvecavati.

Granica izmedju ove dve sekcije se odredjuje prilikom podizanja sistema i alociranja strukture za te sekcije



U ovom metodu takodje **postoji** problem. Problem je to sto blokovi iz nove sekcije imaju niske brojace pa kada predju
u staru sekciju oni ce verovatno imati mnogo manje vrednosti brojaca u odnosu na vrednosti brojaca blokova koji su vec 
bili u toj sekciji neko vreme pa time i imaju vecu varovatnocu da budu izbaceni cim udju u staru sekciju iako to ne bi 
trebalo da se dogodi (ocekivano bi bilo da bude izbacen neki od onih blokova koji su bili prisutni u staroj pre prelaska
datog bloka, onaj medju njima koji ima najmanju vrednost brojaca).

Resenje za to je uvodjenje nove, srednje, sekcije u koju ce da udju blokovi pri izlazku iz nove sekcije. U njoj blokovi nece biti
jos uvek kandidati za izbacivanje, ali counter ce moci da im se uvecava pa se nece odmah izbaciti kada dodju u staru sekciju


# U/I uredjaji na unix-u

Uradjaji su na unix-u imaju pridruzen fajl preko koga se moze komunicirati sa njima

Postoje 2 vrste: **baferovani** i **nebaferovani***

Takodje, postoje 2 vrste bafera: **sistemski bafer kes** (kes diska) i **karakter red**  
razlikuju se po tome sto jedan koristi kao jedinicu prenosa blok, a drugi karakter

Nebaferovani u/i se odvija direktno preko DMA (izmedju u/i modula i procesa)

## Bafer kes

bafer kes je u sustini kes diska

Odrzavaju se 3 liste:
1. **lista slobodnih slotova** - slot je velicine sektora na disku
2. **lista uredjaja** - lista bafera koji su trenutno pridruzeni svakom disku
3. **u/i red drajvera** - lista bafera koji stvarno rade ili cekaju na u/i na odredjenom uredjaju


Pretraga se vrsi preko hash tabele

Kako? stigne zahtev za blok na nekom uredjaju. Npr. (dev_id, block_id) = (1, 5)

to se prevede u neki int i preko hash-a dolazimo do okoline nekog slota u bafer kesu. Bafer kes je povezana lista koja
ima ugradjen mehanizam za pretragu.

Posto hash tabele nisu jednoznacan mehanizam za pretragu, moze da se desi da nismo dosli do bloka koji se trazi, vec je 
to samo njegova okolina. Zbog toga postoji dodatno i pointeri na druge 

postoji i jos jedan lanac pointera, free list pointer, koji pokazuje koja mesta su prazna. Zgodno je da to bude lista 
zbog alokacije memorije (msm da je zato sto se uzima prvo slobodno mesto pa se samo otkaci taj deo iz povezane liste).

## Karakter red

primer uredjaja koji koriste karakter red: mis, tastatura, touch

kada se nesto uzme iz njega onda se to obrise

radi kao fifo (kao i po producer & consumer principu)

## Nebaferovani u/i

Bafer se koristi zbog performansi i neometanog rada sistema za stranicenje, ali ga ovi uredjaji ne koriste.

Posto se ne koristi buffer onda se smanjuju mogucnosti za stranicenje, sto je njihova mana.

Mana je i takodje to sto se UI uredjaj veze za jedan proces pa je drugim procesima nedostupan.


ovakav u/i je nekada neophodan, npr. kada je u/i uredjaj povezan direktno sa procesorom (kada se radi u realnom vremenu)

# U/I sistema Linux


Prvi pokusaj da se napravi u kernulu modul koji radi sa diskovima je **Linus Elevator**. Napisao ga je Linus Torvalds

To nije nista drugo nego tehnika SCAN
(scan drzi sortiran red zahteva), tj. jedna varijante te tehnike.


Nakon toga je u nekoj sledecoj verziji kernela uveden **deadline scheduler (rasporedjivac po roku)**. Napravljen je kao odgovor na probleme sa linus elevatorom (lepljenje glave diska i isti prioritet operacija za citanje i pisanje)

Zasto nije potrebno da budu istog prioritete? Zato sto su operacije citanja bitnije jer ce ti ucitani podaci verovatno biti potrebni **odmah** za neki rad sa njima. Operacija pisanja su manjeg prioriteta jer nije neophodno da se odmah odrade. Mozemo
prepustiti OS-u da to uradi u pogodnom trenutku, dok su ti podaci privremeno uskladisteni u bafer kesu.

Ovaj modul radi tako sto pored elevatora (sortiranog reda koji jedino postoji u slucaju Linus Elevator-a; to je sortirani
red u SCAN-u) postoje jos i 2 reda (FIFO), jedan za citanje i jedan za pisanje.

Zahtev se prihvati u elevator, a pored toga se dodaje i u odgovarajuci red, write ili read zavisno od tipa zahteva

Oba reda imaju odredjeno vremensko ogranicenje za koje zahtevi u njima moraju da se obave. Ako se rok za izvrsenje priblizava 
kraju onda se prati redosled u tom red a ne redosled u elevatoru.

Naredna verzija jeste **predictive scheduler (rasporedjivac sa predvidjanjem)** koji u sebi sadrzi i deadline scheduler, tj.
predstavlja njegovu nadogradnju. On racuna lokalnost na osnovu vremena. To radi tako sto pri prijemu novih zahteva ne krece 
odmah da ih ispunjava vec ceka 6ms za slucaj da dodju jos nekih zahtevi koji zahtevaju slicne blokove pa ih onda izvrsava 
u paketu.

# Fajl sistem

Pozeljne osobine fajlova:
1. permanentno postojanje
2. deljivot izmedju procesa (permissions; istovremeni rad)
3. unutrasnja struktura zavisna od aplikacije
4. globalna struktura u obliku hijerarhije fajlova

Osnovne operacije nad fajlovima:
1. kreiranje
2. brisanje
3. otvaranje
4. zatvaranje
5. citanje
6. upis


## Struktura fajla i operacije nad njim 

Strukture:
1. polje (field)
2. zapis (recod)
3. fajl (file)

**Polje** je osnovni element podatka. Jedno polje predstavlja jednu vrednost

**Zapis** je kolekcija polja sa kojima aplikacioni program postupa kao sa jedinicama

**Fajl** je kolekcija povezanih podataka (ili mozda zapisa?)


### Operacije

1. izvuci_sve (koristi se u sekvencijalnim obradama, kada se zahtevaju svi zapisi)
2. izvuci_jedan (zasniva se na transakcijama; zahteva se jedan zapis)
3. izvuci_sledeci
4. izvuci_prethodni
5. umetni_jedan (nekad je potrebno sacuvati redosled, nekada nije)
6. izbrisi_jedan
7. azuriraj_jedan
8. izvuci_nekoliko (na osnovu nekog uslova)


## Korisnicki zahtevi

1. CRUD + write 
2. kontrola dozvola za sopstvene fajlove
3. kontrolisani pristup fajlovima drugog korisnika
4. restruktuiranje
5. pomeranje podataka izmedju fajlova
6. backup
7. pristup koriscenjem simbolickih imena



## Arhitektura fajl sistema

Na najnizem sloju su drajveri uredjaja za skladistenje. 

Basic File System i Basic IO supervisor se mogu smatrati kernelskim delom kojem se moze pristupiti 
preko interfejsa u obliku fajla /dev/sdXY npr.

Iznad toga se nalazi Logicki IO

Podaci mogu da se organizuju na vise nacina: pile, sequential, indexed sequential, indexed i hashed

1. drajveri uredjaja - komuniciraju direktno sa hardverom
2. osnovni fajl sistem ili fizicki U/I - zaduzen je za razmenu i baferovanje blokova (deo je OS-a)
3. logicki U/I - radi sa zapisima (records), a ne sa blokovima

---

Fajlu se obraca pomocu direktorijuma (direktorijum menadzera). Taj pristup se kontrolise 
user access control-om.

Ta zahtevana operacija se vrsi nad strukturama fajla, nad zapisima. 

Zapisi se pretvaraju u blokove jer kes radi iskljucivo sa blokovima. O tome se brine kernel OS i
disk kontroler.

Ti blokovi se pretvaraju u blokove diska (preko necega kao sto su elevatori koji su u ovoj lekciji
prethodno spomenuti)

ovaj opisani tok predstavlja neko upisivanje, tj. jedan od primera rada sa fajlom.

Fajl sistem / menadzment ima nadleznost od pocetka ovog procesa do rada sa zapisima, a
OS od te tacke do kraja. U toj tacki, na nivou zapisa, se susrecu ova 2 sistema


## Pozeljne osobine za FS

Pozeljne su, ali nisu podjednako bitnije:
1. logicko struktuiranje zapisa (programera nije briga to o kojim blokovima se radi, on radi)
2. kratko vreme pristupa
3. lakoca azuriranja
4. ekonomicnost (da ne trosi previse prostora na metapodatke ili neke dnevnike bespotrebno)
5. jednostavno odrzavanje
6. pouzdanost


One su pozeljne, ali ne i neophodno, npr. fs na CD-ROMu nema potrebe za lakocnom azuriranja jer 
je rec o read-only fs


## Gomila (pile)

Jedan od tipova organizacije fajlova (njihove unutrasnje strukture).

To je najjednostavniji oblik organizacije

Podaci se rasporedjuju onako kako dostizu. Posto polja ne stizu redom onda svako treba da 
sadrzi svoj opis (samoopis)

Ako se nesto trazi onda je potrebno da se pretrazi ceo fajl (celu gomilu)

Najbolji slucaj je da to sto trazimo bude na pocetku gomile, a najgori na njenom kraju.

Prosecno vreme pretrage je polovina broja zapisa tog fajla (gomile).

Duzina zapisa je varijabilna kao i skup polja

Ovaj tip je koristan u nekim situacijama, npr. za skladistenje privremenih podataka ili 
kada se cesto menja struktura.


## Sekvencijalni fajl

Fiksni format, zapisi su iste duzine i imaju neki redosled

Obicno prvo polje u zapisu predstavlja polje kljuca

Koristi se u paketnim aplikacijama (primer: aplikacija koja racuna prosek plata)

Pretrazuje se sekvencijalno, a to je lose. Moze da bude efikasnije u slucaju kada je ceo fajl
u RAM-u

Posto zapisi moraju da ostanu sortirani, a to sortiranje moze da bude skupo jer bi se mnogo
podatak premestalo cesto (manje-vise bi zahtevalo da se fajl obrise i napravi ponovo, onda 
se pristupa problemu tako sto se dodatnizapisi dodaju u novi fajl pile tipa. To je overflow 
fajl (moguce je da u ovom slucaju nije, vec da se zove journal, proveriti). 
Zapisi iz tog fajla se periodicno unose u glavni fajl.


Postoji i alternativa u kojoj se cuva redosled i omogucava jeftinije azuriranje. To se postize
organizacijom u obliku povezane liste.


## Indeksirani sekvencijalni fajl

Indeksiranje omogucava brzo stizanje do okoline onoga sto se trazi (u ovom slucaju zapisa)

Fajl prekoracenja (overflow file) je slican dnevniku (journal) koji ide uz sekvencijalni fajl,
ali je integrisan


Kada je potrebno dodati zapis on se dodaje u fajl prekoracenja i pointeri se azuriraju.

Da bi se ceo fajl obradio sekvencijalno obrada se vrsi redom dok se ne dodje do pokazivaca na
prekoracenje i onda se stavlja sa obradom prolaskom kroz tu listu sve dok se ne dodje do NULL-a.
Zatim se pretraga nastavlja tamo gde se stalno u glavnom fajlu.

Indeksi mogu da budu organizovani u vise nivoa, zbog cega se obicno i prikazuju graficki u obliku
trougla.


## Indeksni fajl

Dosta lici pristupu podacima tabele u MySQL-u.

Nekada se pretraga vrsi po atributu koji nije PK

Za svako polje od interesa se dodaje poseban indeks. **Napusta se** koncept sekvencijalnosti i
PK.

Postoje 2 vrste indeksa:
* iscrpni indeks
* delimicni indeks

Iscrpni indeks (exhaustive index) sadrzi stavku za svaki zapis

Delimicni indeks (partial index) ima stavku samo za one zapisi koji sadrze neko polje

## Direktan (hesirani) fajl

Koristi se kada je potrebno da se dodje **brzo** do jednog zapisa **sa odredjenom osobinom**.

Ne postoji koncept sekvencijalnog uredjivanja

Koristi se hesiranje vrednosti kljuca jer se pretrazuje po njemu

Primenjuje se u slucajevima u kojima su zapisi fiksne duzine, gde se trazi brz pristup i
pristupa samo po jednom zapisu istovremeno
