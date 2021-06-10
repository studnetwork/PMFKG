### 1. Objasniti GPT(GUID Partition Table) i osnovne razlike između MBR(Master Boot Record) i GPT.

GPT je jedan tip particione tabele, deo je UEFI standarda. Komatabilan je sa MBR-om, koristi LBA (Logical Block Addressing). Zove se GUID zato što svaka particija na disku ima jedinstven globalni identifikator, tj. GUID (**G**lobal **U**nique **ID**entifier)

Razlike:  

* GPT koristi 64 bita za adresiranje blokova, MBR koristi 32 bita
* kod MBR broj primarnih particija je ograničen na 4 po disku, dok GPT dozvoljava 128 primarnih particija po disku
* MBR podržava samo Legacy BIOS, dok GPT podržava i BIOS i UEFI


### 2. Objasniti upotrebu i sadržaj /etc/shadow fajla i dati primer jedne linije iz fajla.

Fajl `/etc/shadow` se postavljanje pravila koja se tiču lozinke nekog naloga i za skladištenje iste u šifrovanom obliku, kao i nekih drugih informacija.

Sadržaj:

* korisničko ime
* šifrovana lozinka
* datum poslednje izmene lozinke (u danima od 1.1.1970.)
* broj dana koji mora da se sačeka kako bi lozinka mogla ponovo da se promeni
* broj dana trajanja lozinke
* broj dana pred istek lozinke kada će se pojaviti upozorenje
* period neaktivnosti
* datum isteka
* rezervisano/eksperimentalno polje

Primer jedne linije:  
```
linus:2fd2358e1ea1b7a6bc08ea6:17060:0:99999:7:::
```

### 3. Objasniti svako polje iz sledeće linije koja je uzeta iz /etc/passwd fajla:<br/>torvalds:x:1001:1001:Linus Torvalds:/home/torvalds:/bin/sh

* **torvalds** - username
* **x** - lozinka (pre se nalazila na ovom mestu, sada je u `/etc/shadow`)
* **1001** - user id
* **1001** - group id
* **Linus Torvalds** - generalne informacije o nalogu ili korisniku (GECOS field)
* **/home/torvalds** - putanja do home direktorijuma korisnika
* **/bin/sh** - putanja do korisnikovog komandnog interpretera

### 4. Napisati komande koje kreiraju fajl test.txt i postavljaju mu prava pristupa tako da vlasnik ima sva prava, grupa kojoj korisnik pripada ima pravo da čita i piše dok svi ostali imaju samo pravo izvršavanja.<br>(dozvoljeno korišćenje i oktalnog i simboličkog režima)

Oktalni režim:  
```
touch test.txt
chmod 761 test.txt
```

Simbolički režim:  
```
> test.txt
chmod u=rwx,g=rw,o=x test.txt
```

### 5. Šta predstavlja i čemu služi Sticky bit (t) ?

Sticky bit je specijalna dozvola pristupa. Pre se koristila za zadržavanje procesa u memoriji i nakon njegovog izvršavanja, danas se najčešće koristi kako bi se sprečilo da jedan korisnik koji ima pravo upisa na nekom direktorijumu obriše fajlove drugog korisika u tom istom direktorijumu

### 6. Objasniti razliku između simboličkih i hard linkova.

Hard linkovi su alternativna imena nekog fajla, dok su simbolički linkovi fajlovi koji pokazuju na neku putanju koja može biti i fajl i direktorijum, pa čak i nevalidna putanja. 

Hard link mora da bude na istom disku i u istoj particiji kao i originalni fajl, dok simbolički link ne mora, već može da pokazuje i na neki fajl u mreži, drugom disku i slično.

Hard link ima ista prava kao i originalni fajl, dok simbolički link ne mora imati ni ista prava niti istog vlasnika ili grupu.

Ako se obriše jedini hard link, briše se i fajl, dok kod simboličkog linka, ako se obriše originalni fajl, simbolički link će postojati, jer će samo pokazivati na nepostojeću putanju.

### 7. Opisati strukturu foldera OS posle izvršenja sledeće komande:<br/><code>mkdir -p OS/{dir1/{test0,test1}/{test2,test3},dir2/{test4,test5}}</code>

```
OS
|
|--------dir1
|         |
|         |--------test0
|         |          |
|         |          |--------test2
|         |          |
|         |          \--------test3
|         |
|         |
|         \--------test1
|                    |
|                    |--------test2
|                    |
|                    \--------test3
|
|
\--------dir2
          |
          |--------test4
          |          
          \--------test5

```


### 8. Napisati regularni izraz koji služi za validaciju promenljivih. Promenljiva mora da počinje malim slovom ili znakom "_". Može da sadrži mala ili velika slova, brojeve i znakove: "+","-", "_" i mora da bude duža od 4 karaktera a kraca od 10. 


```
^([a-z]|_)[a-zA-Z0-9_+\-]{5,9}$
```