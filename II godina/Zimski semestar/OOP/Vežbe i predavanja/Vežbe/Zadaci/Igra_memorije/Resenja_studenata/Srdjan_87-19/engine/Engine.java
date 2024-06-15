package engine;

import java.sql.Time;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class Engine {
	private int brojJedinstvenih;
	private Polje[][] polja;
	private int skor;
	private int visina;
	private int sirina;
	private int brojPoteza; // 0, 1 ili 2
	private Polje prvoPolje;
	
	public Engine(int brojJedinstvenih, int visina, int sirina ) {
		this.brojJedinstvenih = brojJedinstvenih;
		this.visina = visina;
		this.sirina = sirina;
		
		init();
	}
	
	public void init() {
		int listLen = visina*sirina;
		List<Polje>slobodnaPolja = new ArrayList<Polje>(listLen);
		Polje tempPolje;
		
		skor = 0;
		brojPoteza = 0;
		prvoPolje = null;
		polja = new Polje[visina][sirina];

		for (int i = 0; i < visina; i++) {
			for (int j = 0; j < sirina; j++) {
				polja[i][j] = new Polje(i, j, -1, SadrzajPolja.NEVIDLJIV);
				slobodnaPolja.add(polja[i][j]);
			}
		}

		/* po 2 random polja ce dobiti istu vrednost */
		Random r = new Random();
		for (int i = 0; slobodnaPolja.size() > 0; i++) {
			tempPolje = slobodnaPolja.remove( r.nextInt(slobodnaPolja.size()) );
			tempPolje.setVrednost(i/2);
		}
	}
	
	public IshodPoteza odigrajPotez(int i, int j ) {
		if( polja[i][j].getSadrzajPolja() == SadrzajPolja.NEVIDLJIV ) {
			
			brojPoteza++;

			// prikazi sadrzaj polja
			polja[i][j].setSadrzajPolja(SadrzajPolja.VIDLJIV);
			
			if( brojPoteza == 1 ) {
				prvoPolje = polja[i][j];
			} 
			
			return IshodPoteza.ODIGRAN_POTEZ;
			
		}
		
		return IshodPoteza.NEMOGUC_POTEZ;
	}
	
	public IshodPoteza proveriIshod(int i, int j) {
		if( brojPoteza == 2 ) {
			
			brojPoteza = 0;
			
			// proverava da li polja imaju isti sadrzaj
			if( prvoPolje.getVrednost() == polja[i][j].getVrednost() ) {
				skor++;

				if( skor == brojJedinstvenih ) {
					return IshodPoteza.KRAJ;
				}
				else {
					return IshodPoteza.POKLAPANJE;
				}
			}
			else {
				// sakrij polja jer nemaju isti sadrzaj
				prvoPolje.setSadrzajPolja(SadrzajPolja.NEVIDLJIV);
				polja[i][j].setSadrzajPolja(SadrzajPolja.NEVIDLJIV);
				
				return IshodPoteza.NEPOKLAPANJE;
			}
		}
		
		return IshodPoteza.CEKAJ_DRUGI_POTEZ;
	}

	public int getSkor() {
		return skor;
	}
	
	public int getVrednostPolja(int i, int j) {
		return polja[i][j].getVrednost();
	}
	
	public SadrzajPolja getSadrzaljPolja( int i, int j ) {
		return polja[i][j].getSadrzajPolja();
	}
}
