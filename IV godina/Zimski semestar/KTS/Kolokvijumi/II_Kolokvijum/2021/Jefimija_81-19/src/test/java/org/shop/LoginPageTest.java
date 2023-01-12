package org.shop;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.edge.EdgeDriver;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.BeforeSuite;
import org.testng.annotations.Test;

import static org.testng.Assert.*;

public class LoginPageTest {
    private WebDriver driver;
    private static Logger logger = LoggerFactory.getLogger(Logger.class);
    private LoginPage loginPage;

    @BeforeSuite
    public void beforeSuite(){
        WebDriverManager.edgedriver().setup();
    }

    @BeforeMethod
    public void beforeMethod(){
        driver = new EdgeDriver();
        driver.navigate().to("http://localhost/Prodavnica/login.php");
        loginPage = new LoginPage(driver);
    }

    // Prijavljivanje na sistem (username: pera password: pera)
    @Test
    public void login(){
        loginPage.setUsername("pera");
        loginPage.setPassword("pera");
        CartPage cartPage = loginPage.login();
        assertNotNull(cartPage);
        assertEquals(driver.getCurrentUrl(), "http://localhost/Prodavnica/index.php");
    }
}