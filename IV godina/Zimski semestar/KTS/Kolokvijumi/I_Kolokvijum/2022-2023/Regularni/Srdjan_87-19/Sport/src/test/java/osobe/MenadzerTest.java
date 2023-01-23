package osobe;

import izuzeci.NemaDovoljnoNovca;
import izuzeci.SportistaNijeOdgovarajuci;
import klub.FudbalskiKlub;
import klub.Klub;
import org.hamcrest.MatcherAssert;
import org.hamcrest.Matchers;
import org.junit.Before;
import org.junit.Test;
import org.mockito.Mockito;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.List;

import static org.junit.Assert.*;

public class MenadzerTest {

    private final PrintStream originalOut = System.out;
    private Menadzer menadzer;

    @Before
    public void setUp() throws Exception {
        menadzer = new Menadzer("Petar");
    }

    // javni konstruktor koji prihvata ime i instancira niz sportista na 10 elemenata
    @Test
    public void testirajKonstruktor() {
        // arrange

        // act

        // assert
        MatcherAssert.assertThat(menadzer.sportisti, Matchers.arrayWithSize(10));

        // ovo bi mozda trebalo da se uradi preko field-ova jer getIme moze da bude kompleksnije od
        // obicnog getter-a koji vraca vrednost polja
        MatcherAssert.assertThat(menadzer.getIme(), Matchers.equalTo("Petar"));
    }

    // javni pregaženi metod indeksKorisnosti koji vraća sumu indeksa korisnosti svih sportista koje
    // menadžer zastupa
    @Test
    public void indeksKorisnosti() {
        // assert
        Fudbaler fudbaler = Mockito.mock(Fudbaler.class);
        Kosarkas kosarkas = Mockito.mock(Kosarkas.class);

        Mockito.when(fudbaler.indeksKorisnosti())
                .thenReturn(100);

        Mockito.when(kosarkas.indeksKorisnosti())
                .thenReturn(80);

        menadzer.sportisti[0] = fudbaler;
        menadzer.sportisti[1] = kosarkas;

        // act
        int indeksKorisnosti = menadzer.indeksKorisnosti();

        // assert
        assertEquals(180, indeksKorisnosti);
    }

    // javni metod potpisiUgovorSaKlubom koji prihvata Sportistu i niz klubova sa kojima menadžer treba da
    // potpise ugovor. Ukoliko je potpisivanje uspešno vratiti true i setovati menadzera kod sportiste, u
    // suprotnom vratiti false
    @Test
    public void potpisiUgovorSaKlubom_sa_fudbalerom_baca_exception_NemaDovoljnoNovca() throws NemaDovoljnoNovca, SportistaNijeOdgovarajuci {
        // arrange
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        System.setOut(new PrintStream(out));

        Fudbaler fudbaler = Mockito.mock(Fudbaler.class);

        Klub[] klubovi = new Klub[] {
                Mockito.mock(FudbalskiKlub.class),
                Mockito.mock(FudbalskiKlub.class)
        };

        Mockito.doAnswer((invocation) -> {
            throw new NemaDovoljnoNovca("Nema dovoljno novca");
        }).when(klubovi[0]).potpisiUgovor(Mockito.any(Sportista.class), Mockito.anyDouble());

        Mockito.when(klubovi[1].potpisiUgovor(Mockito.any(Sportista.class), Mockito.anyDouble()))
                .thenReturn(true);

        // act
        menadzer.potpisiUgovorSaKlubom(fudbaler, klubovi, 1_000);

        // assert
        System.setOut(new PrintStream(originalOut));

        assertEquals("Nema dovoljno novca", out.toString().trim());
    }

    @Test
    public void potpisiUgovorSaKlubom_sa_fudbalerom() throws NemaDovoljnoNovca, SportistaNijeOdgovarajuci {
        // arrange
        Fudbaler fudbaler = Mockito.mock(Fudbaler.class);

        Klub[] klubovi = new Klub[] {
                Mockito.mock(FudbalskiKlub.class),
                Mockito.mock(FudbalskiKlub.class)
        };

        Mockito.when(klubovi[0].potpisiUgovor(Mockito.any(Sportista.class), Mockito.anyDouble()))
                .thenReturn(true);

        Mockito.when(klubovi[1].potpisiUgovor(Mockito.any(Sportista.class), Mockito.anyDouble()))
                .thenReturn(true);

        // act
        boolean potpisan = menadzer.potpisiUgovorSaKlubom(fudbaler, klubovi, 1_000);

        // assert
        assertTrue(potpisan);
    }
}