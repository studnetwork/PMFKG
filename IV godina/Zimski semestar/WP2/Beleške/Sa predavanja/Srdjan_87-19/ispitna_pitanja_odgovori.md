# 1. Sta je Nginx

Nginx je fleksibilan HTTP server koji se moze konfigurisati na razlicite nacine.
On je takodje i reverse proxy server, mail proxy server i genericki TCP/UDP sever.

# 2. Nginx funkcionlanosti

Funkcionalnosti koje nginx omogucava:
* load balancing
* serviranje statičkih file–ova
* proxy ponasanje, tj. može da "sakrije“ razne servere koji rade na različitim portovima 
i time korisniku stvori utisak da se radi o samo jednom serveru koji radi na jednom portu
* reverse proxying (sa kesiranjem)
* kesiranje za razne web servere
* autoindexing
* skalabilnost

# 3. ECMAScript i verzije

ECMAScript je standard koji osigurava interoperabilnost izmedju web stranica 
i razlicitih pregledaca (browser-ima). Najcesce se koristi za pisanje skripti 
koje se izvrsavaju na klijentskom delu, ali u sve vecem porastu je i njegovo 
koriscenje za pisanje serverskog dela aplikacija i servisa.

Verzije:
* ES1
* ES2
* ES3
* ES5 (ili ECMAScript 2009)
* ES6 (ili ECMAScript 2015)
* ECMAScript 2016
* ECMAScript 2017
* ECMAScript 2018
* ECMAScript 2019
* ECMAScript 2020
* ECMAScript 2021
* ECMAScript 2022

Napomena: **ES4 je preskocena** (ne postoji)
          
# 4. Javascript - Use strict 

Use strict je direktiva kojom se oznacava da se dati deo 
koda treba izvrsiti u strinktnom modu ("strict mode")

Pomaze pri pisanju "clean" i "secure" JS koda. 

Ono sto je smatrano losom sintaksom koja je tolerisana 
ili ignorisana ce u ovom modu **uzrokovati gresku**

Ova direktiva je u stvari samo jedan string koji se navodi
**na pocetku fajla** ili **na vrhu neke funkcije** (od cega zavisi
i njen scope). Oni pregledaci koji je podrzavaju ce je 
izvrsiti, a oni koji je ne podrzavaju ce je samo ignorisati
i tretirati kao obican string.

```Javascript
"use strict";
```

# 5. Javascript - `forEach`

`forEach` je metod array objekta koji nad svakim elementom 
niza (array-a) zove prosledjenu funkciju.

Sadrzi 2 parametra:
1. funkciju koja ce da se izvrsi nad svakim elementom
2. opcioni parametar koji ce predstavljati `this` referencu 
   unutar prosledjene funkcije

Funkcija koja predstavlja prvi parametar prihvata 3 parametra:
1. vrednost trenutnog elementa
2. opcioni parametar koji predstavlja indeks trenutnog elementa
3. opcioni parametar koji predstavlja niz kojem trenutni 
   element pripada
   
   
Primer:
```Javascript
let result = 0;
let nums = [1, 2, 3, 4, 5];
numbers.forEach(sum);

funciton sum(value) {
    result += value;
}
```

# 6. Javascript - Getter i setter 

Getter i setter predstavljaju metode koji podsecaju na 
getter-e i setter-e svojstva (propertija). Rad sa njima podseaca na 
rad sa poljima jer ne zahtevaju koriscenje zagrada. 

Pri definisanju objekta umesno key-value (property name - value) 
para koristimo rec `get` ili `set` ispred odgovarajuceg metoda.

Funkcija setter-a ima dodatni parametar koji predstavlja vrednost
koja se dodeljuje property-u

Omogucavaju enkapsulaciju i definisanje dodatne logike kao sto su 
neke provere ili procesiranje.


Primer:
```Javascript
val person = {
    fistName: "Petar",
    lastName: "Petrovic",
    get fullName() {
        return this.firstName + " " + this.lastName;
    },
    set name(value) {
        this.firstName = value; 
    }
};
```

