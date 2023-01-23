Test moze da se ignorise koriscenjem anotacije `@Ignore`

Primer
```Java
@Ignore
@Test
public void nekiMetod() {
    ...
}
```

# Mocking

Koristimo biblioteku `Mockito`.

Snipped za `pom.xml`
```XML
<dependency>
    <groupId>org.mockito</groupId>
    <artifactId>mockito-core</artifactId>
    <version>4.3.1</version>
    <scope>test</scope>
</dependency>
```

Mock objekat se kreira sa `Mockito.mock(???.class)`.

Mock-ujemo tako sto definisemo sta ce se dogoditi u odredjenom slucaju. 
Za to koristimo `Mockito.when()` metodu. Nakon toga pozivamo neki od then metoda
nad povratnom vrednoscu `when`-a: `Mockito.when(???).then???(???)`.

Neki od then metoda:
* `thenReturn(???)`
* `thenThrow(???)`

Mockito biblioteka sadrzi i matcher-e koji se mogu koristiti za match-ovanje
parametra u `when` delu, npr:
```Java
Mockito.when(klasaKojuKoristiSUT.metod(Mockito.anyString()))
    .thenReturn(true);
```

Mock iz ovog primera ce vratiti vrednost `true` ukoliko se pozove `klasaKojuKoristiSUT.metod` sa
bilo kojim string parametrom.

Da bi smo utvrdili da li je neki metod pozvan i koliko puta je pozvan koristimo:
```Java
Mockito.verify(this.mockovanObjekat).metodIzWhena1();           // proverava da li je pozvan tacno 1
Mockito.verify(this.mockovanObjekat, never()).metodIzWhena2();  // proverava da li metod nikada nije pozvan
Mockito.verify(this.mockovanObjekat, times(3)).metodIzWhena3(); // proverava da li je metod pozvan tacno 3 puta
```

Postoji jos dosta toga sto je moguce uraditi kao sto je provera redosleda poziva metoda mock-ovanog objekta
i slicno, ali to nije relevantno za ovaj kurs.

## Koriscenjem `MockitoJUnitRunner`-a

`@RunWith(MockitoJUnitRunner.class) ` je runner koji automatski inject-uje mock-ove tamo 
gde je potrebno na osnovu anotacija `@Mock` i `InjectMocks`

`@Mock` kreira mock objekat

`@InjectMocks` inject-uje mock-ove oznacene sa `@Mock` u objekat na koju referise
promenljiva iznad koje se ova anotacija nalazi.

Primer sa bacanjem exception-a kada odredjeni metod dobije neki string
```Java
@RunWith(MockitoJUnitRunner.class)
public class NekiTest{

    @InjectMocks
    private SystemUnderTest sut; // poziva `.nekiMetod(String s)` klase `NekaKlasa`

    // ako nema default-ni konstruktor, moramo da izaberemo kojim konstruktorom se kreira objekat
    // private SystemUnderTest sut = new SystemUnderTest(1,2,3); 

    @Mock
    private NekaKlasa nekaKlasa; // sadrzi `.nekiMetod(String s)`

    @Test
    public void test() {
        // arrange
        Mockito.when(this.nekaKlasa.nekiMetod(Mockito.anyString()))
            .thenThrow(new IllegalArgumentException());
        ...
        sut.nekiDrugiMetod("test"); // ovaj metod interno poziva `nekaKlasa.nekiMetod("test")`
        ...
    }
    ...
}
```

## Koriscenjem metode `Mockito.mock`

Primer sa bacanjem exception-a kada odredjeni metod dobije neki string
```Java
public class NekiTest{

    private SystemUnderTest sut;
    private NekaKlasa nekaKlasa;

    @Before
    public void setUp() {
        this.nekaKlasa = Mockito.mock(NekaKlasa.class);
        this.sut = new SystemUnderTest(nekaKlasa);
    }

    @Test
    public void test() {
        // arrange
        Mockito.when(this.nekaKlasa.nekiMetod(Mockito.anyString()))
            .thenThrow(new IllegalArgumentException());
        ...
        sut.nekiDrugiMetod("test");
        ...
    }
    ...
}
```

`@Test` deo je isti kao u prvom pristupu sa runner-om.

