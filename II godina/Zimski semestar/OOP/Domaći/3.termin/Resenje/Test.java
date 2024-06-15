public class Test
{
	public static void main( String[] args )
	{
		final int brojSati = 30;

		KancelarijskiRadnik marko = new KancelarijskiRadnik( "Marko", "Nemacki" );
		Menadzer nikola = new Menadzer( "Nikola", false, false );
		marko.izracunajPlatu( 20 );
		nikola.izracunajPlatu( 15 );

		byte poredjenje = marko.uporediPlatu( nikola );

		if( poredjenje == 0 )
			System.out.println( marko.getImeRadnika() + " i " + nikola.getImeRadnika() +
					"imaju jednake plate" );
		else if( poredjenje == 1 )
			System.out.println( marko.getImeRadnika() + " ima vecu platu" );
		else
			System.out.println( nikola.getImeRadnika() + " ima vecu platu" );
	
		System.out.println();

		Zaposleni[] nizZaposlenih = new Zaposleni[4];

		nizZaposlenih[0] = new KancelarijskiRadnik( "Misa", "Francuski" );
		nizZaposlenih[1] = new Menadzer( "Sale", false, true );
		nizZaposlenih[2] = new KancelarijskiRadnik( "Mimi", "Engleski" );
		nizZaposlenih[3] = new Menadzer( "Miki", true, false );

		marko.izracunajPlatu( brojSati );
		nikola.izracunajPlatu( brojSati );

		for( Zaposleni z : nizZaposlenih )
			z.izracunajPlatu( brojSati );

		marko.stampajPodatke();
		System.out.println();
		
		nikola.stampajPodatke();
		System.out.println();
		
		for( Zaposleni z : nizZaposlenih )
		{
			z.stampajPodatke();
			System.out.println();
		}

		System.out.println("Svim zaposlenima je ukupno isplaceno: " + Zaposleni.getUKUPNA__ISPLATA() );
		System.out.println("Svim kancelarijskim radnicima je ukupno isplaceno: " + KancelarijskiRadnik.getUKUPNA__ISPLATA() );
		System.out.println("Svim menadzerima je ukupno isplaceno: " + Menadzer.getUKUPNA__ISPLATA() );
	}
}
