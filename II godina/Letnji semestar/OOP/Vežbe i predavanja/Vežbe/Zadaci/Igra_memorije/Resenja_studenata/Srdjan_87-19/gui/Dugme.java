package gui;

import javax.swing.JButton;

public class Dugme extends JButton {
	private int i;
	private int j;
	
	public Dugme(int i, int j) {
		super();
		this.i = i;
		this.j = j;
	}

	public int getI() {
		return i;
	}

	public int getJ() {
		return j;
	}
	
}
