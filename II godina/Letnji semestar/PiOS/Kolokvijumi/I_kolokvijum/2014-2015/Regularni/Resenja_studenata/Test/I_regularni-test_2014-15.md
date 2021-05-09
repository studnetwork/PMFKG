### 1. Koliko jedan hard disk može da sadrži primarnih a koliko extended particija. (?)


      | max primarnih | max extended
:---: | :---:         | :---: 
MBR   | 4             | proizvoljno mnogo
GTP   | 128           | proizvoljno mnogo


---

### 2. Čemu služi virtuelna memorija i kako se ona realizuje.(?)

---

### 3. Čemu služi mkfs komanda i šta radi sledeći njen poziv: mkfs ‐t hpfs ‐l /dev/list /dev/os1kol1

Komanda `mkfs` služi za kreiranje fajl sistema.

Navedenim pozivom se kreira fajl sistem tipa `hpfs`i specificira se putanja do fajla koji sadrži listu neispravnih blokova

---

### 4. Šta je rezultat izvršavanja sledećih komandi

```
a) cp /home/student/izvornikod.cpp{,‐old}
b) cd –
c) kill KILL 1111 && ./vezba.sh
d) $ find /home/student/demo ‐type f ‐perm 445 –print
e) ls –la | grep ^b‐wx
```

#### a) `cp /home/student/izvornikod.cpp{,‐old}`

Pravi kopiju fajla čiji je naziv dobijen nadovezivanjem stringa "-old" na sam naziv datog fajla


#### b) `cd --`

Postavlja trenutni radni direktorijum na vrednost sistemske promenljive `OLDPWD`, ukoliko je prethodno izvršena promena radnog direktorijuma, u suprotnom ispisuje poruku o grešci (da `OLDPWD` nije set-ovan). Pre izmene radnog direktorijuma, sistemska promenljiva `OLDPWD` dobija kao vrednost putanju do trenutnog radnog direktorijuma.


#### c) `kill KILL 1111 && ./vezba.sh`

ubija proces čiji je pid `1111` i nakon toga pogreće skriptu `vezba.sh` koja se nalazi u trenutnom radnom direktorijumu


#### d) `find /home/student/demo ‐type f ‐perm 445 –print`

U direktorijumu `demo` traži regularne fajlove koji imaju sledeće dozvole pristupa: vlasnik fajla ima samo dozvolu za čitanje, grupa ima samo dozvolu sa čitanje, a ostali korisnici imaju dozvolu za čitanje i dozvolu za izvršavanje.

Nakon što se pronađe fajl sa navedenim karakteristikama ispisaće se njegova putanja.


#### e) `ls –la | grep ^b‐wx (?)`

Ispisuje informacije u long formatu svih fajlova koji počinju sa `b‐wx`

---

### 5. Koje je pravo potrebno nad direktoriijumom za prikazivanje njegovog detaljnog listinga (`ls – l`)

Execute (`x`)

---

### 6. Napisati komandu koja dodaje novog korisnika pod imenom os1user. Pravo ime ovog korisnika je Operativni Sistemi 1. Ovaj nalog je potreban do 22. Januara 2015. Primarna grupa kojoj pripada je informatika, a sekundarna drugagodina. Ime shell‐a koji se koristi je Bourne Again shell (bash). Ako se ne prijavi na nalog u periodu od 25 dana, nalog će biti blokiran.

```
sudo useradd -c "Operativni Sistemi 1" -e "2015-01-22" -g "informatika" -g "drugagodina" -s "/bin/bash" -f 25 os1user
```