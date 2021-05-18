package gui;

import javax.swing.JButton;

public class FieldButton extends JButton implements ReadWriteString, HasGridPosition
{
	private int posX;
	private int posY;
	
	public FieldButton(int x, int y)
	{
		posX = x;
		posY = y;
	}
	
	@Override
	public int getPosX() {
		return posX;
	}
	
	@Override
	public int getPosY() {
		return posY;
	}
	
	@Override
	public String read() {
		return getText();
	}

	@Override
	public void write(String text) {
		setText(text);
	}
}
