# Brzi pregled jedne od mogucih varijanti strukture projekta

## PageBase class
```java
// Da se navigacija ne bi izvrsila za location se prosledi null
public PageBase(WebDriver driver, String location) {
    this.driver = driver;

    if(location != null)
        driver.navigate().to(location);

    PageFactory.initElements(driver, this);
}
```

## ConcretePage class
```java
public class ConcretePage extends PageBase {
    @FindBy(...)
    WebElement element1;

    @FindBy(...)
    WebElement element2;

    void action1() { }
    void action2() { }
}
```

## ConcretePageTest class
```java
@BeforeSuite
public void driverSetup() {
    WebDriverManager.chromedriver().setup();
}

@BeforeMethod
public void openPage() {
    this.driver = new ChromeDriver();
    this.page = new ConcretePage(this.driver, "http://location/..."); // Navigacija se desava u PageBase konstruktoru
}
```

## Logger
```java
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

// Upotreba: logger.info("...");
Logger logger = LoggerFactory.getLogger(Logger.class);
```
