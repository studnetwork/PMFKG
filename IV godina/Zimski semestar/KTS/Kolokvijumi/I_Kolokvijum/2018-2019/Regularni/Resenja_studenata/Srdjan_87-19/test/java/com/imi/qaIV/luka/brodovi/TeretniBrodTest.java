package com.imi.qaIV.luka.brodovi;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class TeretniBrodTest {
    private String shipName = "TBrod";
    private String captainName = "Pera";

    private TeretniBrod underTest;

    @Before
    public void setUp() throws Exception {
        underTest = new TeretniBrod(
                shipName, captainName, 10, 8, 600);
    }

    @Test
    public void dajUkupnuZapreminuKontejnera() {
        // arrange
        double expectedResult = 80; // = 10 * 8;

        // act
        double actualResult = underTest.dajUkupnuZapreminuKontejnera();

        // assert
        assertEquals(expectedResult, actualResult, 0.001);
    }

    @Test
    public void dajZaradu() {
        // arrange
        double expectedResult = 48_000; // = 10 * 8 * 600;

        // act
        double actualResult = underTest.dajZaradu();

        // assert
        assertEquals(expectedResult, actualResult, 0.001);
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
        assertTrue(strRepr.contains("ukupnaZapreminuKontejnera=80.0"));
    }
}