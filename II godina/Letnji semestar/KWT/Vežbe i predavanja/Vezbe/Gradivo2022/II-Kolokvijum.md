# JavaScript

## Povezivanje sa stranicom
### Interni `<script>` tag

`index.html`
```html
HTML kod...

<script>
    // JavaScript kod...
</script>

HTML kod...
```

### Eksterni `.js` fajl

`index.html`
```html
HTML kod...
<script src="skripta.js"></script>
HTML kod...
```
`skripta.js`
```js
// JavaScript kod...
```

Linkovi:
- [Where should I put `<script>` tags in HTML markup?](https://stackoverflow.com/a/24070373)

## Kodiranje

### Komentari
```js
// Inline...

/*
Multiline
...
*/
```

### Promenljive
```js
// Novi nacin (ES6 - 2015)
let x = 33   // promenljiva
const c = 49 // konstanta

// Stari nacin
var v = 17   // izbegavati
```
- _nije obavezno zavrsiti liniju sa `;`_
- [_JavaScript Let vs Var vs Constant_](https://youtu.be/XgSjoHgy3Rk)

#### Scope
```js
let globalna = 0

function funkcija() 
{
    let lokalna = 0
}
```

#### Dynamic-typing
```js
let x = 17
x = 'Tekst'
x = function() { ... }
```

#### Redeclaration (error)
```js
let x = 17
let x = 33
// Uncaught SyntaxError: redeclaration of let x
```

### Operacije i izrazi
```
Aritmeticke:
  + - * / %
Logicke:
  == != === !==
  && || !
```
```js
4 * 3       // => 12
12 / 5      // => 2.4
10 % 4      // => 2
'str ' + 17 // => 'str 17'

4 == 4      // => true
4 == '4'    // => true
4 === '4'   // => false

true == 1   // => true
true === 1  // => false

// itd.
```

### String
#### Literali
```js
let s1 = "Tekst"
let s2 = 'Tekst'
let s3 = `Tekst` // template literal
```

### Izvršavanje koda
```js
funkcija(17) // poziv funkcije (validno)

function funkcija(x) // definicija funkcije
{
    // ...
}

funkcija(33) // poziv funkcije (validno)
```

### Grananje (if-else)
```js
if(uslov) {
    // ...
} else if(uslov) {
    // ...
} else {
    // ...
}
```

### Petlje
#### While
```js
while(uslov) {
    // ...
}
```
#### For
```js
for(let i = 0; i < 10; i++) {
    // ...
}
```

### Text output
#### Log
```js
console.log('Tekst')
```
#### Alert
```js
alert('Tekst')
```


## Interakcija sa stranicom

### Events

```html
<!-- [Klik] na element -->
<p onclick="fn()">On Click</p>

<!-- Pointer [Preko] ili [Izvan] elementa -->
<p onmouseover="fn()">On Mouse Over</p>
<p onmouseout="fn()">On Mouse Out</p>

<!-- Na [Pritisak] ili [Pustanje] klika -->
<p onmouseup="fn()">On Mouse Up</p>
<p onmousedown="fn()">On Mouse Down</p>

<!-- Na [Pritisak] dugmeta na tastaturi -->
<input type="text" onkeydown="fn()">

<script>
    function fn() {
        // ..
    }
</script>
```

### Pristup HTML elementima
JavaScript je objektno-orjentisani jezik. HTML elementima pristupamo pomoću reference na objekat, a ta referenca se može dobiti na više načina:

#### `this`
```html
<p onclick="fn(this)">Paragraf</p>

<script>
    function fn(x) {
        // x: referenca na HTMLElement objekat
    }
</script>
```

#### `getElementById()`
```html
<p id="p1">Paragraf</p>

<script>
    // x: referenca na HTMLElement objekat
    let x = document.getElementById('p1')
</script>
```

### Izmena HTML elementa

#### `document.write()` - Radikalna izmena!

```js
document.write('Ovaj tekst je postao jedini sadrzaj stranice')
document.write(', a sada je dodat i ovaj tekst')
document.write(', i jos jedan...')
```

Neka od svojstava HTML elemenata koja se mogu menjati:

#### `innerHTML`
Property `HTMLElement` objekta koji uzima (get) ili postavlja (set) sadržaj elementa
```html
<div id="d1">
    <span>Stari span</span>
</div>

<script>
    // x: referenca na HTMLElement objekat
    let x = document.getElementById('d1')
    x.innerHTML = '<p>Novi paragraf</p>'
</script>
```
pomocu eventa, JS kod u HTML-u:
```html
<div onclick="this.innerHTML='<p>Novi paragraf</p>'">
    <span>Stari span</span>
</div>
```
Rezultat je ekvivalentan HTML kodu:
```html
<div id="d1">
    <p>Novi paragraf</p>
</div>
```
Source: [MDN | innerHTML](https://developer.mozilla.org/en-US/docs/Web/API/Element/innerHTML)


#### `className`
```html
<p id="p1" class="c1">Paragraf</p>

<script>
    // x: referenca na HTMLElement objekat
    let x = document.getElementById('p1')
    x.className = 'c2 c3'
</script>
```
Rezultat je ekvivalentan HTML kodu:
```html
<p id="p1" class="c2 c3">Paragraf</p>
```


#### `style`
Property `HTMLElement` objekta preko koga se postavljaju ili citaju vrednosti svojstava inline CSS-a tog elementa (svojstva postavljena preko `style` attributa)
```html
<p id="p1">Paragraf</p>

<script>
    // x: referenca na HTMLElement objekat
    let x = document.getElementById('p1')
    x.style.fontSize = '25px'
</script>
```
Rezultat je ekvivalentan HTML kodu:
```html
<p id="p1" style="font-size: 25px;">Paragraf</p>
```
Source: [MDN | style](https://developer.mozilla.org/en-US/docs/Web/API/HTMLElement/style)


#### `href`
Property `HTMLAnchorElement` objekta
```html
<a id="a1" href="https://google.com">Paragraf</a>

<script>
    // x: referenca na HTMLAnchorElement objekat
    let x = document.getElementById('a1')
    x.href = 'https://duckduckgo.com'
</script>
```

## HTML elementi

- Različiti HTML elementi imaju različite osobine. Na primer, [HTMLAnchorElement](https://developer.mozilla.org/en-US/docs/Web/API/HTMLAnchorElement) predstavlja `a` HTML element i poseduje svojstvo `href`, dok [HTMLImageElement](https://developer.mozilla.org/en-US/docs/Web/API/HTMLImageElement) predstavlja `img` HTML element i poseduje svojstvo `src`, itd.
- [_**Lista HTML element interfejsa**_](https://developer.mozilla.org/en-US/docs/Web/API/HTML_DOM_API#html_dom_api_interfaces) (Za svaki od interfejsa u listi postoji detaljna dokumentacija, klik na link)

![Class Tree](https://i.stack.imgur.com/r3Ci6.png)