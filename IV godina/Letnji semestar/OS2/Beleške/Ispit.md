# Informacije o skripti

## Važne napomene

- Skripta sadrži pregled gradiva obrađenog na predavanjima na predmetu _Operativni Sistemi 2_.
- Za neke delove gradiva samo su navedeni pojmovi, dok za druge postoji i određen nivo objašnjenja.
- Skripta je sačinjena od informacija sa predavanja (2022/23), sa Moodle stranice predmeta (Snimci, prezentacije i PDF-ovi), sa Internet-a (pretezno Wikipedija), i slobodne interpretacije autora skripte.
- Potpuna tačnost informacija u ovoj skripti **nije garantovana**.
- Skripta je **otvorenog karaktera**, tako da svako može doprineti kreiranjem _**Issue**_-a za primećene **greške**, **predloge** i **komentare**, kao i kreiranjem _**Pull Request**_-a za sve **izmene** skripte.
- Po prirodi stvari, skripta je uvek u statusu `work in progress`, ne postoji definitivna finalna verzija, ali je ideja da se svakom novom verzijom poveća vrednost koju skripta pruža studentima na predmetu _OS2_.
- Verzionisanje skripte: `[kompletiranje_celine] . [unapredjenje_sadrzaja] . [ispravka_greske]`

## Status

- Trenutna verzija: `0.1.0`
- Pokriveno gradivo za verziju `1.0.0` (kompletiranje svog gradiva na minimalnom upotrebljivom nivou):
    - [X] I/O control & Disk scheduling
    - [ ] _**IN PROGRESS**_ - File Systems
    - [ ] CPU scheduling
    - [ ] Distributed systems, Client-server & Clusters
    - [ ] Virtualization
    - [ ] Cloud Computing + Docker
    - [ ] Distributed process scheduling + Network FS
    - [ ] Security and safety of computer systems

---

# Input/Output

## Hardverska platforma

Tri tehnike za izvođenje I/O operacija:
- Programirani I/O
- I/O koji se inicira prekidom
- Direktan pristup memoriji (DMA, Direct Memory Access)

Istorijski razvoj I/O funkcionalnosti:
- CPU direktno upravlja
- I/O kontroler, programirani I/O, bez interrupta
- I/O kontroler, sa interrupt-ima
- I/O kontroler + DMA (disk I/O)
- I/O kontroler je poseban procesor
- I/O kontroler + memorija (kontrola terminala)

### CPU-DMA komunikacija

CPU šalje DMA kontroleru:
- Da li se zahteva čitanje ili upis
- Adresa I/O uređaja
- Početna adresa u memoriji za čitanje/pisanje
- Dužina podataka za čitanje/pisanje

DMA, različite hardverske izvedbe:
- Single-bus, detached DMA
- Single-bus, integrated DMA-I/O
- Dedicated I/O bus

## Projektovanje I/O OS-a

Ciljevi projektovanja:
- Efikasnost - Kako premostiti ogroman jaz između brzina CPU-a i I/O periferija
- Opštost - Hijerarhijski, modularni pristup projektovanju I/O funkcionalnosti OS-a

### Slojevita arhitektura I/O

Postoje različiti slojevi, tj. realizacije za rad sa različitim vrstama I/O uređaja.

Periferijski uređaji (jednostavno):
- Logički - Sa uređajima se radi preko ID-a i jednostavnih komandi za otvaranje/zatvaranje, čitanje/pisanje
- I/O uređaj - Zadate operacije se pretvaraju u I/O instrukcije
- Raspoređivanje i upravljanje - Čekanje u redovima i raspoređivanje na hardverskom nivou

Fajl sistem (složenije):
- Directory management - Simbolička imena fajlova se pretvaraju u identifikatore koji referenciraju fajl deskriptore ili tabelu indeksa
- File system - Otvaranje/zatvaranje, čitanje/upis, prava pristupa, itd.
- Fizička organizacija - Logičke reference fajlova se pretvaraju u fizičke adrese na disku (traka, sektor, itd.)

