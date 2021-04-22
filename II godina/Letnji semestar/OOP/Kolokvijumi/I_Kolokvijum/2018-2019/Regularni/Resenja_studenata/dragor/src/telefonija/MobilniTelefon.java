package telefonija;

import telefonija.kartice.IPopust;
import telefonija.kartice.MobilnaKartica;

public class MobilniTelefon extends Telefon implements IPopust
{
	private MobilnaKartica[] kartice;
	
	public MobilniTelefon(String proizvodjac, int brKart)
	{
		super(proizvodjac);
		kartice = new MobilnaKartica[brKart];
	}
	
	public void dodajKarticu(MobilnaKartica kartica) throws Exception
	{
		for (int i = 0; i < kartice.length; i++)
		{
			if(kartice[i] == null) {
				kartice[i] = kartica;
				return;
			}
		}
		
		throw new Exception("Svi slotovi za kartice su popunjeni!");
	}
	
	public double izbaciKarticu(String broj) throws Exception
	{		
		for (int i = 0; i < kartice.length; i++)
		{
			if(kartice[i] != null && kartice[i].getBrojKartice() == broj) {
				double racun = kartice[i].dajRacun();
				kartice[i] = null;
				return racun;
			}
		}
		
		throw new Exception("Kartica ne postoji!");
	}
	
	public String dajBrojeveKartica()
	{
		String s = "";
		
		for (MobilnaKartica mobilnaKartica : kartice)
		{
			if(mobilnaKartica != null)
				s += "[" + mobilnaKartica.getBrojKartice() + "]";
		}
		
		return s;
	}

	@Override
	public double dajPopust()
	{
		double popust = 0;
		
		for (MobilnaKartica mobilnaKartica : kartice)
		{
			if(mobilnaKartica instanceof IPopust)
			{
				popust += ((IPopust)mobilnaKartica).dajPopust();
			}
		}
		
		return popust;
	}
	
	@Override
	public double dajRacun()
	{
		double racun = 0;
		
		for (MobilnaKartica mobilnaKartica : kartice)
		{
			if(mobilnaKartica != null)
				racun += mobilnaKartica.dajRacun();
		}
		
		return racun;
	}

	public void razgovor(String broj, int minuti)
	{
		for (int i = 0; i < kartice.length; i++)
		{
			if(kartice[i] != null && kartice[i].getBrojKartice() == broj)
			{
				kartice[i].dodajPotroseneMinute(minuti);
			}
		}
	}
	
	public void posaljiSMSove(String broj, int brSMS)
	{
		for (int i = 0; i < kartice.length; i++)
		{
			if(kartice[i] != null && kartice[i].getBrojKartice() == broj)
			{
				kartice[i].dodajPoslateSMSove(brSMS);
			}
		}
	}
	
}
