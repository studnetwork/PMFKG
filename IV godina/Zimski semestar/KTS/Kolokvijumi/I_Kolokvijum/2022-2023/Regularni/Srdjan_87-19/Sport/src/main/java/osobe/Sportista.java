package osobe;
import common.MerljivUcinak;
import klub.Klub;
import turnir.Statistika;

public abstract class Sportista extends Osoba  implements MerljivUcinak
{
	private Menadzer menadzer = null;
	private int brojNaDresu;
	private Klub klub = null;
	
	public Sportista(String ime, int brojNaDresu) 
	{
		super(ime);
		this.brojNaDresu = brojNaDresu;
	}

	@Override
	public abstract int indeksKorisnosti();
	
	public abstract void dodajStatistiku(Statistika statistika);
	
	public void setKlub(Klub klub)
	{
		this.klub = klub;
	}
	
	public boolean equals(int brojNaDresu)
	{
		if(this.brojNaDresu == brojNaDresu)
			return true;
		else
			return false;
	}
	
	public void setMenadzer(Menadzer menadzer)
	{
		this.menadzer = menadzer;
	}
	
	
	
}
