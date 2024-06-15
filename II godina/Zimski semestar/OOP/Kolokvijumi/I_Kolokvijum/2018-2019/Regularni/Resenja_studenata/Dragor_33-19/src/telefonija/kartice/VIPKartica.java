package telefonija.kartice;

public class VIPKartica extends MobilnaKartica implements IPopust
{
	public VIPKartica(String broj)
	{
		super(broj);
	}
	
	public double dajPopust() {
		return 100;
	}
	
	@Override
	public double dajRacun()
	{
		return super.dajRacun() - dajPopust();
	}
}
