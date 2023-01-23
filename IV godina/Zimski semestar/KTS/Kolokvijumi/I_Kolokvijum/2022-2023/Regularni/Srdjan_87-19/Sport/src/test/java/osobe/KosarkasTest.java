package osobe;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import turnir.Statistika;
import turnir.TIP_STATISTIKE;

import java.util.Arrays;
import java.util.Collection;

import static org.junit.Assert.*;

@RunWith(Parameterized.class)
public class KosarkasTest {

    private Statistika statistika;

    @Parameterized.Parameters
    public static Collection statistike() {
        return Arrays.asList(
                new Statistika(TIP_STATISTIKE.ASISTENCIJE,25,"IMI kosarka", 10),
                new Statistika(TIP_STATISTIKE.KOSEVI,25,"IMI kosarka", 5),
                new Statistika(TIP_STATISTIKE.ASISTENCIJE,12, "IMI kosarka", 12),
                new Statistika(TIP_STATISTIKE.KOSEVI,12,"IMI kosarka", 30)
        );
    }

    public KosarkasTest(Statistika statistika) {
        this.statistika = statistika;
    }

    @Test
    public void dodajStatistiku() {
        // arrange
        Kosarkas kosarkas = new Kosarkas("Petrovic", 25);

        // act
        kosarkas.dodajStatistiku(statistika);

        // assert
        int indeksKorisnosti = kosarkas.indeksKorisnosti();
        assertEquals(statistika.getOstvareniUcinak(), indeksKorisnosti);
    }
}