## Baferovanje

Problemi:
- Program se zaustavlja i čeka spori I/O
- Proces ne može biti swapovan ako čeka I/O

Namena baferovanja:
- Izvođenje prenosa **sa uređaja** **pre** nego što se zahtev postavi (predvidjanje)
- Izvođenje prenosa **na uređaj** neko vreme **nakon** postavljanja zahteva (odlaganje)

Vrste periferala:
- Uređaji orjentisani na **blokove** - U baferu skladište **blok**
- Uređaji orjentisani na **tokove** - U baferu skladište **bajt**

Vrste baferovanja
- Single buffering
- Double buffering
- Circular buffering

## Performanse diska

Parametri performanse diska:
- Vreme pozicioniranja (`Ta`) - Broj staza + smirivanje
- Rotaciono kasnjenje (`Tb`) - Prosek max i min obrtaja do odgovarajuceg sektora, `Tb = 1/2r`, _seconds per rotation_ (`r` - brzina obrtanja)
- Vreme prenosa (`Tc`) - Samo prebacivanje podataka, `Tc = b/rN` (`b` - broj bajtova za prenos, `N` - broj bajtova po stazi, `r` - brzina obrtanja)
- Ukupno vreme pristupa: `T = Ta + Tb + Tc`

### Politike raspoređivanja

- Da bi se poboljšale porformanse treba smanjiti **srednje vreme koje se provodi u pozicioniranju**
- Napomena: Operativni sistem održava red čekanja zahteva za čitanje/pisanje od različitih procesa
- Slučajan redosled ispunjavanja zahteva daje veoma loše rezultate

### Algoritmi za raspoređivanje

- **FIFO** - **Ok za jedan proces**. Loše performanse ako ima više procesa.
- **PRI (prioritetno)** - Prioritetniji su **kratki interaktivni poslovi**. Nije cilj optimizacija korišćenja diska već da se ispuni neki drugi zahtev OS-a.
- **LIFO** - Poboljšavanje **lokalnosti**. Pretpostavka da će se glava diska najmanje pomeriti za naredni zahtev. Očigledna mogućnost **gladovanja**.
- **SSTF (Shortest Service Time First)** - Izabrati zahtev koji zahteva najmanje pomeranje glave diska. Slučajan izbor kada su rastojanja podjednaka.

_Sve dosadašnje tehnike mogu ostaviti neki zahtev neispunjen osim ako se ne isprazni red čekanja._

- **SCAN** - Glava se pomera u samo jednom smeru usput ispunjavajući zahteve, sve dok ne stigne do poslednje staze ili nema više zahteva u tom smeru. Zatim menja smer, vraća se nazad, i ispunjava zahteve u tom drugom smeru. Prednost se daje krajnjim stazama i poslovima koji su najkasnije stigli.
- **C-SCAN** - Kao SCAN samo, ne ispunjava zahteve u tom suprotnom smeru kada se vraća, već se prebaci na početak i ponovo krene u prvom smeru da ispunjava zahteve.

_Kod SCAN i C-SCAN moguće je da se glava ne pomera neko duže vreme, ako se često pristupa jednoj stazi._

- **N-stepeni SCAN** - Red čekanja zahteva se deli na podredove dužine N. Podredovi se obrađuju jedan po jedan koristeći SCAN. Dok se jedan red obrađuje novi zahtevi stižu u neki drugi red.
- **FSCAN** - Kao N-stepeni SCAN, samo koristi 2 reda čekanja.

## RAID (Redundant Array of Independent Drives)

Namena:
- Performanse - Višestruke paralelne komponente
- Sigurnost

Karakteristike svih RAID-ova:
- Skup fizičkih uređaja koje sistem vidi kao jedan logički uređaj
- Podaci su raspoređeni preko niza fizičkih uređaja
- Kapacitet redundantnog diska se koristi za skladištenje informacija koje garantuju obnovljivost u slučaju otkaza jednog diska (ovo ne važi za RAID0)

