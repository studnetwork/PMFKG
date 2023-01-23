package osobe;
import common.MerljivUcinak;
import izuzeci.NemaDovoljnoNovca;
import izuzeci.SportistaNijeOdgovarajuci;
import klub.Klub;

public class Menadzer extends Osoba implements MerljivUcinak
{
	Sportista sportisti[];

	public Menadzer(String ime) {
		super(ime);
		sportisti = new Sportista[10];
	}

	@Override
	public int indeksKorisnosti() 
	{
		int s = 0;
		
		for (Sportista sportista : sportisti) {
			if(sportista != null)
				s += sportista.indeksKorisnosti();
		}
		
		return s;
	}
	
	public boolean potpisiUgovorSaKlubom(Sportista sportista, Klub[] klubovi, double cena)
	{
		for (Klub klub : klubovi) 
		{
			try 
			{
				if(klub.potpisiUgovor(sportista, cena))
				{
					sportista.setMenadzer(this);
					return true;
				}
			} 
			catch (NemaDovoljnoNovca | SportistaNijeOdgovarajuci e) 
			{
				System.out.println(e.getMessage());
			}
		}
		
		return false;
	}

}
