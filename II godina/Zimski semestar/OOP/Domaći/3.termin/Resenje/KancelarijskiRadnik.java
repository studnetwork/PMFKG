public class KancelarijskiRadnik extends Zaposleni
{
	private static double UKUPNA__ISPLATA;

	private static final int KOEFICIJENT_KANC_RADNIKA = 120;

	private String straniJezik;

	public KancelarijskiRadnik( String imeRadnika, String straniJezik )
	{
		super( imeRadnika, false );
		this.straniJezik = straniJezik;	
	}

	@Override
	public void izracunajPlatu( int brojSati )
	{
		super.izracunajPlatu( brojSati );
		this.setPlata( super.getPlata() + this.KOEFICIJENT_KANC_RADNIKA * brojSati );
	}

	@Override
	public String toString()
	{
		String output = this.getImeRadnika() + ":(" + this.getPlata() + ", nema bonus)";	
		System.out.println( output );
		
		return output;
	}

	@Override
	public void stampajPodatke()
	{
		super.stampajPodatke();
		System.out.println("Strani jezik: " + this.straniJezik );
	}

	@Override
	public void setPlata( double plata )
	{
		UKUPNA__ISPLATA += plata - super.getPlata();

		super.setPlata( plata );
	}

	public static double getUKUPNA__ISPLATA()
	{
		return UKUPNA__ISPLATA;
	}
}
