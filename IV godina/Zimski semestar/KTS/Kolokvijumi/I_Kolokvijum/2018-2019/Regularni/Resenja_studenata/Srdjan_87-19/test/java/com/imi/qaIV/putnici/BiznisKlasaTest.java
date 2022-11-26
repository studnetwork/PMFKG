package com.imi.qaIV.putnici;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ErrorCollector;

import java.lang.reflect.Field;

import static org.hamcrest.CoreMatchers.equalTo;
import static org.hamcrest.CoreMatchers.nullValue;
import static org.junit.Assert.*;

public class BiznisKlasaTest {
    @Rule
    public ErrorCollector collector = new ErrorCollector();

    @Before
    public void setUp() throws Exception {
    }

    @Test
    public void testConstructor() throws NoSuchFieldException, IllegalAccessException {
        // arrange
        Class BiznisKlasaClass = BiznisKlasa.class;
        Class KartaClass = Karta.class;

        Field osnovnaCenaField = KartaClass.getDeclaredField("osnovnaCena");
        Field dodatniWifiField = BiznisKlasaClass.getDeclaredField("dodatniWifi");
        Field cenaZaWifiField = BiznisKlasaClass.getDeclaredField("cenaZaWifi");

        // act
        BiznisKlasa underTest = new BiznisKlasa(1_000, true, 2_000);

        // assert
        osnovnaCenaField.setAccessible(true);
        dodatniWifiField.setAccessible(true);
        cenaZaWifiField.setAccessible(true);

        double osnovnaCena = (double) osnovnaCenaField.get(underTest);
        boolean dodatniWifi = (boolean) dodatniWifiField.get(underTest);
        double cenaZaWifi = (double) cenaZaWifiField.get(underTest);

        // collector is used to continue the test even if one of asserts fail
        collector.checkThat(osnovnaCena, equalTo(1_000.0));
        collector.checkThat(dodatniWifi, equalTo(true));
        collector.checkThat(cenaZaWifi, equalTo(2_000.0));

        osnovnaCenaField.setAccessible(false);
        dodatniWifiField.setAccessible(false);
        cenaZaWifiField.setAccessible(false);
    }

    @Test
    public void dajCenuKarte_wifiIsUsed() {
        // arrange
        BiznisKlasa underTest = new BiznisKlasa(2000, true, 500);

        // act
        double price =  underTest.dajCenuKarte();

        // arrange
        assertEquals(2500, price, 0.0001);
    }

    @Test
    public void dajCenuKarte_wifiIsUsed() {
        // arrange
        BiznisKlasa underTest = new BiznisKlasa(2000, false, 500);

        // act
        double price =  underTest.dajCenuKarte();

        // arrange
        assertEquals(2000, price, 0.0001);
    }
}