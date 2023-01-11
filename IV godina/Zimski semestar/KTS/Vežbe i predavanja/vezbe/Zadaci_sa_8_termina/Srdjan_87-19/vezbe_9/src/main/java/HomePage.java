import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;

public class HomePage extends BasePage{

    private final By loginPageLinkBy = By.xpath("//a[text()='Prijava']");
    private final By rememberUsernameMenuBtnBy = By.xpath("//a[@id='action-menu-toggle-1']");
    private final By logoutLinkBy = By.xpath("//a[@data-title='logout,moodle']");

    public HomePage(WebDriver driver) {
        super(driver);
    }

    public LoginPage navigateToLoginPage() {
        driver.findElement(loginPageLinkBy).click();
        return new LoginPage(driver);
    }

    public HomePage logout() {
        driver.findElement(rememberUsernameMenuBtnBy).click();
        driver.findElement(logoutLinkBy).click();

        return new HomePage(driver);
    }

    public WebElement getLoginPageLinkElement() {
        return driver.findElement(loginPageLinkBy);
    }
}
