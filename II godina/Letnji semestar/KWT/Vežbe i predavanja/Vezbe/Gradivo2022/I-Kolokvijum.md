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


