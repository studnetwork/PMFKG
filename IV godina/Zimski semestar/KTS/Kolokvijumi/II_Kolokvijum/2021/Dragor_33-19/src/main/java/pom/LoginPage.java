package pom;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;

public class LoginPage extends PageBase {

    @FindBy(id = "korisnicko")
    WebElement userInput;
    @FindBy(id = "lozinka")
    WebElement passInput;
    @FindBy(css = "input[type=\"submit\"]")
    WebElement submitButton;

    public LoginPage(WebDriver driver, String location) {
        super(driver, location);
    }

    public void setLoginData(String user, String pass) {
        userInput.sendKeys("pera");
        passInput.sendKeys("pera");
    }

    public void login() {
        submitButton.click();
    }
}
