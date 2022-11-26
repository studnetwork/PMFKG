package com.imi.qaIV.luka;

import com.imi.qaIV.luka.brodovi.PutnickiBrod;
import com.imi.qaIV.luka.brodovi.TeretniBrod;
import com.imi.qaIV.putnici.BiznisKlasa;
import com.imi.qaIV.putnici.Karta;
import com.imi.qaIV.putnici.Putnik;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Ignore;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import static org.junit.Assert.*;

public class LukaTest {
    private final PrintStream standardOutput = System.out;

    private Luka underTest;

    private Skladiste[] warehouses;
    private final int numOfShips = 1;

    private static Method izbaciKontejnereUSkladistaMethod;

    // @BeforeClass // commented out to hide stacktrace print caused by absence of 'izbaciKontejnereUSkladista'
    public static void setUpClass() {
        try {
            izbaciKontejnereUSkladistaMethod = Luka.class
                    .getDeclaredMethod("izbaciKontejnereUSkladista", TeretniBrod.class);
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
    }

    @Before
    public void setUp() throws Exception {
        warehouses = new Skladiste[] {
            new Skladiste(30),
        };

        underTest = new Luka(numOfShips, warehouses);
    }

    public void callMethodIzbaciKontejnereUSkladista(TeretniBrod teretniBrod)
            throws InvocationTargetException, IllegalAccessException {
        izbaciKontejnereUSkladistaMethod.setAccessible(true);

        izbaciKontejnereUSkladistaMethod.invoke(underTest, teretniBrod);

        izbaciKontejnereUSkladistaMethod.setAccessible(false);
    }

    @Test
    public void prodajKartu() {
        // arrange
        Putnik putnik = new Putnik("Pera");
        Karta karta = new BiznisKlasa(1000, false, 350);

        // act
        underTest.prodajKartu(putnik, karta);

        // assert
        assertEquals(karta, putnik.getKarta());
    }

    @Test
    public void usidriBrod_anchorPassengerShip() throws Exception {
        // arrange
        PutnickiBrod putnickiBrod = new PutnickiBrod(
                "PBrod", "Pera", 2, 2);

        // act
        underTest.usidriBrod(putnickiBrod);

        // assert
        assertEquals(1, warehouses[0].getBrojBrodova());
    }

    @Test
    public void usidriBrod_anchorCargoShip() throws Exception {
        // arrange
        TeretniBrod teretniBrod = new TeretniBrod(
                "TBrod", "Pera", 2, 10, 750);

        // act
        underTest.usidriBrod(teretniBrod);

        // assert

        assertEquals(1, warehouses[0].getBrojBrodova());

        // "dodatno izbacuje kontejnere u skladišta" test
        assertEquals(20, warehouses[0].getPopunjenost(), 0.001);
    }

    @Test
    public void usidriBrod_thereIsNoSpaceForTheShip() {
        // arrange
        TeretniBrod teretniBrod1 = new TeretniBrod(
                "TBrod", "Pera", 2, 10, 650);
        TeretniBrod teretniBrod2 = new TeretniBrod(
                "TBrod", "Mika", 2, 10, 700);

        try {
            // act
            underTest.usidriBrod(teretniBrod1);
            underTest.usidriBrod(teretniBrod2);
        } catch (Exception e) {
            // assert
            assertEquals("Nema mesta u luci!", e.getMessage());
        }
    }

    @Test
    public void izbaciKontejnereUSkladista_addCargoShipWithVolumeOf16()
            throws InvocationTargetException, IllegalAccessException {
        // arrange
        TeretniBrod teretniBrod = new TeretniBrod(
                "TBrod", "Pera", 2, 8, 700);

        // act
        callMethodIzbaciKontejnereUSkladista(teretniBrod);

        // assert
        assertEquals(16, warehouses[0].getPopunjenost(), 0.001);
    }

    @Test
    public void izbaciKontejnereUSkladista_addCargoShipWithVolumeOf32()
            throws InvocationTargetException, IllegalAccessException {
        // arrange
        TeretniBrod teretniBrod = new TeretniBrod(
                "TBrod", "Pera", 4, 8, 700);

        try {
            // act
            callMethodIzbaciKontejnereUSkladista(teretniBrod);
            fail("An exception should be thrown because there is no enough space in the warehouse");
        } catch (Exception e) {
            // assert
            assertEquals("Nema mesta u skladistima!", e.getMessage());
        }

    }

    /**
     * Assumption: method "usidriBrod" is implemented correctly */
    @Test
    public void izlistajUsidreneBrodove() throws Exception {
        // arrange

        // Redirect output to the buffer
        final ByteArrayOutputStream newOut = new ByteArrayOutputStream();
        System.setOut(new PrintStream(newOut));

        TeretniBrod teretniBrod = new TeretniBrod(
                "TBrod", "Pera", 2, 8, 600);

        underTest.usidriBrod(teretniBrod);

        // act
        underTest.izlistajUsidreneBrodove();
        String actualResult = newOut.toString();

        // assert
        System.setOut(standardOutput);
        System.out.println(actualResult);

        assertNotNull(actualResult);

        // TODO: make better test (format should be defined before that)
        assertTrue(actualResult.contains(
                "TeretniBrod{naziv='TBrod', imeKapetanaBroda='Pera'"
                + ", brojKonterjnera=2, zapreminaKontejnera=8, cenaPoMetruKubnom=600}"));
    }

    @Test
    public void izlistajSkladista() {
        // arrange

        // Redirect output to the buffer
        final ByteArrayOutputStream newOut = new ByteArrayOutputStream();
        System.setOut(new PrintStream(newOut));

        TeretniBrod teretniBrod = new TeretniBrod(
                "TBrod", "Pera", 2, 8, 600);

        // act
        underTest.izlistajSkladista();
        String actualResult = newOut.toString();

        // assert
        System.setOut(standardOutput);
        System.out.println(actualResult);

        assertNotNull(actualResult);
        // TODO: make better test (format should be defined before that)
        assertTrue(actualResult.contains(
                "Skladiste{kapacitet=30.0, popunjenost=0.0, brojBrodova=0}"));
    }
}