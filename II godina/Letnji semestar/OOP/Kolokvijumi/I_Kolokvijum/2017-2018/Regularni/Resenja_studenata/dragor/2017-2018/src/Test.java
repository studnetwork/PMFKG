import merljivi.*;
import merljivi.tovar.*;
import prevoz.*;

public class Test
{
	public static void main(String[] args)
	{
		Aerodrom a = null;
		System.out.println(a instanceof Aerodrom);
		
		Aerodrom nt = new Aerodrom("Nikola Tesla", 2);
		
		// Za putnicki avion
		Osoba[] osobe = new Osoba[2];
		osobe[0] = new Osoba("Pera", 70);
		osobe[1] = new Osoba("Mika", 80);
		
		Paket[] paketi = new Paket[2];
		paketi[0] = new Paket("Tegle meda", 150);
		paketi[1] = new Paket("Graficke karte", 100);
		
		Kontejner kontejner = new Kontejner(100, 3);
		
		PutnickiAvion putnicki = null;
		try {
			putnicki = new PutnickiAvion("PUT3141592", 6000, 3300);

			putnicki.dodajNaSlobodnoMesto(osobe[0]);
			putnicki.dodajNaSlobodnoMesto(osobe[1]);
			putnicki.dodajNaSlobodnoMesto(paketi[0]);
			putnicki.dodajNaSlobodnoMesto(paketi[1]);
			
			putnicki.dodajNaSlobodnoMesto(kontejner);
		}
		catch (Exception exc) {
			System.out.println(exc.getMessage());
		}
		
		nt.AvionSlece(putnicki);
		
		// Za teretni avion
		Kontejner kont = new Kontejner(100, 3);
		try {
			kont.dodajMerljivObjekat(new Paket("Cigle", 500));
			kont.dodajMerljivObjekat(new Paket("Sveske", 400));
			kont.dodajMerljivObjekat(new Paket("Tegle", 100));
		}
		catch (Exception exc) {
			System.out.println(exc.getMessage());
		}
		
		TeretniAvion teretni = null;
		
		try {
			teretni = new TeretniAvion("TER1234567", 13000, 6000);
			teretni.dodajNaSlobodnoMesto(kont);
		}
		catch (Exception exc) {
			System.out.println(exc.getMessage());
		}
		
		nt.AvionSlece(teretni);
		
		// Dodatni kontejner
		Kontejner kont2 = new Kontejner(100, 5);
		try {
			kont2.dodajMerljivObjekat(new Paket("Cigle", 500));
			kont2.dodajMerljivObjekat(new Paket("Cigle", 500));
			kont2.dodajMerljivObjekat(new Paket("Cigle", 500));
			kont2.dodajMerljivObjekat(new Paket("Sveske", 400));
			kont2.dodajMerljivObjekat(new Paket("Tegle", 100));
		}
		catch (Exception exc) {
			System.out.println(exc.getMessage());
		}
		
		nt.DodajMerljivTip("TER1234567", kont2);
		
		System.out.println(nt.dajUkupnuTeznu());
		
		Osoba[] os = nt.dajSpisakosoba();
		for (Osoba osoba : os) {
			if(osoba == null) continue;
			System.out.println(osoba);
		}
		System.out.println(nt);
		
		
		
		nt.AvionPolece("TER1234567");
	}
	
	public static void test_01()
	{
		TeretniAvion tav = null;
		
		try {
			tav = new TeretniAvion("DFF7F89A44", 2000, 1000);
			Kontejner kon = new Kontejner(500, 50);
			for(int i = 0; i < 10; i++)
				kon.dodajMerljivObjekat(new Paket("Prazne konzerve", 45));
			
			tav.dodajNaSlobodnoMesto(kon);
		}
		catch (Exception exc) {
			System.out.println("ERR: " + exc.getMessage());
			exc.printStackTrace();
		}
		
		System.out.println(tav);
		
		// --------
		
		PutnickiAvion pav = null;
		
		try {
			pav = new PutnickiAvion("98E7FFW89A", 700, 3300);
			
			pav.dodajNaSlobodnoMesto(new Osoba("Pera", 70));
			pav.dodajNaSlobodnoMesto(new Osoba("Mika", 65));
			pav.dodajNaSlobodnoMesto(new Osoba("Laza", 60));
		}
		catch (Exception exc) {
			System.out.println("ERR: " + exc.getMessage());
			exc.printStackTrace();
		}
		
		System.out.println(pav);
	}

}
