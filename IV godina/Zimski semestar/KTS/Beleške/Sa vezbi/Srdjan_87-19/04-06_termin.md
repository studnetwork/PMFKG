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