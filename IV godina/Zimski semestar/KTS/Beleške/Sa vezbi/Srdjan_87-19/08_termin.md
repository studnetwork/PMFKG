# Selenium

Za automatsko pronalazenje i konfigurisanje WebDriver-a dodati u `pom.xml` sledece dependency-e:

```XML
<dependency>
    <groupId>org.seleniumhq.selenium</groupId>
    <artifactId>selenium-chrome-driver</artifactId>
    <version>3.141.59</version>
</dependency>
<dependency>
    <groupId>io.github.bonigarcia</groupId>
    <artifactId>webdrivermanager</artifactId>
    <version>3.7.1</version>
</dependency>
```

**Napomena**: ukoliko se ovo koristi onda se `WebDriverManager` importuje iz ovog paketa `io.github.bonigarcia` umesto iz seleniumovog  


Instanciranje driver-a
```Java
    WebDriver driver;

    ...

    @BeforeSuite
    public void suiteSetup() {
         // umesto chromium driver-a moze da se postavi bilo koji drugi,
         // ali u BeforeMetod-u umesto `new ChormiumDriver()` treba instancirati
         // taj izabrani driver
        WebDriverManager.chromiumdriver().setup();
    }

    ...

    @BeforeMethod
    public void BeforeMethod() {
        driver = new ChormiumDriver();
    }
```

---

Kada se preuzme `WebElement` koji ima tag `input` onda se nad njime moze 
pozvati metod `.submit()` kojim se salje zahtev (forma) serveru


XPath:
* `nestoIliNista//nestoDrugo` - relativno adresiranje (krece od `nestoIliNista` pa onda  
                                  onda trazi `nestoDrugo` koje moze biti na bili kojoj "dubini"  
                                  unutar `nestoIliNista`)
* `div[@class='picture']` - match-uje div ciji je atribut `class` koji ima vrednost `picture`                                  
* `*` - match-uje bilo (primer koriscenja: `//*[@class=nesto]`, gde se trazi bilo sta sto ima atribut `class`
        sa vrednoscu `nesto`)
* `text()` - match-uje tekst unutar nekog elementa (npr. `*[text()='neki tekst']`)



U before metodu se moze definisati da se browser pokrece u maksimizovanom prozoru (to nije default ponasanje):
```Java
driver.manage().window().maximize();
```


Trazenje `WebElement`-a pomocu XPath-a: 
```Java
driver.findElement(By.xpath(nekiStr))
```


Za `select` tag postoji wrapper klasa posto sa obicnim `WebElement`-om nema potrebne metode:
```Java
Select select = new Select(driver.findElement(nekiBy));
```

Neki od `By` metoda koji se mogu koristiti za pronalazenje linkova
```Java
By.linkText
By.partialLinkText
```