Nekada je potrebno koristi ovaj pristup jer se test pokrece sa drugim 
runner-om (npr. `Parameterized.class`)

# Testiranje standardnog izlaza

Ukoliko je npr. potrebno da testiramo da li metod kao rezultat svog
izvrsavnja ima odgovarajuci ispis na standardni izlaz onda je potrebno
da izvrsimo redirekciju izlaza pre poziva te funkcije.

Redirekciju podataka vrsimo sa `System.setOut` u neku promenljivu tipa `ByteArrayOutputStream`.

Nakon zavrsetka testa je **neophodno da se output destinacija programa vratiti**
**na standardni izlaz** kako ne bi uticali na rad ostalih testova.

Primer
```Java
    // cuvamo standardni izlaz kako bi posle mogli da se vratimo na pocetno stanje
    private final PrintStream originalOut = System.out;

    ...

    @Test
    public void testirajIspis() {
        // arrange
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        System.setOut(new PrintStream(out));
        ...
        // act 
        underTest.metodKojiVrsiIspis();
        
        // assert
        System.setOut(originalOut));
        
        // `trim()` koristimo kako bi smo uklonili `\n` koji se dodaje na kraj
        // prosledjenog stringa u metodu `System.out.println` 
        assertEqual("neki string", out.toString().trim());
        ...
}
```

# Hamcrest

Snippet koji se dodaje u `pom.xml`
```
<dependency>
    <groupId>org.hamcrest</groupId>
    <artifactId>hamcrest-all</artifactId>
    <version>1.3</version>
    <scope>test</scope>
</dependency>
```

**Hamcrest** je biblioteka koja nudi razle alate za match-ovanje.

U testingu se koristi jer olaksava definisanje tvrdnji kojima se
proverava rezultat metoda koji testiramo.

Primeri:
```Java
import org.hamcrest.MatcherAssert;
import static org.hamcrest.Matchers.*;

// proverava da li promenljive referisu isti objekat
MatcherAssert.assertThat(ACTUAL, sameInstance(EXPECTED));

// proverava da li promenljive imaju isti sadrzaj 
// (u slucaju listi da li imaju elemente istih vrednosti, u odgovarajucem redosledu)
MatcherAssert.assertThat(ACTUAL, equalTo(EXPECTED));

// proverava da li lista sadrzi element `first`
MatcherAssert.assertThat(list, hasItem(first));

MatcherAssert.assertThat(map, hasKey(KEY));  
MatcherAssert.assertThat(map, not(hasKey(INCORRECT_KEY)));

MatcherAssert.assertThat(actualString, is("nekiStr"));

MatcherAssert.assertThat(actualString, not("nekiString"));
MatcherAssert.assertThat(actualString, not(isEmptyOrNullString()));

// proveriti da li vise uslova vazi
MatcherAssert.assertThat(actualString, 
    allOf(
        not("nekiString"),
        not(isEmptyOrNullString()),
        startsWith("nek")
        )
    );

// proveriti da li je broj u blizini broja 10 sa odstupanjem 0.01
MatcherAssert.assertThat(actualNumber, closeTo(10, 0.01));

MatcherAssert.assertThat(list, hasItems(10, 20));
MatcherAssert.assertThat(list, everyItem(greaterThan(0)));
MatcherAssert.assertThat(list, contains(20, 13));
MatcherAssert.assertThat(list, containsInAnyOrder(20, 13));

MatcherAssert.assertThat(array, arrayWithSize(3));
MatcherAssert.assertThat(array, hasItemInArray(7));
MatcherAssert.assertThat(array, arrayContaining(20, 13));
MatcherAssert.assertThat(array, arrayContainingInAnyOrder(20, 13));
```

*Napomene*:
* `assertThat` postoji i biblioteci `JUnit` pa je zbog toga potrebno eksplicitno pozivati tu metodu sa `MatcherAssert.assertThat` (za to je neophodan import `import org.hamcrest.MatcherAssert`)
* `contains`, `containsInAnyOrder`, `arrayContaining` i `arrayContainingInAnyOrder` zahtevaju da svi elementi budu navedeni (ako niz/lista sadrzi 1, 2 i 3 onda je neophodno da se ovim metodima proslede isti ti brojevi)
* `contains` i `arrayContaining` zahtevaju da elementi budu odgovarajucem redosledu 
