package telefonija.kartice;

public class MobilnaKartica
{
	protected String brojKartice;
	private int potroseniMinuti = 0;
	private int brojPoslatihSMS = 0;
	
	/* -- Constructors -- */
	
	public MobilnaKartica(String broj)
	{
		brojKartice = broj;
	}
	
	/* -- Methods -- */
	
	public void dodajPotroseneMinute(int minuti)
	{
		if(minuti <= 0) return; // <- Nije zahtevano u zadatku
		potroseniMinuti += minuti;
	}
	
	public void dodajPoslateSMSove(int sms)
	{
		if(sms <= 0) return; // <- Nije zahtevano u zadatku
		brojPoslatihSMS += sms;
	}
	
	public double dajRacun()
	{
		double racun = 0;
		racun += potroseniMinuti*Cenovnik.getCenaMinutaMobilneTelefonije();
		racun += brojPoslatihSMS*Cenovnik.getCenaSMS();
		return racun;
	}
	
	/* Pure Getters & Setters */
	
	public String getBrojKartice() {
		return brojKartice;
	}
	
	public int getPotroseniMinuti(){
		return brojPoslatihSMS;
	}
	
}
