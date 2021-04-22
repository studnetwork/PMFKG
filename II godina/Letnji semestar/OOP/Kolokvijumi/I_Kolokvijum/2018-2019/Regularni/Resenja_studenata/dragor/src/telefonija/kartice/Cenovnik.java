package telefonija.kartice;

public class Cenovnik
{
	private static double cenaMinutaFiksneTelefonije = 7;
	private static double cenaMinutaMobilneTelefonije = 10;
	private static double cenaSMS = 5;
	
	public static double getCenaMinutaFiksneTelefonije() {
		return cenaMinutaFiksneTelefonije;
	}

	public static double getCenaMinutaMobilneTelefonije() {
		return cenaMinutaMobilneTelefonije;
	}

	public static double getCenaSMS() {
		return cenaSMS;
	}	
}
