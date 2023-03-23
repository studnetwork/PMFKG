# 1. Sta je Nginx

Nginx je fleksibilan HTTP server koji se moze konfigurisati na razlicite nacine.
On je takodje i reverse proxy server, mail proxy server i genericki TCP/UDP server.

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
* ECMAScript 2016
* ...
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
getter-e i setter-e svojstva (propertija). Za razliku od obicnih metoda
oni mogu da se koriste kao property (ne zahtevaju koriscenje zagrada 
poziv i dobijanje vrednosti ili dodela vrednosti radi na isti nacin kao 
i kod obicnog property-a)

Pri definisanju objekta umesno key-value (property name - value) 
para koristimo rec `get` ili `set` ispred odgovarajuceg metoda (pogledati priemr).

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

console.log(person.fullName);
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

`var` i `let` promenljive ne mogu da se deklarisu u istom bloku pod istim imenom.

Konstanta (`const`) sprecava slucajnu promenu sadrzaja promenljive ciji sadrzaj nije
predvidjeno menjati.

Konstante **moraju** da imaju dodeljenu vrednost (da budu inicijalizovane)

Vrednost ne moze da im se menja, ali ako pokazuju na neki objekat ili niz onda je 
moguce menjati njihov sadrzaj (dok pokazivac ostaje onakav kakav jeste)

# 10. Javascript - for (standardni, in, of)

`for..of` i `for..in` omogucavaju prolazak kroz iterabilne objekte 

`for..of` omogucava iterisanje tako da se pri svakoj iteraciji dobije vrednost
koja ce se vratiti (vrednost propertija `next`), dok `for..in` pri svakoj 
interaciji vraca redom sve nazive enumerabilne string property-e datog objekta

`for` je standardan `for` koji se pojavljuje u vecini jezika:
```Javascript
for (initialization; condition; afterthought)
  statement
```

# 11. Javascript - Iterables

Iterables su objekti koji implementiraju metod `Symbol.iterator`. 
Kroz njih je moguce iterisati pomocu `for..of`-a

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

## Map

Mape omogucavaju da se definisu mapiranja kljuceva u odgovarajuce vrednosti.

Kao kljuc mozemo koristiti i neki objekat

Redosled kljuceva je isti kao redosled u kojem su oni dodavani.

Kreiranje mape i dodavanje novog mapiranja:
```Javascript
const fruits = new Map();

fruits.set('Apples', 500);
fruits.get('Apples');
// output: 500
```

