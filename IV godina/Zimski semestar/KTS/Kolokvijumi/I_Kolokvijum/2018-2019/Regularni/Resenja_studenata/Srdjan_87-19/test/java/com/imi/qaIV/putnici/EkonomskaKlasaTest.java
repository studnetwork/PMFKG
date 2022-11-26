package com.imi.qaIV.putnici;

import org.junit.Test;

import static org.junit.Assert.*;

public class EkonomskaKlasaTest {

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