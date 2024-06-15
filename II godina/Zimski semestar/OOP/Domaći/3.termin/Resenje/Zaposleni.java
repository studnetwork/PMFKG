public class Zaposleni
{	
	private static double UKUPNA__ISPLATA;
	
	private static final short OSNOVNI_KOEFICIJENT = 200;
	
	public double plata;

	private String imeRadnika;
	private boolean bonus;

	public Zaposleni( String imeRadnika, boolean bonus )
	{
		this.imeRadnika = imeRadnika;
		this.bonus = bonus;
	}

	public void izracunajPlatu( int brojSati )
	{
		this.setPlata( brojSati * this.OSNOVNI_KOEFICIJENT );	
	}

	/* 
	 * Metod uporediPlatu uporedjuje platu zaposlenog koji je
	 * pozvao ovu metodu sa platom zaposlenog cija je referenca
	 * prosledjena kao argument
	 *
	 * Return: Vraca vrednost tipa byte:
	 *	 0 - ako su im plate jednake
	 *	 1 - ako zaposleni koji je pozvao metod ima vecu platu od drugog zaposlenog
	 *	-1 - ako zaposleni koji je pozvao metod ima manju platu od drugog zaposlenog
	 */

	public byte uporediPlatu( Zaposleni drugiZaposleni )
	{
		double plata = this.getPlata();
		double plataDrugorZaposlenog = drugiZaposleni.getPlata();

		if( plata == plataDrugorZaposlenog )
			return 0;
		else if( plata > plataDrugorZaposlenog )
			return 1;
		else
			return -1;
	}

	public void stampajPodatke()
	{
		System.out.println("Podaci zaposlenog:");
		System.out.println("Ime: " + this.getImeRadnika() );
		System.out.println("Plata: " + this.getPlata() );
		
		String bonusStr = "Nema";
		if( this.getBonus() )
			bonusStr = "Ima";

		System.out.println("Bonus: " + bonusStr );
	}

	@Override
	public String toString()
	{
		String output = this.getImeRadnika() + ":" + super.toString();
		System.out.println( output );
		
		return output;	
	}

	/*	
		dodati su getter i setter za promeljivu plata zato sto
		je trazeno da se naprave za sve promenljive, ali u ovom
		slucaju nisu neophodni jer promenljiva plata ima modifier
		public
	*/

	public double getPlata()
	{
		return this.plata;
	}

	public void setPlata( double plata )
	{
		UKUPNA__ISPLATA += plata - this.getPlata();
		this.plata = plata;
	}

	public String getImeRadnika()
	{
		return this.imeRadnika;
	}

	public void setImeRadnika( String imeRadnika )
	{
		this.imeRadnika = imeRadnika;
	}

	public boolean getBonus()
	{
		return this.bonus;
	}
	
	public void setBonus( boolean bonus )
	{
		this.bonus = bonus;
	}

	public static double getUKUPNA__ISPLATA()
	{
		return UKUPNA__ISPLATA;
	}
}
