package org.shop;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;

public class LoginPage extends BasePage{
    @FindBy(name = "korisnicko")
    private WebElement username;
    @FindBy(name = "lozinka")
    private WebElement password;
    @FindBy(name = "zapamti")
    private WebElement remember;
    @FindBy(name = "prijava")
    private WebElement login;

    public LoginPage(WebDriver driver) {
        super(driver);
    }
    public void setUsername(String username){
        this.username.sendKeys(username);
    }
    public void setPassword(String password){
        this.password.sendKeys(password);
    }
    public CartPage login(){
        login.click();
        return new CartPage(driver);
    }
}
