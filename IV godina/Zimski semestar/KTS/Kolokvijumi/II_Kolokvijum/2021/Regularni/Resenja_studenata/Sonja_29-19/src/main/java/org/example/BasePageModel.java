package org.example;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.support.PageFactory;

public abstract class BasePageModel {

    WebDriver driver;

    public BasePageModel(WebDriver driver) {
        this.driver = driver;
        PageFactory.initElements(driver, this);
    }
}
