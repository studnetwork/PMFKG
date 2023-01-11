Selenium ima ugradjenu podrsku za POM framework i to je implementirano kao PageFactory.

```
PageFactory.initElements(driver, this);
```

Ovaj kod inicijalizuje sve elemente date stranice (pisemo ga u konstruktoru zbog toga)

Omogucava jednostavniji rad jer npr. skracuje kod koji se pise i omogucava lakse pisanje kompleksnih upita.

Umesto da se koristi `driver.findElement` koristi se anotacija `@FindBy` iznad polja tipa `WebElement` koje sadrzi rezultat, odnosno trazeni element.

Sa Ctrl+p unutar zagrada `FindBy` je moguce izlistati sve dostupne parametre.

```
@FindBy(id="nekiId")
...

@FindBy(linkTexe="neki tekst")
...
```


Ova anotacija ima i parametar `how` kojim se definise nacin na koji ce se pretraga izvrsiti. Zajedno sa ovim parametrom je potrebno definisati i
parametar `using` u kome se navodi vrednost po kojoj ce se izvrsiti pretraga.

```
@FindBy(how=How.ID, using="nekiId")
...
```

```
@FindBys({
@FindBy(how=How.ID, using="nekiId"),
@FindBy(how=How.NAME, using="nekiName")
})
...
```
nalazi sve elemente koji metchuju svaki naveden `FindBy`, gde je prethodni element parent datog elementa. Npr:
```
<div id='nekiId'>
    <p name='nekiName'></p>
</div>
```



```
@FindAll({
@FindBy(how=How.ID, using="nekiId"),
@FindBy(how=How.NAME, using="nekiName")
})
...
```
nalazi sve elemente koji match-uju bilo koji FindBy . Npr: 
```
<p id='nekiId' name='nekiName'></p>
```
ili 
```
<div id='nekiId'></div>
```



Anotacija `@CacheLookUp` kesira rezultat kako se ne bi stalno trazio. To moze da ubrza izvrsenje testova.

Za kol obnoviti wamp:
- C:\wamp\public 
- phpmyadmin db import

Za vezbu: cs-cart.com
Zahteva reg, dobija se trial od 14 dana
