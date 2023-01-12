package org.example;

import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.FindBy;
import org.openqa.selenium.support.FindBys;
import org.openqa.selenium.support.How;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.Select;
import org.openqa.selenium.support.ui.WebDriverWait;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import javax.swing.text.html.Option;
import java.time.Duration;
import java.util.List;
import java.util.Objects;

public class ShoppingPage extends BasePageModel {

    @FindBy(how = How.LINK_TEXT, using = "LOG OUT")
    private WebElement linkForLogout;

    @FindBy(how = How.XPATH, using = "//select")
    private WebElement select;

    @FindBy(how = How.CSS, using = "#korpaKorisnik > span")
    private WebElement usernameFromCart;

    @FindBy(how = How.NAME, using = "cb_1")
    private WebElement cbSmoki;

    @FindBy(how = How.NAME, using = "cb_3")
    private WebElement cbVodaVoda;

    @FindBy(how = How.NAME, using = "cb_5")
    private WebElement cbJaffaCrvenka;

    @FindBy(how = How.NAME, using = "tb_1")
    private WebElement textBoxSmoki;

    @FindBy(how = How.NAME, using = "tb_3")
    private WebElement textBoxVodaVoda;

    @FindBy(how = How.NAME, using = "tb_5")
    private WebElement textBoxJaffaCrvenka;

    @FindBy(how = How.NAME, using = "kupi")
    private WebElement buyBtn;

    @FindBy(how = How.ID, using = "nedovoljno")
    private WebElement spanNedovoljno;

    @FindBy(how = How.XPATH, using = "//button[text() = 'Azuriraj korpu']")
    private WebElement azurirajKorpuBtn;

    @FindBy(how= How.ID, using = "azuriranje-korpe")
    private WebElement korpaJeAzuriranaSpan; //uvek postoji, samo se menja poruka na "" ili poruku

    @FindBys({
            @FindBy(how = How.CSS, using = "tr > td"),
            @FindBy(how = How.LINK_TEXT, using = "Voda Voda")
    })
    private WebElement vodaVodaUKorpi;


    private static Logger logger = LoggerFactory.getLogger(Logger.class);

    public ShoppingPage(WebDriver driver) {
        super(driver);
    }

    public LoginPage logoutUser() {
        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(5));
        wait.until(ExpectedConditions.visibilityOf(linkForLogout));

        linkForLogout.click();

        return new LoginPage(driver);
    }

    /*
        Ime i prezime nalazi se u dropdown listi u glanom delu programa, kao i u delu koji
        prikazuje korpu. Test treba da ustanovi da li su ova imena ista.
     */

    public boolean checkIfUsernamesAreTheSame() {

//        System.out.println(new Select(select).getFirstSelectedOption().getText().trim());
//        System.out.println(usernameFromCart.getText().trim());

        return Objects.equals(new Select(select).getFirstSelectedOption().getText().trim(), usernameFromCart.getText().trim());
    }


    /* Dodavanje 50 proizvoda „Smoki“ u korpu
    Test treba da ustanovi da li je moguće kupiti ovu količinu proizvoda. Ukoliko nije moguće
    kupiti proizvode na stranici će izaći poruka koliko ovog proizvoda ima na stanju.
    Znaci cekiramo smoki i ukucamo 50 i idemo na kupi i gledamo ima li poruke o gresci ili ne
     */

    public boolean tryToBuy50Smoki() {
        cbSmoki.click();
        textBoxSmoki.sendKeys("50");

        buyBtn.click();

        List<WebElement> elementsNedovoljno = driver.findElements(By.id("nedovoljno"));

        if (elementsNedovoljno.isEmpty())
            return true; //nema poruke greske, moze da kupi
        return false;
    }

    public boolean tryToBuy10VodaVodaAnd5JaffaCrvenka() {
        cbVodaVoda.click();
        textBoxVodaVoda.sendKeys("10");
        cbJaffaCrvenka.click();
        textBoxJaffaCrvenka.sendKeys("5");

        buyBtn.click();

        List<WebElement> elementsNedovoljno = driver.findElements(By.id("nedovoljno"));

        return elementsNedovoljno.isEmpty();
    }

    public boolean canBuy() {
        List<WebElement> elementsNedovoljno = driver.findElements(By.id("nedovoljno"));

        return elementsNedovoljno.isEmpty(); //nema poruke greske, moze da kupi
    }

    /*
        izbacivanje proizvoda „Voda Voda“ iz korpe:
        Proizvod se izbacuje setovanjem količine proizvoda u korpi na 0 i azuriranjem korpe.
        Ukoliko je izbacivanje uspesno Proizvod treba nestati iz korpe i korisnik će biti obavešten
        porukom da je ažuriranje uspešno

        znaci nadji vodavoda u korpi, setuj na 0 i klikni na azuriranje korpe. proveri da li ima vodavoda u korpi
        i proveri da li pise "Korpa je azurirana!" ili je prazan span
     */
    public boolean izbaciVodaVodaIzKorpe() {
        //nadji u korpi
        List<WebElement> celijeTD = driver.findElements(By.tagName("td"));

        boolean nasao = false;
        int indexVodaVoda = 0;

        for (WebElement td: celijeTD) {
            //logger.info(td.getText());
            if (td.getText().equals("Voda Voda")) {
                //logger.info("vodavoda" + td.getText());
                nasao = true;
                break;
            }
            indexVodaVoda++;
        }

        if (nasao == false)
            return false;
        else {
            // <td> <input> </td>
            WebElement tdKolicinaVodaVoda = celijeTD.get(indexVodaVoda + 1); //odmah posle td-a VodaVoda ide td za input kolicina
            WebElement inputKolicinaVodaVoda = tdKolicinaVodaVoda.findElement(By.tagName("input"));
            inputKolicinaVodaVoda.clear();
            inputKolicinaVodaVoda.sendKeys("0");

            azurirajKorpuBtn.click();

            //da li je vodavoda nestala iz korpe?
            List<WebElement> celijeTDnovo = driver.findElements(By.tagName("td"));
            for (WebElement tdNovo: celijeTDnovo) {
                if (tdNovo.getText().equals("Voda Voda"))
                    return false; //jos je u korpi, nije izbaceno
            }

            //nije u korpi, al da vidimo ima li poruke o izbacivanju
            return korpaJeAzuriranaSpan.getText().equals("Korpa je azurirana!");
        }
    }
}
