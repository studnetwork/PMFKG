package turnir;

import klub.FudbalskiKlub;
import klub.KosarkasiKlub;
import org.hamcrest.MatcherAssert;
import org.junit.Test;
import static org.hamcrest.Matchers.*;


import java.util.Arrays;

import static org.junit.Assert.*;

public class TurnirTest {

    @Test
    public void dodajUtakmicu() {
        // arrange
        KosarkasiKlub kosarkasiKlub1 = new KosarkasiKlub("PMF kosarka", 150);
        KosarkasiKlub kosarkasiKlub2 = new KosarkasiKlub("FIN kosarka", 200);
        KosarkasiKlub kosarkasiKlub3 = new KosarkasiKlub("EKF kosarka", 500);

        FudbalskiKlub fudbalskiKlub1 = new FudbalskiKlub("PMF fudbal", 1500);
        FudbalskiKlub fudbalskiKlub2 = new FudbalskiKlub("FIN fudbal", 2000);

        Turnir turnir = new Turnir();

        // act
        turnir.dodajUtakmicu(new Utakmica(kosarkasiKlub1, kosarkasiKlub2));
        turnir.dodajUtakmicu(new Utakmica(kosarkasiKlub1, kosarkasiKlub3));
        turnir.dodajUtakmicu(new Utakmica(kosarkasiKlub2, kosarkasiKlub3));

        turnir.dodajUtakmicu(new Utakmica(fudbalskiKlub1, fudbalskiKlub2));

        // assert
        assertEquals(3, Arrays.stream(turnir.fudbalskeUtakmice).count());
        assertEquals(1, Arrays.stream(turnir.fudbalskeUtakmice).count());
    }

    @Test
    public void dodajUtakmicu2() {
        // arrange
        KosarkasiKlub kosarkasiKlub1 = new KosarkasiKlub("PMF kosarka", 150);
        KosarkasiKlub kosarkasiKlub2 = new KosarkasiKlub("FIN kosarka", 200);
        KosarkasiKlub kosarkasiKlub3 = new KosarkasiKlub("EKF kosarka", 500);

        Utakmica utakmica1 = new Utakmica(kosarkasiKlub1, kosarkasiKlub2);
        Utakmica utakmica2 = new Utakmica(kosarkasiKlub1, kosarkasiKlub3);
        Utakmica utakmica3 = new Utakmica(kosarkasiKlub2, kosarkasiKlub3);

                Turnir turnir = new Turnir();

        // act
        turnir.dodajUtakmicu(utakmica1);
        turnir.dodajUtakmicu(utakmica2);
        turnir.dodajUtakmicu(utakmica3);

        // assert
        MatcherAssert.assertThat(turnir.kosarkaskeUtakmice, hasItemInArray(utakmica1));
        MatcherAssert.assertThat(turnir.kosarkaskeUtakmice, hasItemInArray(utakmica2));
        MatcherAssert.assertThat(turnir.kosarkaskeUtakmice, hasItemInArray(utakmica3));
    }
}