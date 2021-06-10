### 1.) Objasniti upotrebu i sadržaj /etc/shadow fajla.

Koristi se za kontrolu naloga i skladištenje šifrovane lozinke. 

Za svaki nalog se čuva:

* korisničko ime
* šifrovana lozinka
* datum poslednje izmene
* minimanal broj dana trajanja lozinke
* maksimalan broj dana trajanja lozinke
* broj dana pred istek naloga kada se će pojaviti upozorenje
* broj dana bez aktivnosti nakon kojih će se nalog proglasiti neaktivnim
* datum isteka naloga

### 2.) Šta predstavljaju i čemu služe SUID, GUID i Sticky bit?

Predstavljaju specijalne dozvole fajlova.

Svrha:

* **SUID**: dodeljuje procesu nekog izvršnog fajla dozvole koje ima vlasnik tog fajla
* **SGID**: dodeljuje procesu nekog izvršnog fajla dozvole koje ima grupa tog fajla. Ukoliko je reč o direktorijumu, omogućava da svaki novokreirani fajl dobije dozvole tog direktorijuma, a ne dozvole korisnika koji je kreirao taj fajl.
* **Sticky bit**: najčešća implementacija je mogućnost da se korisniku onemogući brisanje fajlova drugih korisnika u tom direktorijumu koji ima setovan sticky bit

### 3.) Napisati komande koje kreiraju fajl proba.txt i postavljaju mu prava pristupa tako da vlasnik ima sva prava, grupa kojoj korisnik pripada ima pravo da čita i izvršava, dok svi ostali imaju samo pravo čitanja.

```
touch proba.txt
chmod 754 proba.txt
```

### 4.) Objasniti razliku između sledećih komandi:<br/><ul><li>ln -s proba p1</li><li>cp -s proba p2</li>

Nema razlike

### 5.) Napraviti regularni izraz koji služi za validaciju formula. Formula mora da počinje brojem (broj može biti i negativan), nakon koga sledi operacija (+,-,*,/), drugi broj (koji takođe može biti negativan i ukoliko je negativan okružen je zagradama), potom znak jednakosti. Formula se završava pozitivnim ili negativnim brojem. Matematičku tačnost formule nije potrebno ispitivati

```
^-?[0-9]+[+*/\-](\(-[0-9]+\)|[0-9]+)=-?[0-9]+$
```

**Napomena**: u delu regexa `[+*/\-]` `-`(crta, tj. *hyphen*) treba da se navede kao poslednji karakter, kako ne bi bio protumačen kao karakter koji predstavlja opseg između dva karaktera, npr. kao u `[A-Z]`