## Set

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
const myCar = new Car('Ford', 2015);
```
 
# 14. Javascript - Promise

Promisi su obecanja da ce ili doci do greske ili da ce se potpuno izvrsiti neki asinhroni kod. 
Predstavljaju alternativu za callback-ove.. Omogucava pisanje citljivijeg
koda jer se izbegava ugnjezdavanje koje se javlja kod callback-ova (callback hell).

Objekat promise-a sadrzi kod koji zahteva cekanje na njegovo potpuno izvrsenje ("producing code"). 

Pomocu tog objekta se kasnije moze pozvati "Consuming code", kod koji ce konzumirati rezultat "producing"
koda, tj. koda koji se ceka.

Promise povezuje "Producing code" i "Consuming code"

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

Jedan od nacina koriscenja je i definisanje skrivenog identifikatora kojem se ne 
moze pristupiti slucajno iz nekog dela koda.

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

Ne mozemo da dobijemo vrednost koriscenjem pomocu koda `Symbol()`

`Symbol.for('key')` omogucava kreiranje jedinstvene vrednosti i njeno cuvanje u 
globalnom registru. Prvo se proverava da li vec postoji u njemu i ukoliko postoji 
onda se ona vraca, a ukoliko ne postoji onda se u njega unosi kreirana vrednost  
i key za koju je kreirana

Zbog toga: `Symbol.for('key') == Symbol.for('key')` vraca `true`

`Symbol.keyFor` je inverzna funcija funkcije `Symbol.for` koja za datu vrednost
vraca njen kljuc

Ovaj globalni registar vazi za celu aplikaciju.


# 17. Javascript - default vrednost parametra i rest parametar

## Default vrednost parametra

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

## Rest parametar

Rest parametar predstavlja parametar u kome se nalazi niz svih argumenata koje preostanu u pozivu datog metoda, tj.
niz argumenata koji sledi nakon niza keyword (moze se rec i "regularnih") parametara

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
na sledecu naredbu. Takvo izvrsavanje se naziva **blokirajucim (ili sinhronim)**
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
tu nit, umesto da se saceka na njegovo izvrsenje u toj niti task ce se 
izvrsiti u nekoj drugoj niti i time nece doci do blokiranja.

Ta druga nit se uzima iz worker pool-a. On sadrzi ogranicen broj niti

Blocking task moze da vrati rezultat preko callback-a
ili pomocu promise-a

Programeru nije vidljiv ovaj visenitni model jer je on sakrivan iza 
NodeJS API-a

# 21. NodeJS - async callback funkcija

(???)

Callback je funkcija koja se poziva nakon sto se zavrsi neki zadatak. Predstavlja jednu mogucnost za
izvrsenje nekog koda nakon sto se neki dogadjaj desi bez cekanja na njegovo izvrsenje. Kada se dogadjaj
dogodi callback se pozove od strane onoga ko obavestava o dogadjaju.

# 22. NodeJS - `process.nextTick` i `setImmediate`

Tick predstavlja jednu iteraciju petlje dogadjaja (event loop-a)

`process.nextTick(callback)` omogucava zakazivanje izvrsenja 
callback-a `callback` pre pocetka naredne iteracije, dok 
`setImmidiate(callback)` izvrsava prosledjeni callback na samom
pocetku sledece iteracije 

`process.nextTick(callback)` se uvek izvrsava pre `setImmidiate(callback)`

**Napomena**: `process` je globalni objekat

`process.nextTick` se koristi kada zelimo da postavimo prosledjeni callback 
na vrh event queue-a, tj. kada zelimo da se izvrsi odmah nakon sto se zavrsi
izvrsavanje trenutne funkcije.

`setImmediate` se koristi kada zelimo da se callback izvrsi nakon svih 
callback-ova IO dogadjaja koji se trenutno nalaze u listi dogadjaja

# 23. NodeJS - EventEmitter

Za emitovanje i registrovanje dogadjaja koristi se klasa `EventEmitter` 
iz modula `events`

Da bi se `EventEmitter` koristio u korisnickom objektu potrebno je 
da klasa ili funkcija sablon (funkcija kojom se kreira objekat)  
nasledjuje prototype klase `EventEmitter`

Primer za funkciju sablon:
```Javascript
const { EventEmitter } = require('events');

function sablonFunkcija() {
  this.metod = function(nekaVrednost) {
    this.emit('nazivDogadjaja', nekaVrednost);
  };
}

sablonFunkcija.prototype = EventEmitter.prototype;

const y = new sablonFunkcija();
```

Za isti dogadjaj je moguce registrovati vise listener-a

Listeneri se mogu registrovati sa `objekat.on('nazivDogadjaja', nekiListener)`
ili sa `objekat.addListener('nazivDogadjaja', nekiListener)`.

Ako hocemo da isto uradimo preko klase koristimo:
```Javascript
class Klasa extends EventEmitter {  // neophodno
  constructor() {                   // neophodno
    super();                        // neophodno
    this.metod = function(nekaVrednost) {
      this.emit('nazivDogadjaja', nekaVrednost);
    }
  }
}
```

# 24. Javascript - closure

Closure je mehanizam koji omogucava funkciji da pristupi podacima koje koristi 
iz spoljasnjeg okruzenja i nakon sto se to okruzenje napusti.

Iako bi se u drugim jezicima javila greska da data promenljiva vise ne postoji,
u JS se zbog closure-a cuva referenca na promenljive koje su u upotrebi od 
strane neke unutrasnje funkcije.

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

U ovom primeru svaki poziv kreira closure koji cuva vrednost promenljive `size`
za dati poziv.

# 25. NodeJs - callback chain

# 26. NodeJS - Baferi

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
poziciju od koje ce da se vrsi upis i kolika ce biti duzina upisa
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

# 27. NodeJS - Tokovi podataka

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
izazvati dogadjaj `end`


Ove klase se nalaze u modulu `streams`:
```Javascript
const { Writable, Readable } = require('streams');
```

Na objektu korisnicke klase koja nasledjuje neku stream klasu moguce je
registrovati listener-e `on('data')` i `on('end')`, gde prvi predstavlja
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

`_write` je metod koji treba da ima sledeci potpis `function(data, encoding, callback)`. 
Funkcija `callback` mora da se pozove unutar callback-a koji se dodeljuje `_write`-u`  

