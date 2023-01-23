package turnir;

import klub.Klub;

public class Utakmica 
{
	Klub domacin;
	Klub gost;
	
	public Utakmica(Klub domacin, Klub gost)
	{
		this.domacin = domacin;
		this.gost = gost;
	}

	public boolean equals(String domacin, String gost)
	{
		if(this.domacin.equals(domacin) && this.gost.equals(gost))
			return true;
		else
			return false;
	}
	
	public void dodajStatistiku(Statistika statistika)
	{
		if(domacin.equals(statistika.getNazivKluba()))
		{
			domacin.dodajStatistikuIgracu(statistika);
		}
		else if(gost.equals(statistika.getNazivKluba()))
		{
			gost.dodajStatistikuIgracu(statistika);
		}
	}
}
