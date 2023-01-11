import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class LoginPage extends BasePage{
    private static final Logger logger = LoggerFactory.getLogger(Logger.class);

    private final By usernameBy = By.xpath("//input[@id='username']");
    private final By passwordBy = By.xpath("//input[@id='password']");
    private final By submitButtonBy = By.xpath("//button[@id='loginbtn']");
    private final By rememberUsernameBy = By.xpath("//input[@id='rememberusername']");

    public LoginPage(WebDriver driver) {
        super(driver);
    }

    public String getUsername() {
        return driver.findElement(usernameBy).getDomAttribute("value");
    }

    public void setUsername(String username) {
        driver.findElement(usernameBy).sendKeys(username);
    }

    public void setPassword(String password) {
        driver.findElement(passwordBy).sendKeys(password);
    }

    public void rememberUsername() {
        driver.findElement(rememberUsernameBy).click();
    }

    public HomePage submitLoginData() {
        driver.findElement(submitButtonBy).click();

        return new HomePage(driver);
    }
}
