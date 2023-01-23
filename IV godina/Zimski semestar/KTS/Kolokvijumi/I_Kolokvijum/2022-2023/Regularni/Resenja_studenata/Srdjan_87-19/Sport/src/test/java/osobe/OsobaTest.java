package osobe;

import izuzeci.Neuporedivo;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class OsobaTest {

    private Osoba osoba;

    @Before
    public void setUp() throws Exception {
        osoba = new Osoba("Test");
    }

    @After
    public void tearDown() throws Exception {
    }

    @Test
    public void uporedi_1nijeUporediv() {
        // arrange
        Osoba fudbaler = new Fudbaler("Mitrovic", 12);

        // act
        try {
            osoba.uporedi(fudbaler);
            fail("Poziv je metoda 'uporedi' je trebao da baci exception 'Neuporedivo'");
        } catch (Neuporedivo e) {

        }
    }
}