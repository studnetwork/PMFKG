package pom;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.support.PageFactory;

public abstract class PageBase {

    WebDriver driver;
    String location;

    public PageBase(WebDriver driver, String location) {
        this.driver = driver;
        this.location = location;

        if(!location.equals(""))
            driver.navigate().to(location);

        PageFactory.initElements(driver, this);
    }

}
