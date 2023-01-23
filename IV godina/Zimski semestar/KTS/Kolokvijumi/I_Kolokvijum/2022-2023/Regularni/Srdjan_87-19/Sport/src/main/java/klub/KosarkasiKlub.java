package klub;

import izuzeci.NemaDovoljnoNovca;
import izuzeci.SportistaNijeOdgovarajuci;
import osobe.Kosarkas;
import osobe.Sportista;
import turnir.Statistika;

public class KosarkasiKlub extends Klub 
{
	public KosarkasiKlub(String nazivKluba, double budzet)
	{
		super(nazivKluba, budzet);
		
		igraci = new Sportista[5];
	}
	
	@Override
	public boolean potpisiUgovor(Sportista sportista, double cena) throws NemaDovoljnoNovca, SportistaNijeOdgovarajuci 
	{
		
		if(sportista instanceof Kosarkas)
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
			else throw new NemaDovoljnoNovca(sportista.getIme() + " je skup za tim " + nazivKluba);
				
		}
		else throw new SportistaNijeOdgovarajuci(sportista.getIme() + " nije kosarkas");
		

	}


	
}
