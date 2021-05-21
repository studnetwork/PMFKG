package logika;

public class XO {
	
	private STATUS_IGRE status;
	
	/*
	 *  1 = x
	 * -1 = o
	 *  0 = prazno
	 * */
	private int[][] polja;
	private int naPotezu;
	private int brojOdigranih;
	private int dim;
	
	public XO() {
		this.dim = 3;
		init();
	}
	
	public XO(int dim) {
		this.dim = dim;
		init();
	}
	
	public void init() {
		polja = new int[dim][dim];
		status = STATUS_IGRE.U_TOKU;
		naPotezu = 1;
		brojOdigranih = 0;
		
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				polja[i][j] = 0;
			}
		}
	}
	
	public STATUS_IGRE odigrajPotez(int i, int j) {
		if( polja[i][j] == 0 ) {
			polja[i][j] = naPotezu;
			naPotezu *= -1;
			brojOdigranih++;
			
			status = proveriStanje();
		}
		
		return status;
	}
	
	private STATUS_IGRE proveriStanje() {
		int sumaVertikalno,
			sumaHorizontalno,
			sumaPoGlavnoj,
			sumaPoSporednoj;
		
		sumaPoGlavnoj = sumaPoSporednoj = 0;
		
		for (int i = 0; i < dim; i++) {
			sumaHorizontalno = sumaVertikalno = 0;
			
			sumaPoGlavnoj += polja[i][i];
			sumaPoSporednoj += polja[dim-1-i][i];
			for (int j = 0; j < dim; j++) {
				sumaHorizontalno += polja[i][j];
				sumaVertikalno += polja[j][i];
			}
			
			if( sumaHorizontalno == dim || sumaVertikalno == dim )
				return STATUS_IGRE.POBEDIO_X;
			
			if( sumaHorizontalno == -dim || sumaVertikalno == -dim )
				return STATUS_IGRE.POBEDIO_Y;
		}
		
		if( sumaPoGlavnoj == dim || sumaPoSporednoj == dim )
			return STATUS_IGRE.POBEDIO_X;
		
		if( sumaPoGlavnoj == -dim || sumaPoSporednoj == -dim )
			return STATUS_IGRE.POBEDIO_Y;
		
		if( brojOdigranih == dim*dim )
			return STATUS_IGRE.NERESENO;
		
		return STATUS_IGRE.U_TOKU;
	}
	
	public String getOznaka(int i, int j) {
		if( polja[i][j] == 0 )
			return "";
		else if( polja[i][j] == 1 )
			return "X";
		else
			return "O";
	}
	
	public String getIgracNaPotezu() {
		if( naPotezu == 1 )
			return "X";
		else
			return "O";
	}
	
	public int getDim() {
		return dim;
	}
}
