package gui;

import javax.swing.JButton;

public class Dugme extends JButton {
	private int coorX;
	private int coorY;

	public Dugme(int coorX, int coorY) {
		super();
		this.coorX = coorX;
		this.coorY = coorY;
	}

	public int getCoorX() {
		return coorX;
	}

	public int getCoorY() {
		return coorY;
	}
	
	
}
