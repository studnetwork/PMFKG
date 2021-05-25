package telefonija;

abstract public class Telefon
{
	private String proizvodjac;
	
	public Telefon(String proizvodjac)
	{
		this.proizvodjac = proizvodjac;
	}
	
	abstract public double dajRacun();
	
	public String getProizvodjac() {
		return proizvodjac;
	}
	
	@Override
	public String toString()
	{
		if(this instanceof FiksniTelefon)
			return "Fiksni telefon: " + ((FiksniTelefon)this).getBrojTelefona() + "\n" + dajRacun();
		else if(this instanceof MobilniTelefon)
			return "Mobilni telefon: " + ((MobilniTelefon)this).dajBrojeveKartica() + "\n" + dajRacun();
		
		return "";
	}
}
