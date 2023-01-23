package osobe;

import turnir.Statistika;
import turnir.TIP_STATISTIKE;

public class Fudbaler extends Sportista
{
	int brojGolova;
	int brojAsistencija;

	public Fudbaler(String ime, int brojNaDresu)  {
		super(ime, brojNaDresu);
	}

	public int indeksKorisnosti() 
	{
		return brojGolova * 10 + brojAsistencija * 5;
	}

	@Override
	public void dodajStatistiku(Statistika statistika) 
	{
		if(statistika.getTipStatistike() == TIP_STATISTIKE.ASISTENCIJE)
			this.brojAsistencija += statistika.getOstvareniUcinak();
		else if(statistika.getTipStatistike() == TIP_STATISTIKE.GOLOVI)
			brojGolova += statistika.getOstvareniUcinak();
		
	}
}
