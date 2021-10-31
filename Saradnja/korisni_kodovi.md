# Opis
U ovom fajlu se nalaze neki delovi koda koji bi mogli biti od koristi za pravljenje novih fajlova u okviru ovog projekta

# Komentar

Ukoliko želite da unesete komentar u markdown (.md) fajlu, koji neće biti vidljiv pri u samom prikazu, koristite sledeći kod:
```

[//]: # (Ovde unosite sadrzaj komentara)
```

**BITNA NAPOMENA:** iznad komentara je neophodno da postoji prazan red kako bi markdown kompajler mogao da prepozna da se radi o komentaru

# Spoiler
```HTML
<details>
  <summary>Tekst koji je vidljiv pre klika</summary>
  Tekst spojlera, vidi se nakon klika
</details>
```
**Primer**:
<details>
  <summary>Tekst koji je vidljiv pre klika</summary>
  Tekst spojlera, vidi se nakon klika
</details>

# Link
Ukoliko želite da navedete link, to možete uraditi tako što će te prvo napisati:
```
[tekst koji predstavljati link][oznaka linka]
```
i onda nakon toga je potrebno navesti, u delu za reference koji se nalazi na kraju svakog fajla, web adresu za oznaku linka:
```
[oznaka linka]: https://www.neka-adresa.com
```

  Taj deo je započinje od sledećeg koda
```
[//]: # (---------------------------------------------------------)

[//]: # (-------------U ovom delu se nalaze reference-------------)

[//]: # (---------------------------------------------------------)
```
i prostire se do kraja fajla u kome se nalazi.


Ovako bi trebao da izgleda deo nekog markdown fajla:
```
...

Ukoliko ste želite da doprinesete projektu i učestvujete u njegovom razvoju posetite ovaj [link][saradnja].

...

[//]: # (---------------------------------------------------------)

[//]: # (-------------U ovom delu se nalaze reference-------------)

[//]: # (---------------------------------------------------------)



[saradnja]: ./README.md#Opis

...
```
**Rezultat navedenog primera:**  
...

Ukoliko ste želite da doprinesete projektu i učestvujete u njegovom razvoju posetite ovaj [link][saradnja].

...

[//]: # (---------------------------------------------------------)

[//]: # (-------------U ovom delu se nalaze reference-------------)

[//]: # (---------------------------------------------------------)



[saradnja]: ./README.md#Opis

...

# Ubacivanje slike
Ubacivanje slike funkcioniše na isti način kao i navođenje linka, jedina razlika je to što se ispred takve komande doda znak "!"  
**Primer**:  
```
...

![Tabela 1][BP1-vezbe-slide1-z1]

...


[//]: # (---------------------------------------------------------)

[//]: # (-------------U ovom delu se nalaze reference-------------)

[//]: # (---------------------------------------------------------)



[BP1-vezbe-slide1-z1]: ../II%20godina/Zimski%20semestar/BP1/Ve%C5%BEbe%20i%20predavanja/BP1-vezbe-slide1-z1.png
```
**Rezultat**:  
...

![Tabela 1][BP1-vezbe-slide1-z1]

...


[//]: # (---------------------------------------------------------)

[//]: # (-------------U ovom delu se nalaze reference-------------)

[//]: # (---------------------------------------------------------)



[BP1-vezbe-slide1-z1]: ../II%20godina/Zimski%20semestar/BP1/Ve%C5%BEbe%20i%20predavanja/BP1-vezbe-slide1-z1.png
