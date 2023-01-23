Selenium ima ugradjenu podrsku za POM framework i to je implementirano kao `PageFactory`.

```Java
PageFactory.initElements(driver, this);
```

Ovaj deo koda inicijalizuje sve elemente date stranice (pisemo ga u konstruktoru zbog toga):
```Java
public BasePageModel(WebDriver driver) {
    this.driver = driver;
    PageFactory.initElements(driver, this);
}
```

Omogucava jednostavniji rad jer npr. skracuje kod koji se pise i omogucava lakse pisanje kompleksnih upita.

Umesto da se koristi `driver.findElement` koristi se anotacija `@FindBy` iznad polja tipa `WebElement` koje sadrzi rezultat, odnosno trazeni element.

Sa `Ctrl` + `p` (Intellj shortcut) unutar zagrada `FindBy`-a je moguce izlistati sve dostupne parametre.

```Java
@FindBy(id="nekiId")
private WebElement id;

@FindBy(linkTexe="neki tekst")
private WebElement text;
```


Ova anotacija ima i parametar `how` kojim se definise nacin na koji ce se pretraga izvrsiti. Zajedno sa ovim parametrom je potrebno definisati i
parametar `using` u kome se navodi vrednost po kojoj ce se izvrsiti pretraga.

```Java
@FindBy(how=How.ID, using="nekiId")
private WebElement nekiId;
```

---

`FindBys` omogucava "ugnjezdenu" pretragu, tj. pretragu u kojoj rezultat jednog `FindBy`-a predstavlja polaznu tacku za pretragu sledeceg `FindBy`-a.

Primer
```Java
@FindBys({
    @FindBy(how=How.ID, using="nekiId"),
    @FindBy(how=How.NAME, using="nekiName")
})
...
```

Prehodni kod match-uje: 
```Html
<div id='nekiId'>
    <p name='nekiName'></p>
</div>
```

Ekvavilent kodu iz ovog primera je:
```Java
    WebElement nekiId = driver.findElement(By.id("nekiId"));

    // obratiti paznju: koristimo `nekiId.findElement`, a ne `driver.findElement`
    WebElement nekiName = nekiId.findElement(By.name("nekiName"));
```

---

Ovaj deo koda nalazi sve elemente koji match-uju bilo koji `FindBy`
```Java
@FindAll({
    @FindBy(how=How.ID, using="nekiId"),
    @FindBy(how=How.NAME, using="nekiName")
})
...
```

Prehodni kod match-uje: 
```Html
<p id='nekiId'></p>
<!-- ili -->
<div name='nekiName'></div>
<!-- ili -->
<p id='nekiId' name='nekiName'></p>
```

---

Anotacija `@CacheLookUp` kesira rezultat kako se ne bi stalno trazio. To moze da ubrza izvrsenje testova.

Za kol obnoviti wamp:
- serviranje fajlova (`C:\wamp\public `)
- phpmyadmin db import

Za vezbu: cs-cart.com  
Zahteva registraciju i ima trial od 14 dana
