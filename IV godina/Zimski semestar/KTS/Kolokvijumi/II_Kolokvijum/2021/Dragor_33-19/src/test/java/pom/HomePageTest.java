package pom;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.BeforeSuite;
import org.testng.annotations.Test;

import static org.testng.Assert.*;

public class HomePageTest {

    HomePage homePage;
    LoginPage loginPage;
    WebDriver driver;

    @BeforeSuite
    public void driverSetup() {
        WebDriverManager.chromiumdriver().setup();
    }

    @BeforeMethod
    public void navigateToHome() {
        driver = new ChromeDriver();

        loginPage = new LoginPage(driver, Conf.url + "/login.php");
        loginPage.setLoginData("pera", "pera");
        loginPage.login();

        homePage = new HomePage(driver, "");
    }

    @Test
    public void testName() {
        String name1 = homePage.nameHeader.getText();
        String name2 = homePage.nameOption.getText();
        assertEquals(name2, name1);
    }

    @Test
    public void testDodatiSmoki() {
        homePage.fillInputSmoki(50);
        homePage.addToChart();
        assertNull(homePage.getNedovoljno());
    }

    @Test
    public void testDodatiVoduIJafu() {
        homePage.fillInputVoda(10);
        homePage.fillInputJaffa(5);
        homePage.addToChart();
        assertNull(homePage.getNedovoljno());
    }

    @Test
    public void testIzbacitiVodu() {
        homePage.fillChartInputVoda(0);
        homePage.refreshChart();
        assertNotNull(homePage.getAzuriranaKorpa());
        assertNull(homePage.getChartInputVoda());
    }

    @Test
    public void testLogout() {
        homePage.logout();
        assertTrue(driver.getCurrentUrl().endsWith("/login.php"));
    }

}