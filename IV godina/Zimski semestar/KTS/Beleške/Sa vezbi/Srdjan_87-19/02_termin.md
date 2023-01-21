U testu mi izvodimo neku akciju i onda nakon toga
definisemo koje tvrdnje moraju da budu zadovoljene.
Njima se proverava uspesnost testa, tj. rezultat
izvrsenja te akcije.

Metode za definisanje tvrdnji se mogu naci u klasi
`Assert` iz biblioteke `JUnit`

Za oznacavanje testnog metoda koristi se anotacija
`@Test`

Sa leve strane testnog metoda, izmedju rednog broja
linije i tog metoda nalazi se dugme preko kojeg je
moguce pokrenuti dati test.


# Struktura testova
## AAA

`AAA` predstavlja:
* Arrange (priprema i kreiranje onoga sto je neophodno za datu akciju, mockovanje, ...)
* Act (izvrsenje akcije, odnosno pozivanje metoda koji se testira)
* Assert (provera rezultata)

```Java
@Test
public void nekiTest() {
    // Arrange
    Nesto x = ???;

    // Act
    z = x.y(123);

    // Assert
    Assert.assertEquals(z, ???)
}
```

## Behavior-driven testing (BDT)

`Given / When / Then`

# Konvencije

Naziv testne klase se zavrsava sa `Test`

Testna klasa treba da bude obicna (nema razloga
da bude `abstract` ili `final`) `public` klasa

Putanja treba da bude identicna kao putanja 
originalne (samo se razlikuje po 1 folderu po kom
je produkcioni kod razdvojen od testnog)

Testna klasa ima ista prava pristupa kao i klasa
koja se testira


`SUT` - system under test

Testovi trebaju da budu nezavisni jedan od drugog
(odnosi se na same testove, a ne i na metode koje
se testiraju (?))


Objetki drugih klasa se mock-uju kako bi se izbeglo
da test pada zbog problema u toj drugoj klasi.


# Izuzetci

Klasa ne bi trebala da podize izuzetke koji
se ne ocekuju (koji npr. nisu predvidjeni u
specifikaciji). 

Ako se neki izuzetak ocekuje onda je potrebno
uhvatiti ga:
1. try-catch blokom
2. anotacijom (dekoraterom) iznad metoda u kojem se to dogadja

Ako se ocekivani izuzetak ne dogodi onda ce test
pasti (zuta ikonica; zelene boje je kada je test
prosao, a crvene ako je doslo do neocekivanog 
problema tokom izvrsavanja testa)

## Testiranje dolaska do izuzetka
### Pomocu anotacije

```Java
@Test(expected = ???.class)
public void nekiMetod(){
    ...
}
```

Ako se dodje do exception-a `???` u toku izvrsenja
metoda `nekiMetod` onda je test prosao.

**Napomena**:
    exception moze biti uzrokovan necim drugim, 
    drugom greskom, zbog cega bi test prosao iako 
    mozda nije trebao da prodje. U tom slucaju je
    bolje koristiti try/catch metod


### Pomocu try/catch bloka

U ovom pristupu se koristi i metod `fail` jer
ukoliko ne dodje do exception-a pri pozivu metoda
koji se testira onda ce se nastaviti izvrsavanje
koda u `try`-u pa nakon toga koda izvan `try`-a i 
test ce onda proci ako ne dodje do neke greske.

Metod `fail` uzrokuje pad testa uz ispis poruke, ako
se ona prosledi.

```Java
@Test
public void nekiMetod() {
    
    ...

    try {
        x = metodKojiSeTestira(y);

        // ovo se koristi kako bi se
        fail("poruka"); 
    } catch () {
        // neki kod, npr. assert
    }
}
```


# Before

Kako se kod ne bi ponavljao (`DRY` princip) i 
kako bi smo izolovali testove kreiranjem novog
objekta za svaki test, koristimo anotaciju `@Before`

Ona oznacava metod koji ce se izvrsiti pre nego sto
se zapocne obavljanje svakog pojedinacnog testa.
Dodje kao priprema pred test, koja se obavlja i za
svaki drugi test. Specificne pripreme svakog testa
se nalaze u njihovog `// Arrange` delu
