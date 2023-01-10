import io.github.bonigarcia.wdm.WebDriverManager;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.openqa.selenium.support.ui.Select;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.testng.annotations.AfterMethod;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.BeforeSuite;
import org.testng.annotations.Test;

import java.util.List;

import static org.testng.Assert.*;

public class MainTest {
    private static final Logger logger = LoggerFactory.getLogger(Logger.class);

    private final String technomediaUrl = "https://www.tehnomedia.rs/";
    private final String technomediaMonitorUrl = "https://www.tehnomedia.rs/search/find.html?rec=monitor";
    private WebDriver driver;

    private final By searchBarBy = By.xpath("//input[@id='search-text']");
    private final By searchBarFormBy = By.xpath("//input[@id='search-text']/..");
    private final By searchBarButtonBy = By.xpath("./button");
    private final By searchBarButtonBy_2 = By.xpath("following-sibling::*");
    private final By resultCountTextBy = By.xpath(
            "//section[@class='bottom_box on_the_sides' and position() = 1]" +
            "/div[@class='left_side']/p");
    private final By resultItemBy = By.xpath("//*[@class='product_item']");
    private final By sortBy = By.xpath("//select[@id='sortme']"); // alt: "//select[@name='sort']"
    private final By proizvodiButtonBy = By.xpath("//button[@class='open_menu']");
    private final By proizvodiListBy = By.xpath(
            "//ul[contains(@class, 'active')" +
                    " and contains(@class, 'visible')]");
    private final By kontaktLinkBy = By.xpath("//a[text()='Kontakt']");
    private final By usloviBy = By.xpath("//a[contains(text(), 'Uslovi ')]");


    @BeforeSuite
    public void suiteSetup() {
        WebDriverManager.firefoxdriver().setup();
    }

    @BeforeMethod
    public void testSetup() {
        driver = new FirefoxDriver();
        driver.manage().window().maximize();
    }

    @Test
    public void visitMainPage() {
        // arrange

        // act
        driver.get(technomediaUrl);

        // assert
        assertEquals(driver.getCurrentUrl().trim(), technomediaUrl);
    }

    @Test
    public void searchUsingSearchBar_enterMonitor_1() {
        // arrange
        driver.get(technomediaUrl);
        WebElement formElement = driver.findElement(searchBarFormBy);
        WebElement submitButtonElement = formElement.findElement(searchBarButtonBy);

        // act
        WebElement searchBarElement = driver.findElement(searchBarBy);
        searchBarElement.sendKeys("monitor");
        submitButtonElement.click();

        // assert
        logger.info("Current URL: " + driver.getCurrentUrl());
        assertTrue(driver.getCurrentUrl().endsWith("/search/find.html?rec=monitor"));
    }

    @Test
    public void searchUsingSearchBar_enterMonitor_2() {
        // arrange
        driver.get(technomediaUrl);
        WebElement searchBarElement = driver.findElement(searchBarBy);
        WebElement submitButtonElement = searchBarElement.findElement(searchBarButtonBy_2); // obratiti panznju, nije driver

        // act
        searchBarElement.sendKeys("monitor");
        submitButtonElement.click();

        // assert
        logger.info("Current URL: " + driver.getCurrentUrl());
        assertTrue(driver.getCurrentUrl().endsWith("/search/find.html?rec=monitor"));
    }

    @Test
    public void countResultsOnFirstPage_forMonitorQuery() {
        // arrange
        driver.get(technomediaMonitorUrl);
        List<WebElement> resultCountElement = driver.findElements(resultItemBy);

        // act
        int count = resultCountElement.size();

        // assert
        logger.info("Number of results on first result page: " + count);

        // ovo ce postati netacno u nekom trenutku jer se inace ne radi na produkcionoj bazi vec na kontrolisanoj
        // bazi za koju se zna rezultat, tj. ishod neke operacije
        assertEquals(count, 16);
    }

    @Test
    public void checkTextForResultCount_forMonitorQuery() {
        // arrange
        driver.get(technomediaMonitorUrl);
        WebElement resultCountElement = driver.findElement(resultCountTextBy);

        // act
        String text = resultCountElement.getText().trim();

        // assert
        logger.info("Result count text: " + text);

        // ovo ce postati netacno u nekom trenutku jer se inace ne radi na produkcionoj bazi vec na kontrolisanoj
        // bazi za koju se zna rezultat, tj. ishod neke operacije
        assertEquals(text, "Prikazano 1 do 16 od ukupno 229 (15 stranica)");
    }

    @Test
    public void selectSortOrder_Naziv() {
        // arrange
        driver.get(technomediaMonitorUrl);
        WebElement sortElement = driver.findElement(sortBy);

        // act
        sortElement.click();
        Select sortSelect = new Select(sortElement);
        assertNotNull(sortSelect); // proveriti da li je ok da ovde stoji
        sortSelect.selectByVisibleText("Nazivu");

        // assert
        // provera da li su svi rezultati sortirani po nazivu
    }

    @Test
    public void goToProizvodi() {
        // arrange
        driver.get(technomediaUrl);
        WebElement proizvodiButton = driver.findElement(proizvodiButtonBy);

        // act
        proizvodiButton.click();

        // assert
        WebElement proizvodiList = driver.findElement(proizvodiListBy);
        assertNotNull(proizvodiList);
    }

    @Test
    public void goToUsloviKoriscenja() {
        // arrange
        driver.get(technomediaUrl);
        WebElement kontaktLinkElement = driver.findElement(kontaktLinkBy);

        // act
        //// go to 'Kontakt'
        kontaktLinkElement.click();
        logger.info("Current URL: " + driver.getCurrentUrl());

        //// remove cookie element
        WebElement cookieElement = driver.findElement(By.xpath("//div[@class='grt-cookie grt-cookie-active']"));
        cookieElement.click();

        //// go to page 'Uslovi koriscenja'
        WebElement usloviLinkElement = driver.findElement(usloviBy);
        usloviLinkElement.click();
        logger.info("Current URL: " + driver.getCurrentUrl());

        // assert
        assertEquals(driver.getCurrentUrl(), "https://www.tehnomedia.rs/pages/uslovikoriscenja.html");
    }

    @AfterMethod
    public void postProcessing() {
        driver.close();
    }
}