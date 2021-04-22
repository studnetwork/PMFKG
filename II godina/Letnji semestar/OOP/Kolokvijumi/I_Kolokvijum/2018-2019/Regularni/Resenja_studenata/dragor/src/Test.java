import telefonija.*;
import telefonija.kartice.*;

public class Test
{
	public static void main(String[] args)
	{
		Telefon telefoni[] = new Telefon[3];

		FiksniTelefon ft1 = new FiksniTelefon("Samsung", "034235874");
		ft1.razgovor(120);
		telefoni[0] = ft1;

		MobilniTelefon mt = new MobilniTelefon("Huawei", 2);
		telefoni[1] = mt;

		MTSKartica mtsKartica1 = new MTSKartica("064111111", 10);
		VIPKartica vipKartica = new VIPKartica("060222222");
		MTSKartica mtsKartica2 = new MTSKartica("065123456", 10);

		try {
			mt.dodajKarticu(mtsKartica1);
			mt.dodajKarticu(vipKartica);
			mt.dodajKarticu(mtsKartica2);
		} 
		catch (Exception exc) {
			System.out.println(exc.getMessage());
		}

		mt.razgovor("064111111", 12);
		mt.razgovor("060222222", 15);
		mt.posaljiSMSove("060222222", 4);


		FiksniTelefon ft2 = new FiksniTelefon("LG", "034235874");
		ft2.razgovor(100);
		telefoni[2] = ft2;

		ispisiUkupniRacun(telefoni);
		spisakPotrosnje(telefoni);
		ispisiUkupniPopust(telefoni);


		try {
			System.out.println("Potrosnja izbacene kartice: " + mt.izbaciKarticu("060222222"));
		}
		catch (Exception exc) {
			System.out.println(exc.getMessage());
		} 
		
		ispisiUkupniRacun(telefoni);
		spisakPotrosnje(telefoni);
		ispisiUkupniPopust(telefoni);
	}
	
	public static void ispisiUkupniPopust(Telefon[] telefoni)
	{
		double popust = 0;
		
		for (Telefon tel : telefoni) {
			if(tel != null && tel instanceof IPopust) {
				popust += ((IPopust)tel).dajPopust();
			}
		}
		
		System.out.println(popust);
	}

	private static void spisakPotrosnje(Telefon[] telefoni)
	{
		for (Telefon tel : telefoni) {
			if(tel != null)
				System.out.println(tel);
		}
		
	}
	
	private static void ispisiUkupniRacun(Telefon[] telefoni)
	{
		double racun = 0;
		
		for (Telefon tel : telefoni) {
			if(tel != null) {
				racun += tel.dajRacun();
			}
		}
		
		System.out.println(racun);
	}
	
}
