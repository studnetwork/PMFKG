import logic.*;
import gui.*;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;


public class GameXO
{
	static XO game;
	static GUI gui;
	
	public static void main(String[] args)
	{
		game = new XO();
		
		// Reaction on Field button click
		ActionListener lsnField = new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent event) {
				int x = ((HasGridPosition)event.getSource()).getPosX();
				int y = ((HasGridPosition)event.getSource()).getPosY();
				
				GameState state;
				try {
					state = game.play(x, y);
				}
				catch (Exception e) {
					System.out.println("Neuspesno odigran potez!"); // DEBUG
					System.out.println(e.getMessage()); // DEBUG
					return;
				}
				
				String sign = (game.getLastTurn() == Field.X)? "X" : ((game.getLastTurn() == Field.O)? "O" : "");
				//((ReadWriteString)event.getSource()).write(sign);
				((HasIcon)event.getSource()).setIcon(new ImageIcon("./img/"+sign+".png"));
				((CanBeDissabled)event.getSource()).dissable();
				
				System.out.println(sign + " PLAYED!"); // DEBUG
				
				handleState(state);
			}
		};
		
		// Reaction on Reset button click
		ActionListener lsnReset = new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent event) {
				handleState(game.newGame());
				gui.clearButtons();
				System.out.println("RESET!"); // DEBUG
			}
		};
		
		gui = new GUI(3, lsnField, lsnReset);
		
		handleState(game.newGame());
	}
	
	public static void handleState(GameState state)
	{
		String label = "Nereseno";
		
		if(state == GameState.IN_PROGRESS) {
			label = (game.getOnTurn() == Field.X)? "X je na potezu" : "O je na potezu";
			gui.setLabelStatus(label);
			return;
		}
		
		if(state == GameState.X_WIN)
			label = "Pobednik je X";
		else if(state == GameState.O_WIN)
			label = "Pobednik je O";
		
		boolean toQuitGame = !gui.isYesOnDialog(label+"\nDa li zelite novu igru?", "Kraj igre");
		
		if(toQuitGame)
			System.exit(0);
		
		handleState(game.newGame());
		gui.clearButtons();
		System.out.println("RESET!"); // DEBUG
	}
}
