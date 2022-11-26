package com.imi.qaIV.luka;

import com.imi.qaIV.putnici.BiznisKlasa;
import com.imi.qaIV.putnici.Karta;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ErrorCollector;

import java.lang.reflect.Field;

import static org.hamcrest.CoreMatchers.equalTo;
import static org.junit.Assert.*;

public class SkladisteTest {
    @Rule
    public ErrorCollector collector = new ErrorCollector();

    private static Field kapacitetField;
    private static Field popunjenostField;

    private static Field brojBrodovaField;

    private Skladiste underTest;
    private final double capacity = 20;

    @BeforeClass
    public static void setUpClass() throws NoSuchFieldException {
        popunjenostField = Skladiste.class.getDeclaredField("popunjenost");
        brojBrodovaField = Skladiste.class.getDeclaredField("brojBrodova");
        kapacitetField = Skladiste.class.getDeclaredField("kapacitet");
    }

    @Before
    public void setUp() throws Exception {
        underTest = new Skladiste(capacity);
    }

    @Test
    public void testConstructor() throws NoSuchFieldException, IllegalAccessException {
        // arrange

        // act

        // assert
        double kapacitet = getDataFromFieldKapacitet();
        double popunjenost = getDataFromFieldPopunjenost();
        int brojBrodova = getDataFromFieldBrojBrodova();

        // collector is used to continue the test even if one of asserts fail
        collector.checkThat(kapacitet, equalTo(20.0));
        collector.checkThat(popunjenost, equalTo(0.0));
        collector.checkThat(brojBrodova, equalTo(0));
    }

    public double getDataFromFieldKapacitet() throws IllegalAccessException {
        kapacitetField.setAccessible(true);
        double kapacitet = (double) kapacitetField.get(underTest);
        kapacitetField.setAccessible(false);

        return kapacitet;
    }

    public double getDataFromFieldPopunjenost() throws IllegalAccessException {
        popunjenostField.setAccessible(true);
        double popunjenost = (double) popunjenostField.get(underTest);
        popunjenostField.setAccessible(false);

        return popunjenost;
    }

    public int getDataFromFieldBrojBrodova() throws IllegalAccessException {
        brojBrodovaField.setAccessible(true);
        int brojBrodova = (int) brojBrodovaField.get(underTest);
        brojBrodovaField.setAccessible(false);

        return brojBrodova;
    }

    @Test
    public void checkDefaultValueForCapacity() throws IllegalAccessException {
        // arrange
        double expectedResult = 0.0;

        // act
        double actualResult = getDataFromFieldPopunjenost();

        // assert
        assertEquals(expectedResult, actualResult, 0.001);
    }

    @Test
    public void checkDefaultValueForNumOfShips() throws IllegalAccessException {
        // arrange
        int expectedResult = 0;

        // act
        int actualResult = getDataFromFieldBrojBrodova();

        // assert
        assertEquals(expectedResult, actualResult);
    }

    @Test
    public void testToString() {
        // assert

        // act
        String strRepr = underTest.toString();

        // assert
        System.out.println(strRepr);

        assertNotNull(strRepr);

        // TODO: make better test (format should be defined before that)
        assertTrue(strRepr.contains(String.valueOf(capacity)));
        assertTrue(strRepr.contains("popunjenost=0.0"));
        assertTrue(strRepr.contains("brojBrodova=0"));
    }
}