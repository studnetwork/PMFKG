package osobe;

import turnir.Statistika;
import turnir.TIP_STATISTIKE;

public class Kosarkas extends Sportista
{
	int brojKoseva;
	int brojAsistencija;

	public Kosarkas(String ime, int brojNaDresu) 
	{
		super(ime, brojNaDresu);
	}

	@Override
	public int indeksKorisnosti() 
	{
		if (brojAsistencija == 0 || brojKoseva == 0)
		{
			if (brojAsistencija!=0) return brojAsistencija;
			if (brojKoseva !=0) return brojKoseva;
		}
		return brojKoseva * brojAsistencija;
	}

	@Override
	public void dodajStatistiku(Statistika statistika) 
	{
		if (this.equals(statistika.getBrojNaDresu())) {
			if (statistika.getTipStatistike() == TIP_STATISTIKE.ASISTENCIJE)
				this.brojAsistencija += statistika.getOstvareniUcinak();
			else if (statistika.getTipStatistike() == TIP_STATISTIKE.KOSEVI)
				brojKoseva += statistika.getOstvareniUcinak();
		}

	}
}