Primer:
```Javascript
let writer = new Writer(); // `Writer` nasledjuje `Writable`
writer.write("neki tekst", "utf8");
writer.end("Kraj"); // upisuje dati string i zatvara tok
```

Pored klasa `Readable` i `Writable` u modulu postoji klasa `Duplex` 
koja omogucava i citanje i pisnje nad istim objektom. Predstavlja 
kombinaciju klasa `Readable` i `Writable`

Jedan tok moze da se prosledi drugom pomocu metode `pipe`:
```Javascript
...
let reader = new Reader();
let writer = new Writer();
reader.pipe(writer)
```

# 28. NodeJS - Kompresija i dekompresija

Razne metode za kompresiju se mogu naci u modulu `zlib`

Svaki metod za kompresiju ima odgovarajucu metodu za dekompresiju,
`deflate`-`inflate`, `deflateRaw`-`inflateRaw`, `gzip`-`gunzip`

Svi metodi rade asinhrono (koriste callback)

Primer:
```Javascript
const zlib = require('zlib');

// isto izgleda i poziv za `deflateRaw` i `gzip`
zlib.deflate("neki sadrzaj koji ce se kompresovati", function(err, buffer) {...});
```

# 29. NodeJS - rad sa datotekama

Koristi se modul `fs`

Upis i ispis mogu da budu i sinhroni i asinhroni

Sinhrone metode dovode do blokiranja event loop-a, sto zna da bude pogodno ukoliko
naredni deo koda treba da radi sa fajlom.

Primer asinhronog upisa:
```Javascript
const fs = require('fs');

const options = {encoding: 'utf8', flag: 'w'};
fs.writeFile('../file.txt', 'neki tekst', options, function(err) {...});
```


Primer sinhronog upisa:
```Javascript
const fs = require('fs');
const fd = fs.openSync('../file.txt', 'w');

let bytes = fs.writeSync(fd, 'neki tekst', null, null);
fs.closeSync(fd);
```

Fajl moze i asinhrono da se otvori:
```Javascript
fs.open('../file.txt', 'w', function(err, fd) {
  ...
  fs.write(fd, "neki tekst", null, null, function(err, bytes) {...});   
  ...
  fs.close(fd);
})
```

Takodje je moguce upisivati u fajl pomocu tokova podataka:
```Javascript
const ws = fs.createWriteStream('../file.txt', options);
ws.write('neki');
ws.end('tekst');
```

Analogno ovim metodama postoje i metode za citanje. Uglavnom je razlika
samo u tome sto je rec o read-u a ne o write-u (i slicno, npr. `r` umesto `w` za flag)

`fs.readSync` kao drugi argument prihvata bafer u kojem ce biti smesteno ono
sto se ucita (u `fs.writeSync` na mestu tog argumenta bio je string koji se upisuje)

Sa `fs.read` je slicna situacija, umesto stringa prosledjuje se bafer, a pored toga 
callback ima i dodatni parametar za podatke koji su procitani (u odnosu na `fs.write`-ov
callback koji ima potpis `function(err, bytes)`)

