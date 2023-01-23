# Page Object Model (POM)

Ideja je da se svaka stranica predstavi kao jedna klasa (objekat).

Ima propertije i metode.

Properti je nesto sto **identifikuje** jedan deo (ili stvar) na stranici.

Sve page klase se nasledjuju iz apstraktne bazne klase koja sadrzi sve ono 
sto je potrebno da ima svaka klasa, na primer `WebDriver` koji se dobija preko 
konstruktora (jer na taj nacin imamo slabo vezivanje page klase i `WebDriver`-a)

Propertiji koji sadrze `By` objekte se instanciraju odmah.
Npr:
```Java
By nameInputBy = By.xpath("//input[@id='name']");
```


Akcije stranice su predstavljene metodama klase.

Propertiji su privatni, a metodi javni.

---

Kada se predje na drugu stranicu potrebno je da se vrati objekat
koji predstavlja tu stranicu

Prosledjivanje linkova preko konstruktora klase date stranice **nije dobra** praksa
jer onda nije moguce ispravko proveriti rad linkova. Na netu se mogu naci tutorijali 
koji to koriste, iako ne bi trebalo.

---

U `@BeforeSuite`-u se setupuje driver

A pre svakog testa (koriscenjem `@BeforeMethod`) vrsi se priprema:
instancira se driver, vrsi navigacija na odgovarajucu stranicu i
instancira objekat te stranice

---

Koriscenje POM-a omogucava razdvajanje testa od stvari koje su vezane za samu stranicu.

Svaki test (klasa) sadrzi referencu objekata same stranice i referencu
web drivera

Jedan od nacina imenovanja propertija jeste da se na kraju naziva stavi `By`
kako bi se npr. izbegle situacije u kojima se ocekuje `By` objekat a 
prosledjuje string gde obe promenljive imaju isti naziv

Za svaku akciju na stranici se pravi metod, npr. za unos podataka u polje, za 
button click, ...




Akcija submitovanja podataka obuhvata samo klik na submit button jer se 
moze pretpostaviti da je to odradjeno akcijama za popunjavanje polja.




# Testiranje sa cekanjem


Za neke stvari je potrebno sacekati neko vreme pre nego sto se izvrsi akcija
jer zahtevaju odredjeno vreme kako bi se neki elementi ucitali (npr. 
odgovor servera dodje kasnije ili koriscenje modala jer treba vremena
da se potpuno ucitaju)


`WebDriverWait` je objekat koji se koristi za cekanje. Prosledjuje se 
referenca drajvera i maksimalna duzina cekanja (koristi se objekat
`Duration`)

`Duration` ima metod `.ofSeconds(x)`


`wait.until(uslov)` - preuzima element iz uslova ako uslov bude ispunjen u
definisanom periodu

Za uslov se koristi neki metod iz `ExpectedConditions.???`, 
na primer `ExpectedConditions.visibilityOfLocatedElement(el)`


Ako istekne vreme dolazi do `TimeoutException`-a
