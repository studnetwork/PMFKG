# 1. 

Nginx je fleksibilan HTTP server koji se moze konfigurisati na razlicite nacine.
On je takodje i reverse proxy server, mail proxy server i genericki TCP/UDP sever.

# 2. 

Funkcionalnosti koje nginx omogucava:
* load balancing
* serviranje statičkih file–ova
* proxy ponasanje, tj. može da "sakrije“ razne servere koji rade na različitim portovima 
i time korisniku stvori utisak da se radi o samo jednom serveru koji radi na jednom portu
* reverse proxying (sa kesiranjem)
* kesiranje za razne web servere
* autoindexing
* skalabilnost

# 3. 

ECMAScript je standard koji osigurava interoperabilnost izmedju web stranica 
na razlicitim pregledacima (browser-ima). Najcesce se koristi za pisanje skripti 
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
          
# 4. 

`"use strict";` oznacava kod koji bi trebao da se izvrsi
u striktnom modu ("strict mode")

Pomaze pri pisanju "clean" i "secure" JS koda. 

Ono sto je smatrano losom sintaksom koja je tolerisana 
ili ignorisana ce u ovom modu **uzrokovati gresku**

Ova direktiva je u stvari samo jedan string koji se navodi
**na pocetku fajla** ili **na vrhu neke funkcije** (od cega zavisi
i njen scope). Oni pregledaci koji je podrzavaju ce je 
izvrsiti, a oni koji je ne podrzavaju ce je samo ignorisati
i tretirati kao obican string.


# 5. 

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

# 6. 

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

# 7. 

Property-ji objekta imaju meta podatke:
* `value`
* `writable` - da li vrednost moze da se promeni
* `enumerable` - da li moze da se enumerise (pristupi u `for..in`-u, `stringify`-u, itd..)
* `configurable` - da li moze da se konfigurise (izmene meta podaci nakon definisanja)

Propery objekta moze da se definise sa:
```Javascript
Object.defineProperty(objekatNadKojimDefinisemo, "nazivPropertija", {
    value: "vrednost",
    writable: false,
    enumerable: true
})
```

# 8. 

`Object.create(prototip)` kreira se novi objekat na osnovu nekog 
drugog objekta (prototipa). Imace iste podatke i strukturu

Ima i drugi argument koji predstavlja objekat u kome se mogu definisati 
novi propertiji (sa svojim metapodacima) koji ce biti dodati novom objektu

# 9. Razlike izmedju `let`, `var` i `const` 

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

# 10. 

`for..of` i `for..in` omogucavaju prolazak kroz iterabilne objekte 

`for..of` omogucava prolazak da se pri svakom prolazu dobije naredna vrednost (
vrednost propertija `next`), dok `for..in` pri svakoj interaciji vraca indeks 

`for` je standardan `for` koji se pojavljuje u vecini jezika:
```Javascript
for (initialization; condition; afterthought)
  statement
```

# 11. 

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

# 12. 

Mape omogucavaju da se definisu mapiranja kljuceva u odgovarajuce vrednosti.

Kao kljuc mozemo koristiti i neki objekat

Kreiranje i dodavanje novog mapiranja:
```Javascript
const apples = {name: 'Apples'};

const fruits = new Map();
fruits.set(apples, 500);
```

Redosled kljuceva je isti kao redosled u kojem su oni dodavani.

Skupovi (`Set`) su kolekcije jedinstvenih vrednosti. Svaka vrednost se moze pojaviti
samo jednom. 

Skupovi mogu imati vrednosti bilo kog tipa podatka.

Primer:
```Javascript
const letters = new Set();

letters.add('a');
letters.add('b');
```

# 13. 

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
 
# 14. 

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

# 15. 

JS Fetch API predstavlja interfejs koji omogucava pregledacima da naprave http zahteve

Fetch API koristi promise-e

Primer:
```Javascript
fetch(file)
.then(f => f.text())
.then(txt => console.log(txt));
```
 
 
# 16. 

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

Ovaj globalni registar vazi za celu aplikaciju.


# 17. 

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