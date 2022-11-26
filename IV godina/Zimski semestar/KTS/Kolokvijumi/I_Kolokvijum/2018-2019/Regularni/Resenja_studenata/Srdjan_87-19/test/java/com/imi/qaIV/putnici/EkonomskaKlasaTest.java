package com.imi.qaIV.putnici;

import org.junit.Test;

import java.lang.reflect.Field;

import static org.junit.Assert.*;

public class EkonomskaKlasaTest {

    @Test
    public void testConstructor() throws NoSuchFieldException, IllegalAccessException {
        // arrange
        Class EkonomskaKlasaClass = EkonomskaKlasa.class;
        Class KartaClass = Karta.class;

        Field osnovnaCenaField = KartaClass.getDeclaredField("osnovnaCena");
        Field tezinaPrtljagaField = EkonomskaKlasaClass.getDeclaredField("tezinaPrtljaga");
        Field cenaPrtljagaPoKgField = EkonomskaKlasaClass.getDeclaredField("cenaPrtljagaPoKg");

        // act
        EkonomskaKlasa underTest = new EkonomskaKlasa(1_000, 5, 2_000);

        // assert
        osnovnaCenaField.setAccessible(true);
        tezinaPrtljagaField.setAccessible(true);
        cenaPrtljagaPoKgField.setAccessible(true);

        double osnovnaCena = (double) osnovnaCenaField.get(underTest);
        double tezinaPrtljaga = (double) tezinaPrtljagaField.get(underTest);
        double cenaPrtljagaPoKgPrtljaga = (double) cenaPrtljagaPoKgField.get(underTest);

        assertEquals(1_000, osnovnaCena, 0.0001);
        assertEquals(5, tezinaPrtljaga, 0.0001);
        assertEquals(2_000, cenaPrtljagaPoKgPrtljaga, 0.0001);

        osnovnaCenaField.setAccessible(false);
        tezinaPrtljagaField.setAccessible(false);
        cenaPrtljagaPoKgField.setAccessible(false);
    }

    @Test
    public void dajPopust_WeightLessThen10() {
        // arrange
        double weight = 5;
        double expectedDiscount = 30.0;
        EkonomskaKlasa underTest = new EkonomskaKlasa(1_000, weight, 1_000);

        // act
        double actualDiscount = underTest.dajPopust();

        // assert
        assertEquals(expectedDiscount, actualDiscount, 0.0001);
    }

    @Test
    public void dajPopust_WeightGreaterThen10() {
        // arrange
        double weight = 15;
        double expectedDiscount = 20.0;
        EkonomskaKlasa underTest = new EkonomskaKlasa(1_000, weight, 1_000);

        // act
        double actualDiscount = underTest.dajPopust();

        // assert
        assertEquals(expectedDiscount, actualDiscount, 0.0001);
    }

    @Test
    public void dajCenuKarte_basePriceIs1000AndWeight15KgWhere1KgCosts1000() {
        // arrange
        double weight = 15;
        double basePrice = 1_000;
        double pricePerKg = 1_000;
        double expectedPrice = 12_800;
        EkonomskaKlasa underTest = new EkonomskaKlasa(basePrice, weight, pricePerKg);

        // act
        double actualPrice = underTest.dajCenuKarte();

        // assert
        assertEquals(expectedPrice, actualPrice, 0.0001);
    }

    @Test
    public void dajCenuKarte_basePriceIs1000AndWeight5KgWhere1KgCosts1000() {
        // arrange
        double weight = 5;
        double basePrice = 1_000;
        double pricePerKg = 1_000;
        double expectedPrice = 4_200;
        EkonomskaKlasa underTest = new EkonomskaKlasa(basePrice, weight, pricePerKg);

        // act
        double actualPrice = underTest.dajCenuKarte();

        // assert
        assertEquals(expectedPrice, actualPrice, 0.0001);
    }
}