RAID nivoi:
- **RAID0** - Performanse i kapacitet. Diskovi se spajaju bez trosenja prostora za redundansu, a posto ih imas vise podaci se mogu citati istovremeno sa vise njih.
- **RAID1** - _Mirror_. Kada ima dosta zahteva priblizava se performansama RAD0. Oporavak posle otkaza jednostavan. Upisivanje zahteva da se azuriraju trake i na originalnom i na mirror disku.
- **RAID2** - Trake su male, cesto 1B. Broj redundantnih diskova je logaritam broja diskova sa podacima. **Preracunava se Hamingov** kod za ispravljanje gresaka. Prilikom pisanja i citanja pristupa se svim diskovima. RAID2 ima primenu iskljucivo kada dolazi do mnogo gresaka diska (znaci danas skoro nikad)
- **RAID3** - Slicno kao RAID2, samo sa jednim redundantnim diskom. Umesto slozenog koda za ispravljanje gresaka, koristi se **jednostavan bit parnosti** za **skup pojedinacnih bitova na istim pozicijama na svim diskovima** za podatke. Ako disk otkaze, zameni se ispravnim, i podaci sa otkazalog diska se rekreiraju na osnovu ostalih diskova i bitova parnosti. Postize veoma dobre performanse jer su svi podaci podeljeni na male trake duz svih diskova, ali se zato moze izvrsavati samo jedan I/O zahtev istovremeno.

_RIAD nivoi 4, 5 i 6 koriste tehniku nezavisnog pristupa, pa su pogodniji za velike ucestanosti I/O zahteva, ali su manje pogodni za velike brzine prenosa. Trake su relativno velike_

- **RAID4** - Traka za parnost na disku parnosti se racuna bit po bit od odgovarajucih bitova na svakom disku za podatke.
- **RAID5** - Slicno kao RAID4, samo se trake za parnost rasporedjuju po svim diskovima. Za RAID5 niz od `n` diskova, traka za parnost se nalazi na jednom od diskova za prvih `n` traka, zatim na razlicitom disku za narednih `n` traka, i tako dalje (round-robin rasporedjivanje trake za parnost).
- **RAID6** - Vrse se _dva odvojena proracuna parnosti_, i smestaju se u posebnim blokovima na razlicitim diskovima (jedan od njih je XOR). Ako se zahteva kapacitet od `N` diskova za podatke, RAID6 niz treba imati `N+2` diska. Podaci mogu da se regenerisu **cak i ako otkazu 2 diska**. Svako upisivanje utice na 2 bloka za parnost, to negativno utice na performanse.

_Postoje softverski i hardverski RAID._

Hibridni RAID-ovi:
- RAID10 (1 + 0)
- RAID01 (0 + 1)

## Keš diska

_Isti princip kao kod CPU keša._

Politika zamene sadržaja keša:
- **LRU** (Least Recently Used) - Najskorije referenciran blok je na vrhu steka. Sa dna steka se izbacuju.
- **LFU** (Least Frequently Used) - Svaki blik ima brojač koji se povećava svakim referenciranjem. Najviše referenciran blok je na vrhu steka. Sa dna steka se izbacuju. Problem ako se blok retko, ali veliki broj puta referencira.

_**Frequency-Based Replacement** - Sortiranje steka prema **MRU** (Most Recently Used, obrnuto od LRU), novokorisceni blokovi prelaze na pocetak steka i povecava im se **count**.
1. **Dve sekcije** - Stek je podeljen na dve jednake sekcije, **new** (od vrha steka do sredine) i **old** (od sredine do dna). Odluka o zameni bloka se donosi prema **LFU** (Least Frequently Used) za blokove iz **old** sekcije. Blokovi iz **new** sekcije ne mogu biti zamenjeni a prilikom pristupa **ne povecava** im se **count**._
2.**Tri sekcije** - Uvodi se **middle** sekcija koja sluzi kao bezbedna zona iz koje blokovi ne mogu biti izbaceni prilikom zamene, dok ne udju u **old** sekciju.


