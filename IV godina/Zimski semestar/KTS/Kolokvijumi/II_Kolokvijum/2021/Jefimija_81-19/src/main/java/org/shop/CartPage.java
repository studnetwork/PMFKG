package org.shop;

import org.apache.commons.lang3.ObjectUtils;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.Select;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;
import java.util.List;

public class CartPage extends BasePage{
    @FindBy(name="idKorisnika")
    private WebElement selectUser;
    @FindBy(css="h2#korpaKorisnik > span")
    private WebElement cartUser;
    @FindBy(linkText = "LOG OUT")
    private WebElement logoutLink;
    @FindBy(id="nedovoljno")
    private WebElement notEnough;
    @FindBy(name="cb_1")
    private WebElement checkBoxSmoki;
    @FindBy(name="cb_3")
    private WebElement checkBoxVodaVoda;
    @FindBy(name="cb_5")
    private WebElement checkBoxJaffa;
    @FindBy(name="tb_1")
    private WebElement inputSmoki;
    @FindBy(name="tb_3")
    private WebElement inputVodaVoda;
    @FindBy(name="tb_5")
    private WebElement inputJaffa;
    @FindBy(name="kupi")
    private WebElement btnBuy;
    public CartPage(WebDriver driver) {
        super(driver);
    }

    public String getSelectValue(){
        return new Select(selectUser).getFirstSelectedOption().getText();
    }
    public String getCartUserValue(){
        return cartUser.getText();
    }
    public LoginPage logout(){
        logoutLink.click();
        return new LoginPage(driver);
    }
    public String addSmoki(int quantity){
        checkBoxSmoki.click();
        inputSmoki.sendKeys(String.valueOf(quantity));
        btnBuy.click();
        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(2));
        WebElement message = wait.until(ExpectedConditions.visibilityOf(notEnough));
        return message.getText();
    }

    public String addVodaVoda(int quantity){
        checkBoxVodaVoda.click();
        inputVodaVoda.sendKeys(String.valueOf(quantity));
        btnBuy.click();
        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(2));
        WebElement message = wait.until(ExpectedConditions.visibilityOf(notEnough));
        return message.getText();
    }
    public String addJaffa(int quantity){
        checkBoxJaffa.click();
        inputJaffa.sendKeys(String.valueOf(quantity));
        btnBuy.click();
        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(2));
        WebElement message = wait.until(ExpectedConditions.visibilityOf(notEnough));
        return message.getText();
    }
    public boolean deleteItemFromCart(){
        List<WebElement> list = driver.findElements(By.tagName("td"));
        int index = 0;
        for (WebElement cell: list) {
            System.out.println(cell.getText());
            if(cell.getText().contains("Voda Voda"))
                break;
            index++;
        }
        System.out.println("Index: " + index);
        if(index == list.size())
            return false;
        WebElement input = list.get(index+1).findElement(By.tagName("input"));
        input.clear();
        input.sendKeys("0");
        driver.findElement(By.xpath("//button[text() = 'Azuriraj korpu']")).click();
        if(driver.findElement(By.id("azuriranje-korpe")).getText().equals("Korpa je azurirana!"))
            return true;
        return false;
    }
}