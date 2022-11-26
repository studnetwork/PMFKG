package com.imi.qaIV.luka;

import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;

import java.lang.reflect.Field;

import static org.junit.Assert.*;

public class SkladisteTest {

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
    public void testConstructor() throws IllegalAccessException {
        // arrange
        double expectedResult = capacity;

        // act
        double actualResult = getDataFromFieldKapacitet();

        // assert
        assertEquals(expectedResult, actualResult, 0.001);
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