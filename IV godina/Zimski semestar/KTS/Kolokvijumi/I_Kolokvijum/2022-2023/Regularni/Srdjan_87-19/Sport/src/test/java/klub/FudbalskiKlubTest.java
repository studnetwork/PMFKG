package klub;

import izuzeci.NemaDovoljnoNovca;
import izuzeci.SportistaNijeOdgovarajuci;
import org.junit.Before;
import org.junit.Test;
import osobe.Fudbaler;
import osobe.Kosarkas;

import static org.junit.Assert.*;

public class FudbalskiKlubTest {

    private FudbalskiKlub fudbalskiKlub;

    @Before
    public void setUp() throws Exception {
        fudbalskiKlub = new FudbalskiKlub("IMI klub",100000);
    }

    @Test
    public void potpisiUgovor_sa_kosarkasem() {
        // arrange
        Kosarkas kosarkas = new Kosarkas("Petrovic",13);

        // act
        try {
            fudbalskiKlub.potpisiUgovor(kosarkas, 110_000);
        } catch (SportistaNijeOdgovarajuci e) {
            assertEquals("Petrovic nije fudbaler", e.getMessage());
        }
    }

    @Test(expected = NemaDovoljnoNovca.class)
    public void potpisiUgovor_sa_fudbalerom() throws SportistaNijeOdgovarajuci {
        // arrange
        Fudbaler fudbaler = new Fudbaler("Mitrovic",12);

        // act
        fudbalskiKlub.potpisiUgovor(fudbaler, 110_000);
    }
}