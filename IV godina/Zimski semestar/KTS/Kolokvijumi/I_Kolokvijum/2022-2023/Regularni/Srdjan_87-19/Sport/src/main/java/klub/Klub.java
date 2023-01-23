package klub;
import common.MerljivUcinak;
import izuzeci.NemaDovoljnoNovca;
import izuzeci.SportistaNijeOdgovarajuci;
import osobe.Sportista;
import turnir.Statistika;

public abstract class Klub
{
	String nazivKluba;
	double budzet;
	Sportista igraci[];
	
	public Klub(String nazivKluba, double budzet)
	{
		this.nazivKluba = nazivKluba;
		this.budzet = budzet;
	}
	
	public abstract boolean potpisiUgovor(Sportista sportista, double cena) throws NemaDovoljnoNovca, SportistaNijeOdgovarajuci;
	
	public void dodajStatistikuIgracu(Statistika statistika)
	{
		
		for (Sportista sportista : igraci) {
			if(sportista.equals(statistika.getBrojNaDresu()))
			{
				sportista.dodajStatistiku(statistika);
				break;
			}
		}
		
	}
	
	public boolean equals(String nazivKluba)
	{
		if(this.nazivKluba == nazivKluba)
			return true;
		else
			return false;
	}
	
	public String toString()
	{
		return nazivKluba;
	}
	
}
