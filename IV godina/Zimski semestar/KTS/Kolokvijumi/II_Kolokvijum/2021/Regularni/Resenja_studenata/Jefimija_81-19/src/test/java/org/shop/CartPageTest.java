package org.shop;

import io.github.bonigarcia.wdm.WebDriverManager;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.edge.EdgeDriver;
import org.openqa.selenium.support.ui.Select;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.BeforeSuite;
import org.testng.annotations.Test;

import static org.testng.Assert.*;

public class CartPageTest {
    private WebDriver driver;
    private static Logger logger = LoggerFactory.getLogger(Logger.class);
    private CartPage cartPage;
    @BeforeSuite
    public void beforeSuite(){
        WebDriverManager.edgedriver().setup();
    }

    @BeforeMethod
    public void beforeMethod(){
        driver = new EdgeDriver();
        driver.navigate().to("http://localhost/Prodavnica/login.php");
        LoginPage loginPage = new LoginPage(driver);
        loginPage.setUsername("pera");
        loginPage.setPassword("pera");
        cartPage = loginPage.login();
    }

    /* Provera imena i prezimena korisnika */
    @Test
    public void testIsSameUserInSelectAndBasket(){
        String selectValue = cartPage.getSelectValue();
        String basketValue = cartPage.getCartUserValue();
        logger.info(selectValue);
        logger.info(basketValue);
        assertNotNull(selectValue);
        assertNotNull(basketValue);
        assertEquals(selectValue, basketValue);
    }

    /* Odjava sa sistema
o      Test treba da ustanovi da li je odjavljivanje uspešno   */
    @Test
    public void logout(){
        LoginPage loginPage = cartPage.logout();
        assertNotNull(loginPage);
        assertEquals(driver.getCurrentUrl(), "http://localhost/Prodavnica/login.php");
    }

    @Test
    public void checkSmokiQuantity() {
        String message = null;
        try {
            message = cartPage.addSmoki(2);
            assertTrue(message.contains("Na stanju imate"));
        } catch (Exception e) {
            assertNull(message);
        }
        logger.info(message);
    }

    @Test
    public void checkVodaVodaAndJaffaQuantity() {
        String messageVodaVoda = null;
        String messageJaffa = null;
        try {
            messageVodaVoda = cartPage.addVodaVoda(3);
            try {
                messageJaffa = cartPage.addJaffa(5);
            } catch (Exception e) {
                assertNull(messageJaffa);
                assertTrue(messageVodaVoda.contains("Voda Voda"));
            }
        } catch (Exception e) {
            try {
                messageJaffa = cartPage.addJaffa(5);
                assertTrue(messageJaffa.contains("Jaffa"));
            } catch (Exception e1) {
                assertNull(messageJaffa);
                assertNull(messageVodaVoda);
            }
        }
        logger.info(messageVodaVoda);
        logger.info(messageJaffa);
    }

    @Test
    public void deleteVodaVoda(){
        assertTrue(cartPage.deleteItemFromCart());
    }
}