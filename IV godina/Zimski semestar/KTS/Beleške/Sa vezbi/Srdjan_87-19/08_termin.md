# Selenium

Za automatsko pronalazenje i konfigurisanje `WebDriver`-a dodati u `pom.xml` sledeci dependency:

```XML
<dependency>
    <groupId>io.github.bonigarcia</groupId>
    <artifactId>webdrivermanager</artifactId>
    <version>3.7.1</version>
</dependency>
```

**Napomena**: `WebDriverManager` se importuje iz paketa `io.github.bonigarcia`


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


XPath:
* `nestoIliNista//nestoDrugo` - relativno adresiranje (krece od `nestoIliNista` pa onda  
                                  onda trazi `nestoDrugo` koje moze biti na bili kojoj "dubini"  
                                  unutar `nestoIliNista`)
* `div[@class='picture']` - match-uje div ciji je atribut `class` koji ima vrednost `picture`                                  
* `*` - match-uje bilo (primer koriscenja: `//*[@class=nesto]`, gde se trazi bilo sta sto ima atribut `class`
        sa vrednoscu `nesto`)
* `text()` - metod kojim se dobija tekst unutar nekog elementa (npr. `*[text()='neki tekst']`)
* `cointains(x,y)` - test kojim se proverava da li se neki string nalazi u drugom stringu (npr. `p[contains(text()='neki string')]`)

Korisni linkovi za xpath:
- https://www.w3schools.com/xml/xpath_intro.asp
- https://www.toolsqa.com/selenium-webdriver/xpath-in-selenium/ (sadrzi neke stvari koje nisu spomenute u w3s tutorijalu)

---

Kada se preuzme `WebElement` koji ima tag `input` onda se nad njime moze 
pozvati metod `.submit()` kojim se salje zahtev (forma) serveru

U before metodu se moze definisati da se browser pokrece u maksimizovanom prozoru (to nije default ponasanje):
```Java
driver.manage().window().maximize();
```


Trazenje `WebElement`-a pomocu XPath-a: 
```Java
driver.findElement(By.xpath(nekiStr))
```


Za `select` tag postoji wrapper klasa koja ima potrebne metode za rad sa padajucom listom:
```Java
Select select = new Select(driver.findElement(nekiBy));
```

Neki od `By` metoda koji se mogu koristiti za pronalazenje linkova
```Java
By.linkText
By.partialLinkText
```