# 7. Javascript - Properties

Property-ji objekta imaju atribute. Neki od njih su:
* `name`
* `value`
* `writable` - da li vrednost moze da se promeni
* `enumerable` - da li moze da se enumerise (pristupi u `for..in`-u, `stringify`-u, itd..)
* `configurable` - da li moze da se konfigurise (izmene vrednosti atributa nakon definisanja)

Propery objekta moze da se definise sa:
```Javascript
Object.defineProperty(objekatNadKojimDefinisemo, "nazivPropertija", {
    value: "vrednost",
    writable: false,
    enumerable: true
})
```

# 8. Javascript - Object.create

`Object.create(prototip)` kreira se novi objekat na osnovu nekog 
drugog objekta (prototipa). Imace iste podatke i strukturu

Ima i drugi argument koji predstavlja objekat u kome se mogu definisati 
novi propertiji (sa svojim atributima) koji ce biti dodati novom objektu

# 9. Javascript - Razlike izmedju `let`, `var` i `const` 

`var` je hoisted (moze da se koristi pre nego sto se deklarise), dok `let` i `const` nisu

`var` ima globalni scope ili scope same funkcije, dok `let` i `const` imaju block
scope. 

Kada se jednom deklarisu `let` i `const` promenljie vise ne mogu ponovo da se deklarisu
pod tim imenom.

Konstantne (`const`) sprecavaju nastanak greske pri promeni sadrzaja promenljivih 
ciji sadrzaj nije trebao da se menja 

Konstante **moraju** da imaju dodeljenu vrednost

Vrednost ne moze da im se menja, ali ako pokazuju na neki objekat ili niz onda je 
moguce menjati njihov sadrzaj (dok pokazivac ostaje onakav kakav jeste)

# 10. Javascript - for (standardni, in, of)

`for..of` i `for..in` omogucavaju prolazak kroz iterabilne objekte 

`for..of` omogucava iterisanje tako da se pri svakoj iteraciji dobije vrednost
koja ce se vratiti (vrednost propertija `next`), dok `for..in` pri svakoj 
interaciji vraca indeks 

`for` je standardan `for` koji se pojavljuje u vecini jezika:
```Javascript
for (initialization; condition; afterthought)
  statement
```

# 11. Javascript - Iterables

Iterables su objekti kroz koje je moguce iterisati pomocu `for..of`-a, tj.
objekti koji implementiraju metod `Symbol.iterator`

Koriste iteratore koji implementiraju `next()` metod. 

`next` vraca objekat koji mora da ima propertije:
* `value` koji sadrzi vrednost koja ce se vratiti
* `done` koji oznacava da li je iterisanje zavrseno ili ne

Primer definisanja iterabilnog objekta:
```Javascript
myNumbers = {};

myNumbers[Symbol.iterator] = function() {
  let n = 0;
  done = false;
  return {
    next() {
      n += 10;
      if (n == 100) {done = true}
      return {value:n, done:done};
    }
  };
}
```

`for..of` automatski zove metod `Symbol.iterator`

# 12. Javascript - Map i Set

Mape omogucavaju da se definisu mapiranja kljuceva u odgovarajuce vrednosti.

Kao kljuc mozemo koristiti i neki objekat

Kreiranje i dodavanje novog mapiranja:
```Javascript
const apples = {name: 'Apples'};

const fruits = new Map();
fruits.set(apples, 500);
```

Redosled kljuceva je isti kao redosled u kojem su oni dodavani.

---

Skupovi (`Set`) su kolekcije jedinstvenih vrednosti. Svaka vrednost se moze pojaviti
samo jednom. 

Skupovi mogu imati vrednosti bilo kog tipa podatka.

Primer:
```Javascript
const letters = new Set();

letters.add('a');
letters.add('b');
```

# 13. Javascript - Klase

Klase u JS predstavljaju sablone za kreiranje objekata.

Uvek moraju da imaju metod `constructor`

Sintaksa:
```Javascript
class ImeKlase {
    constructor(...) {
        ...
    }
}
```

