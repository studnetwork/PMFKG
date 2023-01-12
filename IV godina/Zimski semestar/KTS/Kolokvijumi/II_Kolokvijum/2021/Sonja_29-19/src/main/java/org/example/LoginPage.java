package org.example;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.How;

public class LoginPage extends BasePageModel {

    @FindBy(how = How.ID, using = "korisnicko")
    private WebElement username;

    @FindBy(how = How.ID, using = "lozinka")
    private WebElement password;

    @FindBy(how = How.NAME, using = "zapamti")
    private WebElement rememberMeCb;

    @FindBy(how = How.NAME, using = "prijava")
    private WebElement loginBtn;

    public LoginPage(WebDriver driver) {
        super(driver);
    }

    public void setUsername(String text) {
        this.username.sendKeys(text);
    }

    public void setPassword(String text) {
        this.password.sendKeys(text);
    }

    public void clickRememberMeCb() {
        this.rememberMeCb.click();
    }

    public ShoppingPage submitLogin() {
        loginBtn.click();

        return new ShoppingPage(driver);
    }
}
