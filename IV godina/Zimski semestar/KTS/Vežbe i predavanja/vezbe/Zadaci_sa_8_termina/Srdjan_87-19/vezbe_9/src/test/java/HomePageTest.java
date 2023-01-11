import io.github.bonigarcia.wdm.WebDriverManager;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.testng.annotations.AfterMethod;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.BeforeSuite;
import org.testng.annotations.Test;

import static org.testng.Assert.*;

public class HomePageTest {
    private static final Logger logger = LoggerFactory.getLogger(Logger.class);

    private WebDriver driver;
    private HomePage homePage;

    @BeforeSuite
    public void setUpSuite() {
        WebDriverManager.firefoxdriver().setup();
    }

    @BeforeMethod
    public void setUp() {
        driver = new FirefoxDriver();
        driver.navigate().to("https://imi.pmf.kg.ac.rs/moodle");
        homePage = new HomePage(driver);
    }

    @Test
    public void testNavigateToLoginPage() {
        // arrange

        // act
        LoginPage loginPage = homePage.navigateToLoginPage();
        logger.info("Navigating to login page...");

        // assert
        assertNotNull(loginPage);
        assertEquals(driver.getCurrentUrl(), "https://imi.pmf.kg.ac.rs/moodle/login/index.php");
    }

    @AfterMethod
    public void tearDown() {
        driver.close();
    }
}