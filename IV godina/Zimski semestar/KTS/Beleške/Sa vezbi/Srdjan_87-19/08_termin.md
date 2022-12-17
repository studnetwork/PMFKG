

```
WebDriver driver;

...

@BeforeSuite
...
    WebDriverManager.chromiumdriver().setup();
...

@BeforeMethod
public void BeforeMethod() {
    driver = new ChormiumDriver();
}
```

---


Za automatsko pronalazenje i konfigurisanje WebDriver-a dodati:

```
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
u pom.xml

Napomena: ukoliko se ovo koristi onda se WebDriverManager importuje   
          iz ovog dodatog paketa umesto iz seleniumovog  



Kada se preuzme webelement koji ima tag input onda se nad njime moze 
pozvati metod .submit() kojim se salje zahtev (forma) serveru


XPath:
* `nestoIliNista//nestoDrugo` - relativno adresiranje (krece od `nestoIliNista` pa onda  
                                  onda trazi `nestoDrugo` koje moze biti na bili kojoj "dubini"  
                                  unutar `nestoIliNista`)
* `div[@class='picture']` - match-uje div ciji je atribut `class` koji ima vrednost `picture`                                  * `*` - match-uje bilo (primer koriscenja: `//*[@class]=nesto`, gde se trazi bilo sta sto ima atribut `class`
        sa vrednoscu `nesto`)
* `text()` - match-uje tekst unutar nekog elementa (npr. `*[text()='neki tekst']`)



U before metodu moze i da se definise da se browser pokrece u maksimizovanom prozoru (to nije default ponasanje):
```
driver.manage().window().maximize();
```


Pretrga po XPath-u: 
```
driver.findElement(By.xpath(nekiStr))
```


Za select tag postoji wrapper klasa posto sa obicnim WebElement-om nema potrebne metode:
```
Select select = new Select(driver.findElement(nekiByy));
```


```
By.linkText
By.partialLinkText
```