## UNIX I/O sistem

_Svakom I/O uredjaju se pridruzuje specijalni fajl (oznake `b`, `c`) u direktorijumu `/dev`_

- **Baferovani I/O** - Prolazi kroz sistemske bafere. Vrste bafera:
    - **Sistemski bafer keš**
    - **Karakter red** - Producer/consumer
- **Nebaferovani I/O** - Smanjuje mogucnos za stranicenje. Uredjaj vezan s procesom, nije dostupan drugim procesima.

## Linux I/O system

- Linus Elevator - Odrzava jedan red cekanja (i za citanje i pisanje) blokova i modifikacija
- Deadline scheduler - Postoji rok za citanje i pisanje (ovde je ugradjen je Linus Elevator)
- Predictive scheduler - Vremenska lokalnost (ovde je ugradjen je Deadline scheduler)


# File Systems

Osnovne pozeljne osobine fajlova:
- Permanentno postojanje
- Deljivost zmedju proesa (dozvole)
- Unutrasnja struktura zavisna od aplikacije (OS se ne mesa)
- Globalna struktura u obliku hijerarhije fajlova

Osnovne operacije sa fajlom:
- Kreiranje
- Brisanje
- Citanje
- Pisanje
- Otvaranje
- Zatvaranje

## Arhitektura fajl sistema

