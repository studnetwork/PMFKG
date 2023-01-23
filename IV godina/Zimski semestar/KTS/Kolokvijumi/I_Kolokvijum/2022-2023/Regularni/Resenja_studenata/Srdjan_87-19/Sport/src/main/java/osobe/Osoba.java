package osobe;

import common.MerljivUcinak;
import izuzeci.Neuporedivo;

public class Osoba
{
	private String ime;
	
	public Osoba(String ime)
	{
		this.ime = ime;
	}
	
	public int uporedi(Object osoba) throws Neuporedivo 
	{
		if(!(this instanceof MerljivUcinak) || !(osoba instanceof MerljivUcinak))
		{
			throw new Neuporedivo("");
		}
		
		int index1 = ((MerljivUcinak)(this)).indeksKorisnosti();
		int index2 = ((MerljivUcinak)(osoba)).indeksKorisnosti();
		
		if(index1 > index2)
			return 1;
		else if(index1 < index2)
			return -1;
		else 
			return 0;

	}
	
	public String getIme()
	{
		return ime;
	}

	public String toString()
	{
		return super.getClass().getName() + " " + ime;
	}
}
