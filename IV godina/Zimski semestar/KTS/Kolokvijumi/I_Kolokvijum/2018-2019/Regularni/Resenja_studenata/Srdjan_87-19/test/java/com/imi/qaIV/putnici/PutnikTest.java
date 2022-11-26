package com.imi.qaIV.putnici;

import org.junit.Before;
import org.junit.Test;

import java.lang.reflect.Field;

import static org.junit.Assert.*;

public class PutnikTest {

    private Putnik underTest;

    @Before
    public void setUp() throws Exception {
        underTest = new Putnik("Pera");
    }

    @Test
    public void defaultValueForIdGenIs0() throws NoSuchFieldException, IllegalAccessException {
        // arrange
        Class<Putnik> clazz = Putnik.class;
        Field idGen = clazz.getDeclaredField("idGen");
        idGen.setAccessible(true);

        // act
        // assert
        assertEquals(0, idGen.getInt(underTest));

        idGen.setAccessible(false); // is necessary?
    }

    @Test
    public void toString_userWithTicket() {
        // arrange

        // act
        String strRepr = underTest.toString();

        // assert
        System.out.println(strRepr);

        assertNotNull(strRepr);
        assertNull(underTest.getKarta());

        assertTrue(strRepr.contains("Pera"));
        assertTrue(strRepr.contains("Nema kartu!"));
    }

    @Test
    public void toString_userWithoutTicket() {
        // arrange
        Karta newKarta = new BiznisKlasa(1000, false, 0);
        underTest.setKarta(newKarta);

        // act
        String strRepr = underTest.toString();
        Karta karta = underTest.getKarta();

        // assert
        System.out.println(strRepr);

        assertNotNull(strRepr);
        assertNotNull(karta);

        assertTrue(strRepr.contains("Pera"));
        assertTrue(strRepr.contains("BiznisKlasa"));
        assertTrue(strRepr.contains("1000"));
    }
}