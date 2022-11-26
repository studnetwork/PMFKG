package com.imi.qaIV.putnici;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class BiznisKlasaTest {

    @Before
    public void setUp() throws Exception {
    }

    @Test
    public void dajCenuKarte_tickedIsUsed() {
        // arrange
        BiznisKlasa underTest = new BiznisKlasa(2000, true, 500);

        // act
        double price =  underTest.dajCenuKarte();

        // arrange
        assertEquals(2500, price, 0.0001);
    }

    @Test
    public void dajCenuKarte_tickedIsNotUsed() {
        // arrange
        BiznisKlasa underTest = new BiznisKlasa(2000, false, 500);

        // act
        double price =  underTest.dajCenuKarte();

        // arrange
        assertEquals(2000, price, 0.0001);
    }
}