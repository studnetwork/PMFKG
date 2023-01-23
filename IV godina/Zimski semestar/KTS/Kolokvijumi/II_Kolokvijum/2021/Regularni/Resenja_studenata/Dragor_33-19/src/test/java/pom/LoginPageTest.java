package pom;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import org.testng.Assert;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.BeforeSuite;
import org.testng.annotations.BeforeTest;
import org.testng.annotations.Test;

import static org.testng.Assert.*;

public class LoginPageTest {

    LoginPage loginPage;

    WebDriver driver;

    @BeforeSuite
    public void driverSetup() {
        WebDriverManager.chromiumdriver().setup();
    }

    @BeforeMethod
    public void navigateToLogin() {
        driver = new ChromeDriver();
        loginPage = new LoginPage(driver, Conf.url + "/login.php");
    }

    @Test
    public void testLogin() {
        loginPage.setLoginData("pera", "pera");
        loginPage.login();

        assertTrue(driver.getCurrentUrl().endsWith("/index.php"));
    }
}