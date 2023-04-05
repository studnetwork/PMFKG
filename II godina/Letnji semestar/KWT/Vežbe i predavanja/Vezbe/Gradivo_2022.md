# Okvirni pregled gradiva 2022/23

---

# Pojmovi

Opšte
- Internet, Web
- Klijent, Server
- Web Browser, Web Server

Tehnologije
- HTML, CSS, JavaScript
- HTML elementi i atributi


# HTML

## Struktura

- `!DOCTYPE`
- Struktura dokumenta (`html`, `head`, `body`)
- Metapodaci (`meta`, `title`)


## Tekst

- _Heading_ (`h1` - `h6`)
- _Paragraph_ (`p`)
- _Strong_, _Em_ (`strong`, `em`)
- _Superscript_, _Subscript_ (`sup`, `sub`)
- Manualno formatiranje teksta (`pre`)
- Kod (`code`)
- Skracenica (`abbr`); atribut: `title`
- _Bi-Directional-Override_ (`bdo`)
- Izbrisan i Dodat tekst (`del`, `ins`)
- Mali tekst (`small`)
- _Thematic break & Line break_ (`hr`, `br`)
- _Anchor_ (`a`); atribut: `target="_blank"`
- Specijalni karakteri (`&lt; &gt; &nbsp; &nbsp; &nbsp; &nbsp; &copy;`)
- _Inspector u Browser-u, struktura stranice_


## Slike

- Slika sa spoljašnje adrese; `src="http://..."`; atributi: `alt`, `height`, `width`
    - _Network deo u Inspector-u u Browser-u, kako je slika dobavljena preko mreze HTTP zahtevom_
- Slika iz foldera images; `src="images/..."`
- Slika u linku; kombinovanje tagova, `img` u `a` tagu


## Tabele

Tagovi
- `table`
- _table row_ (`tr`)
- _table data_ (`td`)
- _table header_ (`th`)
    - headeri u prvom redu
    - headeri kao prva celija u svakom redu

Atributi
- `rowspan`
- `colspan`
- `cellspacing`
- `cellpadding`

Sekcije tabele
- `thead`
- `tfoot`
- `tbody`
- Pregled voih sekcija u Inspectoru


## Liste

- _Ordered list_ (`ol`); atribut `type`: `1`, `a`, `A`, `i`, `I`
    - _list item_ (`li`)
- _Unordered list_ (`ul`)
    - _list item_ (`li`)
- _Description list_ (`dl`)
    - _term_ (`dt`)
    - _description_ (`dd`)
- Ugnjezdene liste

## Inputi

- `form`
    - get metoda na neki postojeci url (`https://www.w3schools.com/action_page.php`)
    - post metoda na `MAILTO:name@site.com`, atribut: `enctype="text/plain"`
- `input`; vrednosti za `type` atribut:
    - `text`, `email`, `password`
    - `radio`, `checkbox`
    - `file`
    - `hidden`, `submit`, `reset`
- `select`, `option`, `optgroup`
- `textarea`; atributi: `rows`, `cols`
- `button` (slika unutar dugmeta)
- `label`
- `fieldset`, `legend` (forma unutra)

## IFrame

- `iframe`, rade se 3 varijante:
    - obican
    - prazan, u kome se otvara neki sajt pomocu klika na link (`a`)
    - sa YouTube klipom


# CSS

## Selektori

- element (npr. `a`, `h1`, ...) 
- class (`.`)
- id (`#`)

## Properties

- _layout_
    - `width`
    - `height`
    - `paddign`
    - `margin`
    - `float`
    - `clear`
    - `min-height`
- _background_
    - `background-color`
    - `background-image`
    - `background-repeat`
    - `background-position`
    - `background-attachment`
    - `background-size`
- _text_
    - `color`
    - `text-indent`
    - `text-decoration`
    - `text-aligh`
    - `line-height`
    - `letter-spacing`
- _font_
    - `font-size`
    - `font-style`
    - `font-weight`
    - `font-family`
    - `font-variant`

## TODO: Dodati pojmove sa 4. i 5. termina


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

### Izvršavanje koda
```js
funkcija(17) // poziv (validno)

function funkcija(x) // definicija
{
    // ...
}

funkcija(33) // poziv (validno)
```

### String
#### Literali
```js
let s1 = "Tekst"
let s2 = 'Tekst'
let s3 = `Tekst` // template literal
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

#### On Click
```html
<p onclick="fn('value')">Paragraf</p>

<script>
    function fn(x) {
        // ...
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
    function fn() {
        // x: referenca na HTMLElement objekat
        let x = document.getElementById('p1')
    }
</script>
```

### Izmena HTML elementa

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
Rezultat je ekvivalentan HTML kodu:
```html
<div id="d1">
    <p>Novi paragraf</p>
</div>
```
Source: [MDN | innerHTML](https://developer.mozilla.org/en-US/docs/Web/API/Element/innerHTML)


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
- [_**Lista HTML element interfejsa**_](https://developer.mozilla.org/en-US/docs/Web/API/HTML_DOM_API#html_element_interfaces_2) (Za svaki od interfejsa u listi postoji detaljna dokumentacija, klik na link)

![Class Tree](https://i.stack.imgur.com/r3Ci6.png)