Primer:
```Javascript
class Car {
    constructor(name, year) {
        this.name = name;
        this.year = year;
    }
}
```

Instanciranje:
```Javascript
const myCar = new Car("Ford", 2015);
```
 
# 14. Javascript - Promise

Promisi predstavljaju alternativu za callback-ove. Omogucava pisanje citljivijeg
koda jer se izbegava ugnjezdavanje koje se javlja kod callback-ova (callback hell).

Objekat promise-a sadrzi kod koji zahteva cekanje na njegovo potpuno izvrsenje ("producing code"). 

Pomocu tog objekta se kasnije moze pozvati kod koji ce konzumirati rezultat "producing"
koda, tj. koda koji se ceka.

Sintaksa:
```Javascript
let myPromise = new Promise(function(myResolve, myReject) {
  myResolve();
  myReject(); 
});

myPromise.then(
  function(value) { ... },
  function(error) { ... }
);
```

Takodje, promisi se mogu ulancavati (podseca na otpakivanje rezultata):
```Javascript
myPromise
.then(function(value) { ... })
.then(function(value) { ... })
.catch(function(error) { ... });
```

# 15. Javascript - Fetch API

JS Fetch API predstavlja interfejs koji omogucava pregledacima da naprave http zahteve

Fetch API koristi promise-e

Primer:
```Javascript
fetch(file)
.then(f => f.text())
.then(txt => console.log(txt));
```
 
 
# 16. Javascript - Symbol

Tip `Symbol` moze da se koristi na razlicite nacine.

Jedan od nacina koriscenja je i definisanje skrivenog identifikatora kojem ne moze
slucajno da se pristupi iz nekog dela koda.

Dobija se jedinstvena vrednost.

Omogucava da dodamo property objektu (koji je npr. dolazi iz neke biblioteke) i da 
budemo sigurni da ta vrednost nece biti dodeljena nekom property-u istog naziva koji
je postojao unutar tog objekta ili koji ce se dodatni kasnije, ali u drugom kontekstu.

Primer:
```Javascript
let id = Symbol();
nekiObjekat[id] = 'vrednost';
```

Kao parametar moze da ima i string koji predstavlja samo opis koji moze da bude koristan
prilikom debugging-a

`Symbol('opis') == Symbol('opis')` vraca `false` jer je rezultat uvek nova jedinstvena 
vrednost

Ne mozemo da dobijemo vrednost koriscenjem pomocu koda `new Symbol()`

`Symbol.for('key')` omogucava kreiranje jedinstvene vrednosti i njeno cuvanje u 
globalnom registru. Prvo se proverava da li vec postoji u njemu i ukoliko postoji 
onda se ona vraca, a ukoliko ne postoji onda se u njega unosi kreirana vrednost za 
i key za koju je kreirana

Zbog toga: `Symbol.for('key') == Symbol.for('key')` vraca `true`

`Symbol.keyFor` je inverzna funcija funkcije `Symbol.for` koja za datu vrednost
vraca njen kljuc

Ovaj globalni registar vazi za celu aplikaciju.


# 17. Javascript - default vrednost parametra i rest parametar

Default-ne vrednosti parametra funkcije su vrednosti koje se 
dodeljuju tom parametru ukoliko se pri pozivu ne prosledi njegova 
vrednost ili ukoliko je ta vrednost `undefined`

Primer:
```Javascript
function f(a, b=3) {
  console.log(a + b);
}

f("a");
```

---

Rest parametar predstavlja niz svih argumenata koje preostanu u pozivu datog metoda.

Obuhvata sve argumente za koje nije definisan regularan tip parametra.

Oznacava se sa `...nazivParametra`

Primer:
```Javascript
function f(a, ...niz) {
  console.log("a: " + a);
  for(let e of niz)
    console.log("vrednost elementa: " + e);
}

f("1", "aa", "bb", "cc")
```

# 18. NodeJS - async i sync izvrsavanje

NodeJS se zasniva na asinhronom modelu dogadjaja u jednoj niti.