Za neki fajl mozemo da dobijemo i status, tj. neke informacije o njemu:
```Javascript
// `stats` je objekat. Nad njim mozemo da zovemo razne metode, npr. metode za proveru tipa fajla (isFile, isSocket, ...)
fs.stats('../file.txt', function(err, stats) {...}); 
```

Citanje stavki iz nekog foldera:
```Javascript
fs.readdir('./', function(err, entries){...};)
```

Kreiranje foldera:
```Javascript
fs.mkdir('./noviFolder', function(err){...};)
```

Brisanje foldera:
```Javascript
fs.rmdir('./obrisati', function(err){...};)
```

Provera da li postoji neki fajl:
```Javascript
fs.exists('./file.txt', function(exists){...});
```

Promena imena nekog fajla:
```Javascript
fs.rename('staro.txt', 'novo.txt', function(err){...});
```

# 30. NodeJS - file system promise API

Metode u modulu `fs` imaju i verzije koje rade sa promise-ima
umesto sa callback-ovima

Nalaze se u `fs.promises`, npr. `fs.promises.mkdir(...)`

# 31. NodeJS - http server

Modul `http` omogucava kreiranje jednostavnog http servera. Uglavnom
se za to koristi modul `express` jer pruza dodatne funkcionalnosti
kao sto je jednostavno implementiranje rutiranja.

Objekat servera moze da se kreira na 2 nacina, implicitno i eksplicitno.

Kreiranje servera implicitno:
```Javascript
const server = http.createServer(options, requestListener); 
server.listen(port);
```

Kreiranje servera eksplicitno:
```Javascript
const server = http.createServer();
server.on('request', requestListener);
server.listen(port);
```

`requestListener` je funkcija koja ce obraditi dati zahtev. 
Prihvata: objekat klase `IncomingMessage` i objekat klase `ServerResponse`

Primer `requestListener`-a:
```Javascript
(req, res) => {
  res.writeHead(200, {'Content-Type' : 'application/json'});
  res.end(JSON.stringify({data: 'Hello World!'}));
}
```

Jedna od primena `options`-a je definisanje parametara za https (public key, ...)

Oba parametra metoda `createServer` su opciona (sto se moze i primetiti u primeru
za eksplicitno kreiranje servera)

Rutiranje se implementira tako sto se iskoriste metodi za citanje
podataka iz modula `fs`

# 32. NodeJS - http client

Http client omogucava slanje http zahteva iz obicno js aplikacije ili sa servera.

Potpis metoda
```Javascript
http.request(options[, callback]);
http.request(url[, options][, callback]);
```

Metod `http.request` kreira objekat klase `http.ClientRequest`

Primer:
```Javascript
const http = require('http');
const options = {
  hostname: 'localhost',
  port: '8080',
  path: '/hello.html'
};

const req = http.request(options, function(response) {
  let data = '';
  response.on('data', function(chunk) {
    data += chunk;
  })

  response.on('end', function() {
    // obrada podataka iz promenljive `data`
  })
});

req.end();
```

# 33. NodeJS - predaja podataka (http)

Primer klijentskog dela:
```Javascript
const http = require('http');

const options = {
    host: 'localhost',
    port: '8000',
    method: 'POST' // BITNO
};

const req = http.request(options, function(response) {
    let data = '';
    
    response.on('data', function(chunk) {
        data += chunk;
    });

    response.on('end', function() { 
        console.log(data);
    });
});
req.write('{"nekiProperti": "vrednost"}');
req.end();
```

Primer serverskog dela:
```Javascript
const http = require('http');

const server = http.createServer(function(req, res) {
    let data = '';
    
    req.on('data', function(chunk) {
        data += chunk;
    });

    req.on('end', function() { 
        // try-catch blok se koristi zbog mogucnosti da nema `nekiProperti` propertija
        // ili da primljeni podaci nisu validan json 
        try {
            let obj = JSON.parse(data);
            console.log('neki properti: ' + obj.nekiProperti);
            
            res.writeHead(200);
        } catch(e) {
            res.writeHead(400);
        }

        res.end('response');
    });
});

server.listen(8000);
```

