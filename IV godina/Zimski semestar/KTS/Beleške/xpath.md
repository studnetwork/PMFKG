# Kratki pregled

XPath je putanja do elementa na HTML stranici, kao putanja do nekog foldera u fajl sistemu.

## Direktni potomak (`/`)

Putanja `/div` oznacava `div` element koji se nalazi direktno u root-u stranice.

PUtanja `/div/p` oznacava `p` element koji se nalazi direktno u `div` elementu koji se nalazi direktno u root-u stranice.

Itd.


## Ne-direktni potomak (`//`)

Putanja `//div` oznacava `div` element koji se nalazi negde unutar root-a stranice, ne mora da bude direktni potomak, moze potomak unutar potomka, itd.

Putanja `//div//p` oznacava `p` element koji se nalazi negde medju potomcima `div` elementa koji se nalazi negde medju potomcima root-a stranice.

Itd.


## Detalji elementa

Nakon navodjenja elementa u `[]` se navode detalji koje taj element treba da ima.

Putanja `//div[p]` selektuje `div` element koji kao svog potomka ima `p` element.

Putanja `//div[p='Text']` selektuje `div` element koji koa svog potomka ima `p` element sa textom `Text` u sebi.

Putanja `//div[@name]` selektuje `div` element koji ima atribut `name`.

Putanja `//div[@name='Text']` selektuje `div` element koji ima atribut `name` sa vrednoscu `Text`.


## Primeri

`//div[@id='1']/span[a="Link"]`
- Selektuje `span` element ciji je potomak `a` element sa tekstom `Link`, i (`span` element) direktni je potomak `div` elementa sa `id`-jem `1` koji se nalazi negde unutar stranice (ne mora direktno u root-u)
