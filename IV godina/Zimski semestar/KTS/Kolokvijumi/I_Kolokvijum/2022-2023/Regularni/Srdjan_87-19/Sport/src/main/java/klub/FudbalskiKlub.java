package klub;

import izuzeci.NemaDovoljnoNovca;
import izuzeci.SportistaNijeOdgovarajuci;
import osobe.Fudbaler;
import osobe.Kosarkas;
import osobe.Sportista;
import turnir.Statistika;

public class FudbalskiKlub extends Klub 
{
	public FudbalskiKlub(String nazivKluba, double budzet)
	{
		super(nazivKluba, budzet);
		
		igraci = new Sportista[11];
	}
	
	@Override
	public boolean potpisiUgovor(Sportista sportista, double cena) throws  SportistaNijeOdgovarajuci
	{

		if(sportista instanceof Fudbaler)
		{
			if(budzet >= cena)
			{
				budzet -= cena;
				
				for (int i = 0; i < igraci.length; i++) {
					if(igraci[i] == null)
					{
						igraci[i] = sportista;
						break;
					}
				}
				
				return true;
			}
			else return false;
		}
		else throw new SportistaNijeOdgovarajuci(sportista.getIme() + " nije fudbaler");

	}



}
