package org.example;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.BeforeSuite;
import org.testng.annotations.Test;

import static org.testng.Assert.*;

public class LoginPageTest {

    WebDriver driver;
    LoginPage loginPage;

    @BeforeSuite
    public void setUp() {
        WebDriverManager.chromedriver().setup();
    }

    @BeforeMethod
    public void beforeMethod() {
        driver = new ChromeDriver();
        driver.navigate().to("http://localhost:8080/II%20kolokvijum/Prodavnica/login.php");
        loginPage = new LoginPage(driver);
    }


    @Test
    public void testSubmitLogin() {
        //arrange
        loginPage.setUsername("pera");
        loginPage.setPassword("pera");
        loginPage.clickRememberMeCb();

        //act
        ShoppingPage shoppingPage = loginPage.submitLogin();

        //assert
        assertNotNull(shoppingPage);
        assertEquals(driver.getCurrentUrl().trim(), "http://localhost:8080/II%20kolokvijum/Prodavnica/index.php");
        assertTrue(driver.getCurrentUrl().trim().contains("index.php"));
    }
}