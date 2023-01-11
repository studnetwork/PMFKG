import io.github.bonigarcia.wdm.WebDriverManager;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.testng.annotations.AfterMethod;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.BeforeSuite;
import org.testng.annotations.Test;

import java.time.Duration;

import static org.testng.Assert.*;

public class LoginPageTest {
    private static final Logger logger = LoggerFactory.getLogger(Logger.class);
    private WebDriver driver;
    private LoginPage loginPage;

    @BeforeSuite
    public void setUpSuite() {
        WebDriverManager.firefoxdriver().setup();
    }

    @BeforeMethod
    public void setUp() {
        driver = new FirefoxDriver();
        driver.navigate().to("https://imi.pmf.kg.ac.rs/moodle/login/index.php");
        loginPage = new LoginPage(driver);
    }

    @Test
    public void testSubmitLoginData_withCorrectValues() {
        // arrange
        loginPage.setUsername("ispravan.username");
        loginPage.setPassword("ispravna.lozinka");

        // act
        HomePage homePage = loginPage.submitLoginData();
        logger.info("Logging data is submitted");

        // assert
        assertNotNull(homePage);
        assertEquals(driver.getCurrentUrl(), "https://imi.pmf.kg.ac.rs/moodle/");
    }

    @Test
    public void testSubmitLoginData_withoutAnyValue() {
        // arrange

        // act
        HomePage homePage = loginPage.submitLoginData();
        logger.info("Logging data is submitted");

        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(5));
        WebElement errMsgElement = wait.until(ExpectedConditions.visibilityOfElementLocated(
                By.xpath("//div[@class='alert alert-danger']")));

        // assert
        assertNotNull(errMsgElement);
        assertEquals(errMsgElement.getText().trim(),
                "Pogrešno korisničko ime ili lozinka. Molimo pokušajte ponovo.");
    }

    @Test
    public void testRememberUsername() {
        // arrange
        loginPage.setUsername("ispravan.username");
        loginPage.setPassword("ispravna.lozinka");

        // act
        loginPage.rememberUsername();
        HomePage homePage = loginPage.submitLoginData();
        logger.info("Login data is submitted");
        assertNotNull(homePage);

        homePage = homePage.logout();
        logger.info("Logged out");
        assertNotNull(homePage);
        assertEquals(driver.getCurrentUrl(), "https://imi.pmf.kg.ac.rs/moodle/");

        WebElement loginPageLinkElement = homePage.getLoginPageLinkElement();
        assertNotNull(loginPageLinkElement);
        loginPageLinkElement.click();
        logger.info("Return to login page");

        String username = loginPage.getUsername();

        // assert
        assertNotNull(username);
        assertEquals(username, "ispravan.username");
    }

    @AfterMethod
    public void tearDown() {
        driver.close();
    }
}