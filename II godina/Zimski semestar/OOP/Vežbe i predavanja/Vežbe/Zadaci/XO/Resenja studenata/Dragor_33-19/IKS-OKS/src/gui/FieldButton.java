package gui;

import javax.swing.ImageIcon;
import javax.swing.JButton;

public class FieldButton extends JButton implements ReadWriteString, HasGridPosition, HasIcon, CanBeDissabled
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
	
	@Override
	public void setIcon(ImageIcon icon) {
		super.setIcon(icon);
	}
	
	@Override
	public void dissable() {
		setEnabled(false);
		
	}
}
