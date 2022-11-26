package com.imi.qaIV.luka.brodovi;

import com.imi.qaIV.putnici.BiznisKlasa;
import com.imi.qaIV.putnici.EkonomskaKlasa;
import com.imi.qaIV.putnici.Karta;
import com.imi.qaIV.putnici.Putnik;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.mockito.InjectMocks;
import org.mockito.Mock;

import java.lang.reflect.Field;

import static org.junit.Assert.*;

public class PutnickiBrodTest {

    private static Field putniciField;
    private String shipName = "Putnicki brod";
    private String captainName = "Pera";
    private int numOfBusinessClassPassengers = 2;
    private int numOfEconomyClassPassengers = 2;
    private Putnik[] putnici;
    private PutnickiBrod underTest;

    @BeforeClass
    public static void setUpClass() throws NoSuchFieldException {
        putniciField = PutnickiBrod.class.getDeclaredField("putnici");
    }

    @Before
    public void setUp() throws Exception {
        underTest = new PutnickiBrod(
                captainName, captainName, numOfBusinessClassPassengers, numOfEconomyClassPassengers);

        putnici = new Putnik[] {
                new Putnik("1"),
                new Putnik("2"),
                new Putnik("3"),
                null
        };

        putnici[0].setKarta(new BiznisKlasa(1_000, false, 200));
        putnici[1].setKarta(new BiznisKlasa(1_000, true, 200));
        putnici[2].setKarta(new EkonomskaKlasa(1_000, 5, 200));

        putniciField.setAccessible(true);
        putniciField.set(underTest, putnici);
        putniciField.setAccessible(false);
    }

    public Putnik[] getDataFromFieldPutnici() throws IllegalAccessException {
        putniciField.setAccessible(true);
        Putnik[] underTestPutnici = (Putnik[]) putniciField.get(underTest);
        putniciField.setAccessible(false);

        return underTestPutnici;
    }

    @Test
    public void dajZaradu() {
        // arrange
        double expectedResult = 3_600; //= 1_000 + (1_000 + 200) + (0.7 * (1_000 + 5 * 200));

        // act
        double actualResult = underTest.dajZaradu();

        // assert
        assertEquals(expectedResult, actualResult, 0.0001);
    }

    @Test
    public void dajPopust() {
        // arrange
        double expectedResult = 300; // = 5 * 200 * 0.3;

        // act
        double actualResult = underTest.dajPopust();

        // assert
        assertEquals(expectedResult, actualResult, 0.001);
    }

    @Test
    public void ukrcajPutnika_withoutTicket() {
        // arrange
        Putnik putnik = new Putnik("Pera");

        try {
            // act
            underTest.ukrcajPutnika(putnik);
            fail("Exception should be thrown because user Pera does not have a ticket");
        } catch (Exception e) {
            // assert
            assertEquals("Putnik Pera nema kartu!", e.getMessage());
        }
    }

    @Test
    public void ukrcajPutnika_withEconomyClassTicket() throws Exception {
        // arrange
        Putnik putnik = new Putnik("Pera");
        Karta karta = new EkonomskaKlasa(1000, 2, 100);
        putnik.setKarta(karta);

        // act
        underTest.ukrcajPutnika(putnik);

        // assert
        Putnik[] underTestPutnici = getDataFromFieldPutnici();
        assertEquals(putnik, underTestPutnici[3]);
    }

    @Test
    public void ukrcajPutnika_withBusinessClassTicket() throws Exception {
        // arrange
        Putnik putnik = new Putnik("Pera");
        Karta karta = new BiznisKlasa(1000, false, 100);
        putnik.setKarta(karta);

        // act
        underTest.ukrcajPutnika(putnik);

        // assert
        Putnik[] underTestPutnici = getDataFromFieldPutnici();
        assertEquals(putnik, underTestPutnici[2]);
    }

    @Test
    public void ukrcajPutnika_thereIsNoAvailableSeatInEconomyClass() {
        // arrange
        Putnik putnik1 = new Putnik("Pera");
        Putnik putnik2 = new Putnik("Mika");

        Karta karta1 = new EkonomskaKlasa(1000, 2, 100);
        putnik1.setKarta(karta1);

        Karta karta2 = new EkonomskaKlasa(1000, 2, 100);
        putnik1.setKarta(karta2);

        try {
            // act
            underTest.ukrcajPutnika(putnik1);
            underTest.ukrcajPutnika(putnik2);
            fail("An exception should be thrown because the ship doesn't have any seat available for passenger's class");
        } catch (Exception e) {
            // assert
            assertEquals("Nema dovoljno mesta u EkonomskaKlasa za putnika Mika.", e.getMessage());
        }
    }

    @Test
    public void ukrcajPutnika_thereIsNoAvailableSeatInBusinessClass() {
        // arrange
        Putnik putnik = new Putnik("Pera");

        Karta karta = new BiznisKlasa(1000, true, 100);
        putnik.setKarta(karta);

        try {
            // act
            underTest.ukrcajPutnika(putnik);
            fail("An exception should be thrown because the ship doesn't have any seat available for passenger's class");
        } catch (Exception e) {
            // assert
            assertEquals("Nema dovoljno mesta u BiznisKlasa za putnika Pera.", e.getMessage());
        }
    }

    @Test
    public void iskrcajPutnika_passengerExists() throws Exception {
        // arrange

        // act
        underTest.iskrcajPutnika(putnici[1]);

        // assert
        Putnik[] underTestPutnici = getDataFromFieldPutnici();
        assertNull(underTestPutnici[1]);
    }

    @Test
    public void iskrcajPutnika_passengerDoesNotExist() {
        // arrange
        Putnik putnik = new Putnik("Pera");

        try {
            // act
            underTest.iskrcajPutnika(putnik);
            fail("An exception should be thrown because Pera is not a passenger");
        } catch (Exception e) {
            // assert
            assertEquals("Putnik Pera ne postoji na brodu!", e.getMessage());
        }

    }

    @Test
    public void testToString() {
        // arrange

        // act
        String strRepr = underTest.toString();

        // assert
        System.out.println(strRepr);

        assertNotNull(strRepr);
        assertTrue(strRepr.contains(shipName));
        assertTrue(strRepr.contains(captainName));
        assertTrue(strRepr.contains("Putnik{ime='1', karta=BiznisKlasa}"));
        assertTrue(strRepr.contains("Putnik{ime='2', karta=BiznisKlasa}"));
        assertTrue(strRepr.contains("Putnik{ime='3', karta=EkonomskaKlasa}"));

    }
}