package prevoz;

import merljivi.*;

public abstract class Avion implements Merljiv
{
	String oznaka;
	double maksimalnaTezina = 1000;
	private double tezinaPrazan;
	
	Merljiv[] merljiviObjekti = new Merljiv[10];
	
	
	/* -- Constructors -- */
	
	public Avion(String oznaka, double maxTezina, double tezinaPrazan) throws Exception
	{
		if(oznaka.length() != 10)
			throw new Exception("Data oznaka aviona je neispravna!");
		if(maxTezina < 0)
			throw new Exception("Data maksimalna tezina aviona je neispravna!");
		if(tezinaPrazan < 0)
			throw new Exception("Data tezina praznog aviona je neispravna!");
		
		this.oznaka = oznaka;
		this.maksimalnaTezina = maxTezina;
		this.tezinaPrazan = tezinaPrazan;
	}
	
	
	/* -- Methods -- */
	
	abstract public void dodajNaSlobodnoMesto(Merljiv objekat) throws Exception;
	abstract public void dodajNaPoziciju(int poz, Merljiv objekat) throws Exception;
	
	public Merljiv uzmiMerljivTip(int poz) throws Exception
	{
		if(poz < 0 || poz >= merljiviObjekti.length)
			throw new Exception("Data vrednost pozicije je neispravna!");
		
		if(merljiviObjekti[poz] == null)
			throw new Exception("Data pozicija je prazna!");
		
		return merljiviObjekti[poz];
	}
	
	@Override
	public String dajNaziv() {
		return oznaka;
	}
	
	@Override
	public double dajTezinu()
	{
		double tezina = 0;
		
		for (Merljiv objekat : merljiviObjekti) {
			if(objekat != null)
				tezina += objekat.dajTezinu();
		}
		
		return tezina + tezinaPrazan;
	}
	
	@Override
	public String toString() {
		return oznaka + "(" + dajTezinu() + ")";
	}
}