_File sistemi fajlove cuvaju kao kolekcije bajtova (byte-oriented) ili zapisa ([record-oriented](https://en.wikipedia.org/wiki/Record-oriented_filesystem))._

- Byte-oriented: FAT32, NTFS, EXT4, ZFS, ...
- Record-oriented: Obicno vezani za _mainframe_ operativne sisteme

Slojevi:
1. Logicki I/O - Zapisi (za byte-oriented su bajtovi?)
2. Fizicki I/O - Blokovi (razmena i baferovanje)
3. Drajveri - Komunikacija direktno sa hardverom

Slojevi (resursi):
1. User & Program commands
2. File structure
3. Records (za byte-oriented su bajtovi?)
4. Physical blocks in RAM
5. Physical blocks in Disk

Logicka organizacija zapisa:
- Pile - Zapisi se pakuju redom. Nisu iste duzine. Pretrazuje se ceo fajl da bi se nasao zapis. Koristi se kada se cesto menja struktura fajla.
- Sequential - Zapisi su iste duzine. Lose pretrazivanje. Koristi se u paketnim aplikacijama. Zapisi se prvo dodaju u odvojen Pile fajl (fajl transakcija), pa se periodicno unose. Alternativa je povezana lista.
- Indexed Sequential - Index (hashmap?). Overflow fajl.
- Indexed - Ovako npr. radi MySQL tabela. "Upakovani indeksirani fajl"
- Direct (Hashed) - Direktni pristup jednom bloku. Hash funkcija.

## Deljenje fajlova

_Na Linux-u, prava pristupa se dodeljuju Vlasniku, Grupi i Ostalima._

Prava pristupa:
- Fajlovi
    - **r** - Read content
    - **w** - Modify content
    - **x** - Execute (if script or binary)
- Direktorijumi
    - **r** - Read list of files
    - **w** - Create and delete files or subdirectories
    - **x** - ??

## Blokovanje

Vrste blokovanja:
- Fixed
- Variable spanned (Promenljive duzine sa promoscenjem)
- Variable unspanned (Promenljive duzine bez promoscenja)

## Upravljanje _storage_-om

Izbor velicine prostora za fajl:
- Unapred (zna se velicina fajla: kopiranje, kompajliranje, ...)
- Dinamicko (ne zna se unapred velicina fajla)

Politike dodele blokova fajlu (neiskoriscena grupa blokova):
- **First fit** - Prva grupa
- **Best fit** - Najmanja grupa
- **Nearest fit** - Najbliza grupa

Tehnike za dodeljivanje blokova na osnovu nacina vodjenja evidencije o blokovima fajla:
- **Susedno** - Dodeljeni blokovi su sigurno susedni. Potrebno je sacuvati samo id pocetnog bloka i broj blokova u grupi.
- **Ulancano** - Dodeljeni blokovi nisu nuzno susedni. Blokovi pokazuju na onaj sledeci u listi, tako da je samo potrebno sacuvati pocetni blok i eventualno broj blokova u listi.
- **Indeksno** - Postoji indeksni blok koji ima listu id-jeva blokova, pa je za svaki fajl potrebno voditi racuna samo o indeksnom bloku.

Tehnike za vodjenje evidencije o slobodnim blokovima:
- Tabela bitova - Indikatorski bit za svaki blok. Cela tabela se ucitava u RAM nije bas pogodno za mali RAM.
- Ulancani slobodni segmenti - Azuriranje moze da bude skupo
- Indeksiranje - Slicno kao za fajlove, indeksni blok koji sadrzi promenjljive slobodne delove, zbog performansi
- Lista slobodnih blokova - Slicno tabeli bitova, ali se za svaki slobodni blok cuva njegov id, npr. 32-bitni (4B) i ne ucitava se cela lista u RAM, vec jedan deo, u obliku potisnog steka, pa kada se iz steka izbace svi id-jevi novi se ucitaju se sa diska.

## File management na Unix-ima

Vrste fajlova:
- Regular
- Directory
- Device
- Named pipe
- Soft link
- Socket

File je predstavljen Inode strukturom koja sadrzi sledece podatke o blokovima koje poseduje:
- 13 direktnih pokazivaca na blokove (-> blocks (13))
- 1 jednoindirektni pokazivac na blokove (-> pointers -> blocks)
- 1 dvoindirektni pokazivac na blokove (-> pointers -> pointers -> blocks)
- 1 troindirektni pokazivac na blokove (-> pointers -> pointers -> pointers -> blocks)

## Very Simple File System

- Rezijski deo + Deo sa podacima (1/7)
- Rezija:
    - Indeksni fajlovi
    - Tabela bitova za podatke
    - Tabela bitova za indekse
    - Superblok
- Direktorijum je fajl sa podacima za svaki fjal koji sadrzi, + za `.` i `..`:
    - inum (index node number/id)
    - name
    - reclen (name size in bytes)
    - strlen (name size in char count)

### Proces pristupa fajlu

Citanje fajla `/foo/bar`:
- `open( /foo/bar )`
    - read `/` inode
    - read `/` data
    - read `foo` inode
    - read `foo` data
    - read `bar` inode
- `read()` (one block)
    - read `bar` inode
    - read `bar` data
    - write `bar` inode (update access time)

Kreiranje fajla `/foo/bar` i pisanje:
- `create( /foo/bar )`
    - read `/` inode
    - read `/` data
    - read `foo` inode
    - read `foo` data
    - read & write `inode bitmap` (update bit for `bar` inode)
    - write `foo` (add record for `bar` file)
    - read & write `bar` inode (create inode for `bar` file)
    - write `foo` inode (update modification time)
- `write()` (one block)
    - read `bar` inode
    - read & write `data bitmap` (update bit for one data block for `bar`)
    - write `bar` data (write data to one `bar` data block)
    - write `bar` inode (update modification time)

## Fast File System

- Blokovi u trakama na odredjenoj udaljenosti se nalaze u odvojenim grupama
- Svaka grupa blokova ima svoju "rezijsku" sekciju
- Fajlovi bliski po lokaciji u stablu direktorijuma su bliski i fizicki na disku (nalaze se u istoj grupi)
- Redosled sekvencijalnog citanja blokova randomizovan
- Zakljucavanje fajla

## File System Checker & Journaling (dnevnici)

### Mogući scenariji kod pada sistema

_Metapodaci se ne slažu => _

Prilikom pisanja (1 uspesna operacija):
- Samo su novi data blokovi upisani na disk
    - Nisu azurirani nikakvi rezijski podaci (bitmape i inode-ovi)
    - Stanje sistema je konzistentno. Imamo validno prethodno stanje
- Samo je Inode azuriran
    - Veća šteta
    - Stanje nije konzistentno
- Samo je bitmapa azurirana
    - Nema velike štete. Rezervisano je malo više blokova nego što se zapravo koristi
    - Stanje nije konzistentno


Prilikom pisanja (2 uspesna operacija):
- Metapodaci su azurirani
    - Nije dobro. Podaci nisu azurrani pa u njima imamo "smece"
- Uspešno ažuriranje Inode-a i podataka
    - Stanje nije konzistentno
    - Prostor zapravo nije rezervisan (preko bitmape)
- Uspešno ažurirana bitmapa i podaci
    - Nema velike štete. Rezervisano je malo više blokova nego što se zapravo koristi
    - Stanje nije konzistentno

### File System Checker

_Radi se povremeno. Npr. na Linuxu automatski prilikom n-tog mounta diska._

- Provera Superbloka
- Provera slobodnih blokova - Iščitava se bitmapa slobodnih blokova.
- Provera stanja indeksnih čvorova
- Linkovi indeksnih čvorova (`lost+found`, indeksni čvorovi koji nemaju referencu ni u jednom direktorijumu)
- Dva fajla pokazuju na isti blok - Razdvajanje. Klonira se blok i jedan redirektuje na novi blok
- Provera direktorijuma

_Pre verujemo indeksnim čvorovima nego bitmapi._

### Vodjenje dnevnika (Journaling) - Fizičko logovanje

Jedan zapis u dnevniku:
- Transaction BEGIN
- Nova verzija Inode-a
- Nova verzija Bitmape
- Blok podataka za upis
- Transaction END

Protokol za upis podataka:
- Upis u dnevnik, ali bez "Transaction END" dela
- Dodavanje "Transaction END" dela tek nakon sto su sigurno ostali upisani
- Checkpoint: Upisati podatke na konacne lokaciju na disku
- Osloboditi prostor koji je zauzimala trenutna transakcija u dnevniku

Oporavak:
- Cita se dnevnik
- Ako neka transakcija nije kompletirana, izvrsice se ponovo

Doziranje azuriranja iz log fajla:
- Prvo se azurira disk buffer

### Vodjenje dnevnika (Journaling) - Dnevnik metapodataka

Jedan zapis u dnevniku:
- Transaction BEGIN
- Nova verzija Inode-a
- Nova verzija Bitmape
- Transaction END

Protokol za upis podataka:
- Upisati podatke (ne i metapodataka) na konačne lokacije na disku
- Upis u dnevnik, ali bez "Transaction END" dela
- Dodavanje "Transaction END" dela tek nakon sto su sigurno ostali upisani
- Checkpoint: Upisati metapodatke (podaci su već upisani) na konačne lokacije na disku
- Osloboditi prostor koji je zauzimala trenutna transakcija u dnevniku

_Ponovo korišćenje bloka (???)_

## Solid State Drive (SSD)

- TODO


# Dodatno

## Buffer vs. Cache

_source: ChatGPT_

- **Buffer**
    - Temporarily holds data during data transfer between sources and destinations to manage differences in data rates
    - _Producer-Consumer_
- **Cache**
    - Temporarily stores frequently accessed data to speed up subsequent data retrieval and improve overall system performance
    - _Writter-Reader_

## EXT FS

- EXT2 - Unapređeni FFS
- EXT3 - EXT2 sa Journaling-om
- EXT4 - Unapređeni EXT3




