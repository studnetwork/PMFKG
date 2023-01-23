package pom;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.ui.ExpectedCondition;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;

import java.time.Duration;

public class HomePage extends PageBase {

    @FindBy(xpath = "//option")
    WebElement nameOption;
    @FindBy(xpath = "//h2/span")
    WebElement nameHeader;
    @FindBy(xpath = "//a[@href='index.php?logout']")
    WebElement logoutLink;

    @FindBy(xpath = "//form/input[@type='submit']")
    WebElement addToChartButton;
    @FindBy(xpath = "//div[@id='korpa-div']/button")
    WebElement refreshChartButton;

    @FindBy(xpath = "//form/input[@name='tb_1']")
    WebElement inputSmoki;
    @FindBy(xpath = "//form/input[@name='tb_3']")
    WebElement inputVoda;
    @FindBy(xpath = "//form/input[@name='tb_5']")
    WebElement inputJaffa;
    @FindBy(xpath = "//form/input[@name='cb_1']")
    WebElement checkboxSmoki;
    @FindBy(xpath = "//form/input[@name='cb_3']")
    WebElement checkboxVoda;
    @FindBy(xpath = "//form/input[@name='cb_5']")
    WebElement checkboxJaffa;

    @FindBy(xpath = "//div[@id='korpa-div']/table/tbody/tr[td='Voda Voda']/td[input]/input")
    WebElement chartInputVoda;



    protected WebElement getElementWithWait(By by, int s) {
        WebElement el;
        try {
            WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(s));
            el = wait.until(ExpectedConditions.presenceOfElementLocated(by));
        } catch (Exception e) {
            el = null;
        }
        return el;
    }
    WebElement getNedovoljno() {
        return getElementWithWait(By.id(("nedovoljno")), 3);
    }
    WebElement getAzuriranaKorpa() {
        return getElementWithWait(By.id(("azuriranje-korpe")), 3);
    }
    WebElement getChartInputVoda() {
        return getElementWithWait(By.xpath("//div[@id='korpa-div']/table/tbody/tr[td='Voda Voda']/td[input]/input"), 3);
    }

    public HomePage(WebDriver driver, String location) {
        super(driver, location);
    }

    public void fillInputSmoki(int num) {
        inputSmoki.sendKeys("" + num);
        checkboxSmoki.click();
    }
    public void fillInputVoda(int num) {
        inputVoda.sendKeys("" + num);
        checkboxVoda.click();
    }
    public void fillInputJaffa(int num) {
        inputJaffa.sendKeys("" + num);
        checkboxJaffa.click();
    }

    public void fillChartInputVoda(int num) {
        chartInputVoda.clear();
        chartInputVoda.sendKeys("" + num);
    }
    public void addToChart() {
        addToChartButton.click();
    }
    public void refreshChart() {
        refreshChartButton.click();
    }

    public void logout() {
        logoutLink.click();
    }


}
