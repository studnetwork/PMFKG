package gui;

import javax.swing.Action;
import javax.swing.Icon;
import javax.swing.JButton;

public class Card extends JButton 
{
	private int i;
	private int j;
	
	public Card(int i, int j) 
	{
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
