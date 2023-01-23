package turnir;



public class Statistika 
{
	private TIP_STATISTIKE tipStatistike;
	private int brojNaDresu;
	private String nazivKluba;
	private int ostvareniUcinak;
	
	public Statistika(TIP_STATISTIKE tipStatistike, int brojNaDresu, String nazivKluba, int ostvareniUcinak)
	{
		this.tipStatistike = tipStatistike;
		this.brojNaDresu = brojNaDresu;
		this.nazivKluba = nazivKluba;
		this.ostvareniUcinak = ostvareniUcinak;
	}
	
	public TIP_STATISTIKE getTipStatistike() {
		return tipStatistike;
	}

	public int getBrojNaDresu() {
		return brojNaDresu;
	}

	public String getNazivKluba() {
		return nazivKluba;
	}

	public int getOstvareniUcinak() {
		return ostvareniUcinak;
	}
}
