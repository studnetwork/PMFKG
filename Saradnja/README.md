# Opis
U ovom fajlu se nalaze neke smernice koje predstavljaju neku vrstu konvencije na ovom projektu kao i neki saveti oko pisanja koda

# Dodavanje, brisanje i izmena fajlova
Za dodavanje, brisanje ili izmenu fajlova preporučuje se korišćenje GitHub klijenta koji olakšava rad sa Git-om. Dostupan je na [Windows i macOS sistemima][gh client official], a za Linux sisteme postoji [neoficijalni projekat GitHub programera][gh client linux].

# Organizacija projekta i materijala
## Linkovi
Ukoliko se navode linkovi na neki resurs koji se nalazi u okviru ovog projekta potrebno je koristiti relativno adresiranje, ukoliko je to moguće. To bi omogućilo lakše održavanje projekta i linkova u okviru njega.

Za primer ovakve transformacije adrese linka, iz apsolutne u relativnu, koristićemo link do fajla `korisni_kodovi.md` koji se nalazi u istom folderu kao i ovaj fajl u kome ćemo ga linkovati. Kod sa apsolutnim adresiranjem izgleda ovako:
```
[korisni kodovi]: https://github.com/Produktivna-grupa/PMFKG/blob/master/Saradnja/korisni_kodovi.md
```
Kod za njegovo relativno linkovanje:
```
[korisni kodovi]: ./korisni_kodovi.md
```

Ukoliko bi smo želeli iz ovog fajla da linkujemo sa relativnom adresom neki fajl koji se ne nalazi u trenutnom folderu, npr. fajl `README.md` sa početne stranice, to bi smo uradili na sledeći način:
```
[Link ka README.md fajlu sa početne stranice][link]

Sadržaj koji se nalazi između ova dva dela

[link]: ../README.md
```

Rezultat:  
[Link ka README.md fajlu sa početne stranice][link]

Sadržaj koji se nalazi između ova dva dela

[link]: ../README.md


## Imenovanje fajlova
Poželjno je da svi fajlovi koriste karakter `'_'` (underscore) umesto `' '` (space) karaktera radi lakšeg navođenja tih fajlova prilikom korišćenja komandne linije

## Kreiranje novih foldera i šabloni
Poželjno je da se u folderima nalaze markdown fajlovi ( .md ) koji će imati navigacionu ulogu. Korišćenje nekog mehanizma za navigaciju može biti korisno jer olakšava kretanje korisnika kroz projekat i opisuje sadržaj foldera, ističe bitne informacije i intuitivniji je od običnog spiska fajlova. 

Cilj korišćenja nekog ovakvog mehanizma bi bio pojednostavljivanje pronalaženja informacija koje korisnik traži. Većina tih navigacionih fajlova je kreirana u obliku šablona koje treba samo popuniti i obrisati nepotrebne delove. Svi šabloni se mogu naći u folderu [Šabloni][šabloni].

## Upućivanje korisnika na neki resurs
Ukoliko želite da usmerite korisnika na neki od naslova određenog fajla, link možete dobiti korišćenjem dugmeta pored tog naslova ( kao što je na slici prikazano ).  
![Slika ikonice za link][slika]

# Saveti vezani za markdown ( .md ) fajlove
## Prelazak u novi red
Prelazak u novi red se može postići na 3 načina:  
* navođenjem dva space karaktera na kraju reda  
* pritiskom dva puta na tester Enter  
	(nije preporučljivo jer se time pravi veći razmak između redova)  
* navođenjem HTML tag-a `</br>` na kraju reda  
	(ovaj način se preporučuje samo za situacije u kojima je neophodan kao što je npr. prelazak u novi red unutar nekog HTML koda )
## Code Snippets
Neke specifične delove kodova koji su korišćeni u markdown fajlovima ovog projekta možete pronaći na ovom [linku][korisni kodovi].


[//]: # (---------------------------------------------------------)

[//]: # (-------------U ovom delu se nalaze reference-------------)

[//]: # (---------------------------------------------------------)



[slika]: https://github.com/Produktivna-grupa/PMFKG/blob/master/Saradnja/link2cb.png
[šabloni]: https://github.com/Produktivna-grupa/PMFKG/blob/master/Saradnja/Šabloni
[korisni kodovi]: https://github.com/Produktivna-grupa/PMFKG/blob/master/Saradnja/korisni_kodovi.md
[gh client official]: https://desktop.github.com/ 
[gh client linux]: https://github.com/shiftkey/desktop
