package turnir;

import klub.FudbalskiKlub;
import klub.Klub;
import klub.KosarkasiKlub;



public class Turnir 
{
	Utakmica kosarkaskeUtakmice[];
	Utakmica fudbalskeUtakmice[];
	
	public Turnir()
	{
		kosarkaskeUtakmice = new Utakmica[50];
		fudbalskeUtakmice = new Utakmica[50];
	}
	
	public void dodajUtakmicu(Utakmica utakmica)
	{
		if(utakmica.domacin instanceof KosarkasiKlub)
		{
			for (int i = 0; i < kosarkaskeUtakmice.length; i++) {
				if(kosarkaskeUtakmice[i] == null)
				{
					kosarkaskeUtakmice[i] = utakmica;
					break;
				}
				else{
					break;
				}
			}
		}
		else
		{
			for (int i = 0; i < fudbalskeUtakmice.length; i++) {
				if(fudbalskeUtakmice[i] == null)
				{
					fudbalskeUtakmice[i] = utakmica;
					break;
				}
			}
		}
	}

	public void upisiStatistiku(TIP_SPORTA tipSporta, String domacin, String gost, Statistika statistika)
	{
		Utakmica[] utakmice;
		
		if(tipSporta == TIP_SPORTA.FUDBAL)
		{
			utakmice = fudbalskeUtakmice;
		}
		else
		{
			utakmice = kosarkaskeUtakmice;
		}
		
		for (Utakmica utakmica : utakmice) {
			if(utakmica != null && utakmica.equals(domacin, gost))
			{
				utakmica.dodajStatistiku(statistika);
				break;
			}
		}
	}
	
}
