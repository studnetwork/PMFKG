package merljivi;

public class Osoba implements Merljiv
{
	protected String ime;
	protected double tezina;

	public Osoba(String ime, double tezina)
	{
		this.ime = ime;
		this.tezina = tezina;
	}
	
	@Override
	public double dajTezinu() {
		return tezina;
	}

	@Override
	public String dajNaziv() {
		return ime;
	}
	
	@Override
	public String toString() {
		return ime + "(" + tezina + ")";
	}
}
