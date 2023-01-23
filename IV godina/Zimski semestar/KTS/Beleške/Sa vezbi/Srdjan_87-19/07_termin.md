# TestNG
Dodavanje logger dependency-a je neophodno za rad TestNg-a

Importi za logger (**ne radi** sa `Logger`-om iz `util` paketa):
```Java
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
```
    
Dobra praksa je da se umesto print-ova koristiti logger    

---

Neki od metoda biblioteke `TestNG` koje cemo koristiti
```Java
@BeforeSuite  
@BeforeClass  
@BeforeTest  
@BeforeMethod  

@AfterSuite
@AfterClass  
@AfterTest  
@AfterMethod  
```

Napomena: `@xTest` se odnosi na skup testova (metoda, a ne na pojedinacan metod)

## Parametrizovani testovi

```Java
@Parameters("{ime1IzXMLa, ime2IzXMLa}")      // obratiti paznju: parametri se nalaze unutar `{}`
@Test  
public void metodKojiSeTestira(Type1 ime1KojeNeMoraDaSePoklapaSaXMLom, Type2 ime2KojeNeMoraDaSePoklapaSaXMLom) {
    ...
}
```

Izgled XML-a kojim se definise testing suite
```XML
<!DOCTYPE suite SYSTEM "https://testng.org/testng-1.0.dtd" >
<suite name="Naziv suite-a">               <!-- moze da ima i atribute: thread-count="4" parallel="methods" -->
    <parameter name="ime1IzXMLa" value="vrednost1"/>
    <parameter name="ime2IzXMLa" value="vrednost2"/>

    <test name="Naziv testa">
        <parameter name="ime3IzXMLa" value="vrednost3"/>

        <classes>
            <class name="org.imi.putanja.do.Klase1Test"/>
            <class name="org.imi.putanja.do.Klase2Test">
                <methods>
                    <include name="nazivMetodaKojiCeSeUkljuciti1"></include>
                    <include name="nazivMetodaKojiCeSeUkljuciti2"></include>
                </methods>
            </class>
        </classes>
    </test>

    <test name="Naziv drugog testa">
        <classes>
            <class name="org.imi.putanja.do.KlaseTest" >
                <methods>
                    <exclude name="nazivMetodaKojiCeSeIzuzeti"></exclude>
                </methods>
            </class>
        </classes>
    </test>

</suite>
```

Tag `include` definise metod koji ce biti ukljucen u test (bice testiran).  
Tag `exclude` definise metod koji ce biti iskljucen iz test (nece biti testiran).

Ako se u `metods` tagu nadje tag `include` onda ce biti testirani samo 
metodi date klase koji su definisani u `include` tagovima. Ukoliko se umesto
`include`-a nadje `exclude` onda ce se testirati svi metodi osim onih definisanih
u `exclude` tagovima.

Izvestaj testa moze da se kreira dodavanjem nekog kreatora izvestaja koje se moze izvristiti u:  
`Edit Configuration > Configuration > Listerners` klikom na +
