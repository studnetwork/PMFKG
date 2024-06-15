package engine;

public class Polje {
	private int i;
	private int j;
	private int vrednost;
	private SadrzajPolja sadrzajPolja;
	
	public Polje(int i, int j, int vrednost) {
		this.i = i;
		this.j = j;
		this.vrednost = vrednost;
	}
	
	public Polje(int i, int j, int vrednost, SadrzajPolja sadrzajPolja) {
		this(i,j,vrednost);
		this.sadrzajPolja = sadrzajPolja;
	}

	public int getI() {
		return i;
	}

	public int getJ() {
		return j;
	}

	public int getVrednost() {
		return vrednost;
	}

	public void setVrednost(int vrednost) {
		this.vrednost = vrednost;
	}

	public SadrzajPolja getSadrzajPolja() {
		return sadrzajPolja;
	}

	public void setSadrzajPolja(SadrzajPolja sadrzajPolja) {
		this.sadrzajPolja = sadrzajPolja;
	}
	
}
