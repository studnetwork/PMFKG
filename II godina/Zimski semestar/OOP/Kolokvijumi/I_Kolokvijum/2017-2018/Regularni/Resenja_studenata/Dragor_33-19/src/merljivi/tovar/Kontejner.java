package merljivi.tovar;

import merljivi.*;

public class Kontejner implements Merljiv
{
	static int idGenerator = 0;
	
	protected int id;
	double tezinaPrazan;
	
	Merljiv[] merljiviObjekti;
	
	public Kontejner(double tezinaPrazan, int kapacitet)
	{
		this.tezinaPrazan = tezinaPrazan;
		merljiviObjekti = new Merljiv[kapacitet];
		
		id = idGenerator;
		idGenerator++;
	}
	
	public void dodajMerljivObjekat(Merljiv objekat) throws Exception
	{
		// Exception: Dodavanje osobe u tovar
		if(objekat instanceof Osoba)
			throw new Exception("Osoba nije tovar!");
		
		for (int i = 0; i < merljiviObjekti.length; i++)
		{
			if(merljiviObjekti[i] == null) {
				merljiviObjekti[i] = objekat;
				return;
			}
		}
		
		// Exception: Nema mesta u kontejneru
		throw new Exception("Nema vise mesta!");
		
	}
	
	public Merljiv izvadiMerljivObjekat(String naziv)
	{
		Merljiv temp = null;
		
		for (int i = 0; i < merljiviObjekti.length; i++)
		{
			if(merljiviObjekti[i].dajNaziv() == naziv)
			{
				temp = merljiviObjekti[i];
				merljiviObjekti[i] = null;
			}
		}
		
		return temp;
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
	public String dajNaziv() {
		return "kontejner: " + id + "(" + dajTezinu() + ")";
	}

}
