package com.imi.qaIV.putnici;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ErrorCollector;

import java.lang.reflect.Field;

import static org.hamcrest.CoreMatchers.equalTo;
import static org.hamcrest.CoreMatchers.nullValue;
import static org.junit.Assert.*;

public class PutnikTest {
    @Rule
    public ErrorCollector collector = new ErrorCollector();

    private String name = "Pera";
    private Putnik underTest;

    @Before
    public void setUp() throws Exception {
        underTest = new Putnik(name);
    }

    @Test
    public void testConstructor() throws NoSuchFieldException, IllegalAccessException {
        // arrange
        Class<Putnik> clazz = Putnik.class;

        Field idField = clazz.getDeclaredField("id");
        Field idGenField = clazz.getDeclaredField("idGen");
        Field imeField = clazz.getDeclaredField("ime");
        Field kartaField = clazz.getDeclaredField("karta");


        // act

        // assert
        idField.setAccessible(true);
        idGenField.setAccessible(true);
        imeField.setAccessible(true);
        kartaField.setAccessible(true);

        int id = (int) idField.get(underTest);
        int idGen = (int) idGenField.get(underTest);
        String ime = (String) imeField.get(underTest);
        Karta karta = (Karta) kartaField.get(underTest);

        // collector is used to continue the test even if one of asserts fail
        collector.checkThat(id, equalTo(0));
        collector.checkThat(idGen, equalTo(1));
        collector.checkThat(ime,  equalTo(name));
        collector.checkThat(karta, nullValue());

        idField.setAccessible(false);
        idGenField.setAccessible(false);
        imeField.setAccessible(false);
        kartaField.setAccessible(false);
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