package common;

import org.junit.Before;
import org.junit.Test;
import org.mockito.Mock;
import org.mockito.Mockito;
import osobe.Fudbaler;
import osobe.Kosarkas;
import turnir.Statistika;
import turnir.TIP_STATISTIKE;

import static org.junit.Assert.*;

public class MerljivUcinakTest {

    private Statistika statistikaMock1;
    private Statistika statistikaMock2;

    @Before
    public void setUp() throws Exception {
        statistikaMock1 = Mockito.mock(Statistika.class);
        statistikaMock2 = Mockito.mock(Statistika.class);
    }

    @Test
    public void indeksKorisnosti_kosarkas_Petrovic_20asistencija_15koseva() {
        // arrange
        int brojNaDresu = 13;

        Mockito.when(statistikaMock1.getTipStatistike())
                .thenReturn(TIP_STATISTIKE.ASISTENCIJE);

        Mockito.when(statistikaMock1.getBrojNaDresu())
                .thenReturn(brojNaDresu);

        Mockito.when(statistikaMock1.getOstvareniUcinak())
                .thenReturn(20);


        Mockito.when(statistikaMock2.getTipStatistike())
                .thenReturn(TIP_STATISTIKE.KOSEVI);

        Mockito.when(statistikaMock2.getBrojNaDresu())
                .thenReturn(brojNaDresu);

        Mockito.when(statistikaMock2.getOstvareniUcinak())
                .thenReturn(15);

        Kosarkas kosarkas = new Kosarkas("Petrovic", brojNaDresu);
        kosarkas.dodajStatistiku(statistikaMock1);
        kosarkas.dodajStatistiku(statistikaMock2);

        // act
        int indeksKorisnosti = kosarkas.indeksKorisnosti();

        // assert
        assertEquals(35, indeksKorisnosti);
    }

    @Test
    public void indeksKorisnosti_fudbaler_Mitrovic_20asistencija_2gola() {
        // arrange
        int brojNaDresu = 12;

        Mockito.when(statistikaMock1.getTipStatistike())
                .thenReturn(TIP_STATISTIKE.ASISTENCIJE);

        Mockito.when(statistikaMock1.getBrojNaDresu())
                .thenReturn(brojNaDresu);

        Mockito.when(statistikaMock1.getOstvareniUcinak())
                .thenReturn(20);


        Mockito.when(statistikaMock2.getTipStatistike())
                .thenReturn(TIP_STATISTIKE.GOLOVI);

        Mockito.when(statistikaMock2.getBrojNaDresu())
                .thenReturn(brojNaDresu);

        Mockito.when(statistikaMock2.getOstvareniUcinak())
                .thenReturn(15);

        Fudbaler fudbaler = new Fudbaler("Mitrovic", brojNaDresu);
        fudbaler.dodajStatistiku(statistikaMock1);
        fudbaler.dodajStatistiku(statistikaMock2);

        // act
        int indeksKorisnosti = fudbaler.indeksKorisnosti();

        // assert
        assertEquals(120, indeksKorisnosti);
    }
}