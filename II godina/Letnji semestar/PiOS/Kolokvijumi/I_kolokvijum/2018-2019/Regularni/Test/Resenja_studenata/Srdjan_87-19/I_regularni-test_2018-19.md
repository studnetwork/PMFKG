### 1. Navesti komponente kernela operativnog sistema Linux.

* **upravljanje procesima** - kreira procese i omogućava višeprocesni rad (multitasking)
* **upravljanje memorijom** - kontroliše dodeljivanje memorije i swap prostora procesima, kernelskim komponentama kao i bafersko keširanje
* **upravljanje fajl sistemima** (VFS, Virtual File System)
* **apstrakcija mrežnih servisa**
* **podrška za hardverske uređaje**, podrška za različite sisteme datoteka, podrška za TCP/IP…


### 2. Objasniti čemu služe sledeći fajlovi:

```
a. /etc/passwd
b. /etc/shadow
c. /etc/group
d. /etc/gshadow
```

#### a. `/etc/passwd`

Sadrži informacije o korisničkim nalozima:  
* username  
* ID korisnika   
* ID korisnikove primarne grupe  
* lične podatke o korisniku  
* putanju do ličnog direktorijuma korisnika  
* putanju do shell interpretera  


#### b. `/etc/shadow`

Sadrži sigurnosne podatke o korisničkim nalozima:  

* username  
* enkriptovanu lozinku  
* datum poslednje izmene lozinke  
* broj dana nakon kojeg se lozinka može promeniti  
* broj dana nakon kojih lozinka mora biti promenjena  
* broj dana pre isticanja lozinke kada će korisnik dobiti upozorenje o isticanju lozinke  
* broj dana tokom kojih nalog može biti neaktivan nakon kojih će biti ugašen  
* datum isteka lozinke  


#### c. `/etc/group`

Sadrži informacije o grupi: 

* ime grupe  
* ID grupe  
* listu korisnika koji pripadaju datoj grupi  


#### d. `/etc/gshadow` 

Sadrži sigurnosne podatke o grupi:  

* naziv grupe  
* enkriptovanu lozinku  
* listu administratora grupe  
* listu korisnika grupe  

---

#### 3. Objasniti ishod sledećih komandi:

```
a. cp -r /etc/* /tmp/oldconfig
b. mkfs -t ext4 -l /tmp/list /dev/hda2
```

#### a. `cp -r /etc/* /tmp/oldconfig`

Kopira sav sadržaj direktorijuma `/etc` (i njegovih poddirektorijuma)  u direktorijum `/tmp/oldconfig`)


#### b. `mkfs -t ext4 -l /tmp/list /dev/hda2`

Kreira fajl sistem tipa `ext4` sa inicijalizovanom listom neispravnih blokova `/tmp/list` na particiji `/dev/hda2`

---

### 4. Napisati komandu kojom svim poddirektorijumima i fajlovima unutar zadatog direktorijuma (npr. `/tmp/random`), menja prava pristipa tako da vlasnik ima sva prava, grupa ima pravo čitanja i pisanja, preko: <br/>a. simboličkog režima<br/>b. oktalnog režima.

#### a. simbolički režim

```
chmod -R u=rwx,g=rw,o= zadatiDirektorijum
```


#### b. oktalni režim

```
chmod -R 760 zadatiDirektorijum
```


### 5. Opisati strukturu direktorijuma DIR nakon izvršenja sledeće komande: `mkdir -p DIR/{dir1/{file1,dir2/{file2,file3}},{file4,dir3/{file5,file6}}}`

```
DIR
|----------dir1
|           |----------file1
|           |
|           \----------dir2
|                       |----------file2
|                       |
|                       \----------file3						  
|
|
|
|----------file4
|
\----------dir3
            |----------file5
            \----------file6
```

---

### 6. Napisati regularni izraz koji proverava ispravnost datuma. Ispravan datum je u formatu: <br/>`dd.mm.gggg.` ili `mm/dd/gggg.` dd je u opsegu 01..31, mm je u opsegu 01..12, a gggg su 4 cifre.

```
^(((0[1-9]|(1|2)[0-9]|3(0|1))\.(0[1-9]|1[0-2])\.)|((0[1-9]|1[0-2])/(0[1-9]|(1|2)[0-9]|3(0|1))/))[0-9]{4}$
```

* `^` - mora da počne sa šablonom koji sledi nakon ovog znaka  
* `$` - mora da se završi sa šablonom koji prethodni ovom znaku  
* `(0[1-9]|(1|2)[0-9]|3(0|1))` - odgovara opsegu `01..31`, tj. delu `dd`  
* `(0[1-9]|1[0-2])` - odgovara opsegu `01..12`, tj. delu `mm`  
* `[0-9]{4}` - odgovara delu `gggg`  

* `((0[1-9]|(1|2)[0-9]|3(0|1))\.(0[1-9]|1[0-2])\.)` - odgovara početnom delu prvog formata  
	* uprošćena reprezentacija uz upotrebu prethodno navedenih izraza: `(dd\.mm\.)`  

* `((0[1-9]|1[0-2])/(0[1-9]|(1|2)[0-9]|3(0|1))/)` -  odgovara početnom delu drugog formata  
	* uprošćena reprezentacija uz upotrebu prethodno navedenih izraza: `(mm/dd/)`  
* uprošćena reprezentacija kompletnog regularnog izraza: `^((dd\.mm\.)|(mm/dd/))gggg$`  