package prevoz;

import merljivi.*;

public class Aerodrom
{
	String naziv;
	Avion[] avioni;

	
	/* -- Constructors -- */
	
	public Aerodrom(String naziv, int brAviona)
	{
		this.naziv = naziv;
		avioni = new Avion[brAviona];
	}
	
	
	/* -- Methods -- */
	
	public void AvionPolece(String oznaka)
	{
		for (int i = 0; i < avioni.length; i++) {
			if(avioni[i].dajNaziv() == oznaka) {
				avioni[i] = null;
				return;
			}
		}
	}
	
	public void AvionSlece(Avion avion)
	{
		if(avion == null)
			return;
		
		for (int i = 0; i < avioni.length; i++) {
			if(avioni[i] == null) {
				avioni[i] = avion;
				return;
			}
		}
	}
	
	public void DodajMerljivTip(String oznaka, Merljiv objekat)
	{
		try {
			for (Avion avion : avioni) {
				if(avion != null && avion.dajNaziv() == oznaka) {
					avion.dodajNaSlobodnoMesto(objekat);
					break;
				}
			}
		}
		catch (Exception exc) {
			System.out.println(exc.getMessage());
		}
	}
	
	public Osoba[] dajSpisakosoba()
	{
		Osoba[] putnici = new Osoba[100];
		int i = 0;
		
		for (Avion avion : avioni) {
			if(avion == null) continue;
			for (Merljiv objekat : avion.merljiviObjekti) {
				if(objekat != null && objekat instanceof Osoba)
					putnici[i++] = (Osoba)objekat;
			}
		}
		
		return putnici;
	}
	
	public double dajUkupnuTeznu()
	{
		double tezina = 0;
		
		for (Avion avion : avioni) {
			if(avion == null) continue;
			for (Merljiv objekat : avion.merljiviObjekti) {
				if(objekat != null)
					tezina += objekat.dajTezinu();
			}
		}
		
		return tezina;
	}
	
	@Override
	public String toString()
	{
		String s = "";
		
		for (Avion avion : avioni) {
			if(avion == null) continue;
			s += (avion instanceof TeretniAvion)? "T" : ((avion instanceof PutnickiAvion)? "P" : "");
			s += " " + avion.dajNaziv() + " " + avion.dajTezinu() + "\n";
			
			for (Merljiv objekat : avion.merljiviObjekti) {
				if(objekat == null) continue;
				s += objekat.dajNaziv() + " ";
			}
			s += "\n";
		}
		
		return s;
	}
}
