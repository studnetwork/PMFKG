package telefonija;

import telefonija.kartice.Cenovnik;

public class FiksniTelefon extends Telefon
{
	private int potroseniMinuti;
	private String brojTelefona;
	
	
	public FiksniTelefon(String proizvodjac, String brTel)
	{
		super(proizvodjac);
		brojTelefona = brTel;
	}

	public void razgovor(int min)
	{
		potroseniMinuti += min;
	}
	
	@Override
	public double dajRacun()
	{
		return potroseniMinuti*Cenovnik.getCenaMinutaFiksneTelefonije();
	}
	
	public String getBrojTelefona() {
		return brojTelefona;
	}

}
