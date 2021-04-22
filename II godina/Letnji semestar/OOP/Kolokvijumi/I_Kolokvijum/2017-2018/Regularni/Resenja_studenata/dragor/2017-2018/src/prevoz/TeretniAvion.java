package prevoz;

import merljivi.*;
import merljivi.tovar.*;

public class TeretniAvion extends Avion {

	public TeretniAvion(String oznaka, double maxTezina, double tezinaPrazan) throws Exception
	{
		super(oznaka, maxTezina, tezinaPrazan);
	}

	@Override
	public void dodajNaSlobodnoMesto(Merljiv objekat) throws Exception
	{
		if(!(objekat instanceof Kontejner))
			throw new Exception("Iskljucivo je moguc prevoz kontejnera!");
		
		if(dajTezinu() + objekat.dajTezinu() > maksimalnaTezina)
			throw new Exception("Nije moguce dodati " + objekat.dajNaziv() + "! (Prevelika tezina)");
		
		for (int i = 0; i < merljiviObjekti.length; i++) {
			if(merljiviObjekti[i] == null) {
				merljiviObjekti[i] = objekat;
				return;
			}
		}
		
		throw new Exception("Nije moguce dodati " + objekat.dajNaziv() + "! (Nedovoljno mesta)");
	}

	@Override
	public void dodajNaPoziciju(int poz, Merljiv objekat) throws Exception
	{
		if(!(objekat instanceof Kontejner))
			throw new Exception("Iskljucivo je moguc prevoz kontejnera!");
		
		if(dajTezinu() + objekat.dajTezinu() > maksimalnaTezina)
			throw new Exception("Nije moguce dodati " + objekat.dajNaziv() + "! (Prevelika tezina)");

		if(merljiviObjekti[poz] != null)
			throw new Exception("Nije moguce dodati " + objekat.dajNaziv() + "! (Zauzeto mesto)");
		
		merljiviObjekti[poz] = objekat;
	}

}
