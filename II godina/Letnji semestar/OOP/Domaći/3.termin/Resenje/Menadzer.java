public class Menadzer extends Zaposleni
{
	private static double UKUPNA__ISPLATA;
	
	private static final short KOEFICIJENT_MENADZERA = 150;
	private static final short VREDNOST_BONUSA = 1000;
	private static final short VREDNOST_IZLAZKA_NA_TEREN = 500;

	private boolean teren;

	public Menadzer( String imeRadnika, boolean teren, boolean bonus )
	{
		super( imeRadnika, bonus );
		this.teren = teren;
	}

	@Override
	public void izracunajPlatu( int brojSati )
	{
		super.izracunajPlatu( brojSati );
		this.setPlata( super.getPlata() + this.KOEFICIJENT_MENADZERA * brojSati );

		if( super.getBonus() == true )
			this.setPlata( super.getPlata() + this.VREDNOST_BONUSA );

		if( this.teren == true )
			this.setPlata( super.getPlata() + this.VREDNOST_IZLAZKA_NA_TEREN );
	}

	@Override
	public String toString()
	{
		String output = super.getImeRadnika() + ":(" + super.getPlata() + ",";
		
		if( super.getBonus() == true )
			output += "DA)";
		else if( super.getBonus() == false )
			output += "NE)";

		System.out.println( output );

		return output;
	}

	@Override
	public void stampajPodatke()
	{
		super.stampajPodatke();

		String terenStr = "Ne";

		if( this.teren )
			terenStr = "Da";

		System.out.println("Teren: " + terenStr );
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
