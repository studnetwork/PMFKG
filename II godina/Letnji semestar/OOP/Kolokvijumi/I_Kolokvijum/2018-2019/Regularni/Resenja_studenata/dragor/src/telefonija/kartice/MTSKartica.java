package telefonija.kartice;

public class MTSKartica extends MobilnaKartica
{
	private int besplatniMinuti;
	
	public MTSKartica(String broj, int bmin)
	{
		super(broj);
		besplatniMinuti = bmin;
	}
	
	@Override
	public double dajRacun()
	{
		int min = getPotroseniMinuti() - besplatniMinuti;
		double umanjenje = ((min >= 0)? besplatniMinuti : getPotroseniMinuti()) * Cenovnik.getCenaMinutaMobilneTelefonije();
		return super.dajRacun() - umanjenje;
	}
}
