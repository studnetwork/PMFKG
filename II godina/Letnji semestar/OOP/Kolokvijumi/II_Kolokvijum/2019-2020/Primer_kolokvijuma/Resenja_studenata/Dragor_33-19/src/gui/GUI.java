package gui;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

import logic.*;

public class GUI extends JFrame
{
	// Game Logic
	int height;
	int width;
	Game game;
	
	// UI
	Container content;
	JPanel grid;
	JPanel status;
	JLabel lblAtt;
	JLabel lblHit;
	
	// UI Data
	Card table[][];
	String strAtt = "Broj pokusaja: ";
	String strHit = "Broj pogodjenih: ";
	
	// Helpers
	Timer checkTick;
	boolean canClick;
	
	public GUI(int h, int w)
	{
		// Game Logic Setup
		height = h;
		width = w;
		game = new Game(h, w);
		
		canClick = true;
		checkTick = new Timer(1000, new ActionListener() 
		{	
			@Override
			public void actionPerformed(ActionEvent e) {
				updateTable();
				((Timer)e.getSource()).stop();
			}
		});

		// GUI Elements Setup
		content = getContentPane();
		
		lblAtt = new JLabel(strAtt + 0);
		lblHit = new JLabel(strHit + 0);
		
		// Grid
		table = new Card[h][w];
		grid = new JPanel(new GridLayout(h, w));
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				Card nl = new Card(i, j);
				nl.setPreferredSize(new Dimension(120,120));
				nl.addActionListener(new ActionListener()
				{	
					@Override
					public void actionPerformed(ActionEvent e)
					{	
						if(!canClick)
							return;
						
						Card c = (Card)e.getSource();
						int i = c.getI();
						int j = c.getJ();
						
						if(game.getTable()[i][j].isOpened())
							return;
						
						boolean isLast = game.openField(i, j);
						if(game.getTable()[i][j].isOpened()) {
							c.setIcon(getFieldIcon(i, j));
						}
						
						if(isLast) {
							System.out.println("Timer Start");
							canClick = false;
							checkTick.start();
						}
					}
				});
				table[i][j] = nl;
				grid.add(nl);
			}
		}
		
		// Status
		status = new JPanel(new GridLayout(1, 2));
		status.add(lblAtt);
		status.add(lblHit);
		
		// Reset button
		JButton btnNewGame = new JButton("Nova igra");
		btnNewGame.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				init();
			}
		});
		btnNewGame.setSize(100, 50);
		JPanel pnlNewGame = new JPanel();
		pnlNewGame.add(btnNewGame);
		
		
		// JFrame Setup
		setBounds(1100, 250, 600, 600);
		setTitle("Igra memorije");
		
		content.add(status, BorderLayout.NORTH);
		content.add(grid, BorderLayout.CENTER);
		content.add(pnlNewGame, BorderLayout.SOUTH);
		
		pack();
		setVisible(true);
	}
	
	private void updateTable()
	{
		game.hitCheck();
		
		boolean isOver = true;
		
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if(game.getTable()[i][j].isOpened()) {
					table[i][j].setIcon(getFieldIcon(i, j));
					table[i][j].setEnabled(false);
				}
				else {
					isOver = false;
					table[i][j].setIcon(null);
					table[i][j].setEnabled(true);
				}
			}
		}
		
		lblAtt.setText(strAtt + game.getAttempts());
		lblHit.setText(strHit + game.getHits());
		
		canClick = true;
		
		if(isOver) {
			String mes = "Uspeli ste da resite igru iz " + game.getAttempts() + " pokusaja. Da li ste za novu igru?";
			if(JOptionPane.showConfirmDialog(null, mes, "Kraj igre", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)
				init();
			else
				System.exit(0);
		}
	}
	
	private void init()
	{
		game.init();
		updateTable();
	}
	
	private ImageIcon getFieldIcon(int i, int j)
	{
		return new ImageIcon("img/" + game.getTable()[i][j].getId() + ".png");
	}
}
