package prevoz;

import merljivi.*;
import merljivi.tovar.*;

public class PutnickiAvion extends Avion {

	public PutnickiAvion(String oznaka, double maxTezina, double tezinaPrazan) throws Exception
	{
		super(oznaka, maxTezina, tezinaPrazan);
	}

	@Override
	public void dodajNaSlobodnoMesto(Merljiv objekat) throws Exception
	{
		if(!(objekat instanceof Osoba) && !(objekat instanceof Paket))
			throw new Exception("Iskljucivo je moguc prevoz osoba i paketa!");
		
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
		if(!(objekat instanceof Osoba) && !(objekat instanceof Paket))
			throw new Exception("Iskljucivo je moguc prevoz osoba i paketa!");
		
		if(dajTezinu() + objekat.dajTezinu() > maksimalnaTezina)
			throw new Exception("Nije moguce dodati " + objekat.dajNaziv() + "! (Prevelika tezina)");

		if(merljiviObjekti[poz] != null)
			throw new Exception("Nije moguce dodati " + objekat.dajNaziv() + "! (Zauzeto mesto)");
		
		merljiviObjekti[poz] = objekat;
	}
	
	@Override
	public String toString()
	{
		String s = super.toString() + "\n";
		
		for (Merljiv objekat : merljiviObjekti)
		{
			if(objekat != null)
				s += " - " + objekat.dajNaziv() + "\n";
		}
		
		return s;
	}

}
