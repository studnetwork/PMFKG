package org.example;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.chrome.ChromeDriver;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.BeforeSuite;
import org.testng.annotations.Test;

import static org.testng.Assert.*;

public class ShoppingPageTest {

    WebDriver driver;
    ShoppingPage shoppingPage;

    LoginPage loginPage;

    @BeforeSuite
    public void setUp() {
        WebDriverManager.chromedriver().setup();
    }

    @BeforeMethod
    public void beforeMethod() {
        driver = new ChromeDriver();
        driver.navigate().to("http://localhost:8080/II%20kolokvijum/Prodavnica/index.php");
        shoppingPage = new ShoppingPage(driver);
        loginPage = new LoginPage(driver);
        loginPage.setUsername("pera");
        loginPage.setPassword("pera");
        loginPage.clickRememberMeCb();
        loginPage.submitLogin();
    }


    @Test
    public void testLogoutUser() {
        //arrange

        //act
        LoginPage loginPage = shoppingPage.logoutUser();

        //assert
        assertNotNull(loginPage);
        assertEquals(driver.getCurrentUrl().trim(), "http://localhost:8080/II%20kolokvijum/Prodavnica/login.php");
        assertTrue(driver.getCurrentUrl().trim().endsWith("login.php"));
    }

    @Test
    public void testCheckIfUsernamesAreTheSame() {
        //arrange

        //act
        boolean sameOrNot = shoppingPage.checkIfUsernamesAreTheSame();

        //assert
        assertTrue(sameOrNot);
    }

    @Test
    public void testTryToBuy50Smoki() {
        //arrange

        //act
        boolean canBuy = shoppingPage.tryToBuy50Smoki();

        //assert
        assertTrue(canBuy);
    }

    @Test
    public void testTryToBuy10VodaVodaAnd5JaffaCrvenka() {
        //arrange

        //act
        boolean canBuy = shoppingPage.tryToBuy10VodaVodaAnd5JaffaCrvenka();

        //assert
        assertTrue(canBuy);
    }


    @Test
    public void testIzbaciVodaVodaIzKorpe() {
        //arrange

        //act
        boolean izbaceno = shoppingPage.izbaciVodaVodaIzKorpe();

        //assert
        assertTrue(izbaceno);
    }
}