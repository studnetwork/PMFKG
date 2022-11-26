package com.imi.qaIV.luka.brodovi;

import org.junit.Test;

import static org.junit.Assert.*;

public class BrodTest {

    // TODO: add test for constructor

    @Test
    public void testToString() {
        // assert
        String shipName = "Putnicki brod";
        String captainName = "Pera";
        Brod underTest = new PutnickiBrod(shipName, captainName, 10, 10);

        // act
        String strRepr = underTest.toString();

        // assert
        System.out.println(strRepr);

        assertNotNull(strRepr);
        assertTrue(strRepr.contains(captainName));
        assertTrue(strRepr.contains(shipName));
    }
}