U petlji se preko event listener-a evidentira zavrsetak rada
NodeJS API-a i na osnovu toga se pozivaju odgovarajuci 
event handler-i.

Uobicajeni model programiranja je sinhroni. U njemu se pri pozivu
funkcije ceka na zavrsetak njenog izvrsenja pre nego sto se predje
na sledecu naredbu. Takvo izvrsavanje se naziva **blokirajucim (ili sinhronim) **
jer se program blokira sve dok se data funkcija ne izvrsi. 


Zbog blokiranja aplikacije koje rade sinhrono i istovremeno opsluzuju veliki broj 
korisnika moraju da naprave novu nit kako bi se u njoj izvrsila obrada tog zahteva

Kod sinhronog rada, ukoliko dodje do poziva neke funkcije koja treba da radi neko
vreme onda ce izvrsavanje task-ova da bude blokirano dok se ona ne izvrsi. Kod
asinhronog (neblokirajuceg) taj task ce biti blokiran, pa ce se preci na sledeci
task dok prvi ne postane odblokiran u nekom trenutku.

# 19. NodeJS - event queue i event loop

U NodeJS aplikacijama zahtevi ili pozivi operacija se stavljaju 
u **red dogadaja (event queue)**. Te dogadjaje uzrokuju zahtevi
klijenata.

Event loop je nit koji osluskuje za nove dogadjaje, tj. uzima ih
iz event queue-a.

Ukoliko je rec o I/O task-ovima koji nisu blokirajuci onda se oni 
izvrsavaju u event loop-u i klijentima se vraca odgovarajuci response.

Ukoliko je rec o blokirajucim I/O task-ovima onda se oni 
prosledjuju (internal C++) thread pool-u kako bi se
taj task obavio u nekoj drugoj niti.

# 20. NodeJS - Worker pool 

Event loop predstavlja glavnu nit. Posto bi blokirajuci task zaustavio 
tu nit, umesto da se saceka na njegovo izvrsenje u toj niti task se ce 
izvrsiti u nekoj drugoj niti i time nece doci do blokiranja.

Ta druga nit se uzima iz worker pool-a. On sadrzi ogranicen broj niti

Programeru nije vidljiv ovaj visenitni model jer je on sakrivan iza 
NodeJS API-a

Blocking task moze da vrati rezultat preko callback-a
ili pomocu promise-a

# 21. NodeJS - async callback funkcija

# 22. NodeJS - `process.nextTick` i `setImmediate`

Tick predstavlja jednu iteraciju petlje dogadjaja (event loop-a)

`process.nextTick(callback)` omogucava zakazivanje izvrsenja 
callback-a `callback` pre pocetka naredne iteracije, dok 
`setImmidiate(callback)` izvrsava prosledjeni callback na samom
pocetku sledece iteracije iteracije

`process.nextTick(callback)` se uvek izvrsava pre `setImmidiate(callback)`


# 23. NodeJS - EventEmitter

Za emitovanje i registrovanje dogadjaja koristi se klasa `EventEmitter` 
iz modula `events`

Da bi se `EventEmitter` koristio u korisnickom objektu potrebno je 
da funkcija sablon (funkcija kojom se kreira objekat) ili klasa 
nasledjuju prototype klase 

Primer za funkciju sablon:
```Javascript
const { EventEmitter } = require('events');

function SablonFunkcija() {
  this.metod = function(nekaVrednost) {
    this.emit('nazivDogadaja', nekaVrednost);
  };
}

SablonFunkcija.prototype = EventEmitter.prototype;

const y = new SablonFunkcija();
```

Za isti dogadjaj je moguce registrovati vise listener-a

Listeneri se mogu registrovati sa `objekat.on('nazivDogadaja', nekiListener)`
ili sa `objekat.addListener('nazivDogadaja', nekiListener)`.

Ako hocemo da isto uradimo preko klase koristimo:
```Javascript
class Klasa extends EventEmitter {  // neophodno
  constructor() {                   // neophodno
    super();                        // neophodno
    this.metod = function(nekaVrednost) {
    this.emit('nazivDogadaja', nekaVrednost);
  }
}
```

