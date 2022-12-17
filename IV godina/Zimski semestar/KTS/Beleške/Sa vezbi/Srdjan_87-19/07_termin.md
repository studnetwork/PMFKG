
Dodavanje logger dependency-a je neophodno za rad TestNg-a

Importi za logger (ne radi sa onim iz util paketa):
```
    import org.slf4j.Logger;
    import org.slf4j.LoggerFactory;
```

@BeforeTest  
@BeforeClass  
@BeforeMethod  
@AfterTest  
@AfterClass  
@AfterMethod  

Napomena: @xTest se odnosi na skup testova (metoda, a ne na pojedinacan metod)
    
Umesto print-ova koristiti logger    

```
@Parameters("{ime1IzXMLa, ime2IzXMLa}")  
@Test  
... (Type1 ime1KojeNeMoraDaSePoklapaSaXMLom, Type2 ime2KojeNeMoraDaSePoklapaSaXMLom)
```

Izgled XML-a
```
<!DOCTYPE suite SYSTEM "https://testng.org/testng-1.0.dtd" >
<suite name="Naziv suite-a" thread-count="4" parallel="methods">
    <parameter name="ime1" value="vrednost1"/>
    <parameter name="ime2" value="vrednost2"/>
    <test name="Naziv testa">
        <parameter name="imeparametra" value="vrednost3"/>
        <classes>
            <class name="org.imi.putanja.do.Klase1Test"/>
            <class name="org.imi.putanja.do.Klase2Test"/>
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


Drugi report moze da se nabavi dodavanjem u: Edit Configuration > Configuration > Listerners
klikom na +