# 24. Javascript - closure

Closure je mehanizam koji omogucava funkciji da pristupi podacima koje koristi 
iz spoljasnjeg okruzenja i nakon sto se to okruzenje napusti.

Iako bi se u drugim jezicima javila greska da data promenljiva vise ne postoji,
u JS se zbog closure-a cuva referenca na promenljive koje su u upotrebi od 
strane neke unutrasnje funkcije.

Kontekst (okruzenje) se cuva sve dok se funkcija ne izvrsi.

Primer:
```Javascript
function makeSizer(size) {
  return function () {
    document.body.style.fontSize = `${size}px`;
  };
}

const size12 = makeSizer(12);
const size14 = makeSizer(14);

document.getElementById('size-12').onclick = size12;
document.getElementById('size-14').onclick = size14;
```

# 25. NodeJS - Baferi

Baferi predstavljaju skladista podataka u binarnom obliku.

Podrazumevani encoding je UTF-8

Podrzava citanje u formatu malog ili velikog endian-a.

Operacije sa baferima su neblokirajuce.

Primer za upis u bafer:
```Javascript
let buf256 = Buffer.alloc(256);
buf256.fill(0); // ispuni buffer nulama
buf256.write("neki tekst");
console.log(buf256.toString());
```

Metod `buffer.write` ima i parametre preko kojih je moguce definisati
poziciju od koje ce da se vrsi upis i kolika ce da bude duzina upisa
```Javascript
buf256.write(", dodatni tekst", 10, 15);
```

Takodje je moguce promeniti ili postaviti vrednost nekog bajta, slicno
kao u radu sa nizovima: `buf[30] = 45;`

Bafer moze i da se kreira iz string literala:
```Javascript
let buf = Buffer.from('neki string');
```

Bafer moze da se kopira, potpuno ili delimicno, metodom `copy`

Vise bafera moze da se spoji u jedan metodom `concat` koja prihvata niz
bafera

# 26. NodeJS - Tokovi podataka

Tokovi podataka (streams) su memorijske strukture koje se koriste za
I/O operacije.

Predstavljaju univerzalni mehanizam za prenos podataka sa jednog mesta
na drugo.

Moguce je registrovati listener-e za slucaj kada su podaci dostupni za
citanje ili spremni za pisanje. 

Za citanje (pisanje) iz objekta korisnicke klase potrebno je da ona
nasledjuje klasu `Readable` (`Writable`) i da implementira metod
`_read` (`_write`) iz kojeg prosledjuje podatke koriscenjem metoda
`push()`

Ukoliko se prosledi `null` ili prazan string metodu `push` onda ce se to 
izazvati dogadaj `end`


Ove klase se nalaze u modulu `streams`:
```Javascript
const { Writable, Readable } = require('streams');
```

Na objetku korisnicke klase koja nasledjuje neku stream klasu moguce je
registrovati listener-e `on(data)` i `on(end)`, gde prvi predstavlja
lister koji osluskuje za dogadjaj kada se podaci upisuju / citaju, dok
drugi predstavlja listener koji osluskuje za dogadjaj kada je proces
upisa / citanja gotov.
 
Primer:
```Javascript
const { Readable } = require('streams');

class Answer extends Readable {
  constructor() {
    super();
    this.niz = [1, 2, 3];
    this.indeks = 0;

    this._read = function() {
      if(this.indeks == 2)
        this.push(null);       // dogadjaj `end`
      else {
        this.push(this.niz[this.indeks]);
        this.indeks += 1;
      }
    }
  }
}
```

`_write` je metod koji treba da ima sledeci potpis `function(data, encoding, callback)`

Primer:
```Javascript
let writer = new Writer(); // `Writer` nasledjuje `Writable`
writer.write("neki tekst", "utf8");
writer.end("Kraj"); // upisuje dati string i zatvara tok
```

Pored klasa `Readable` i `Writable` u modulu postoji klasa `Duplex` 
koja omogucava i citanje i pisnje nad istim objektom. Predstavlja 
kombinaciju klasa `Readable` i `Writable`