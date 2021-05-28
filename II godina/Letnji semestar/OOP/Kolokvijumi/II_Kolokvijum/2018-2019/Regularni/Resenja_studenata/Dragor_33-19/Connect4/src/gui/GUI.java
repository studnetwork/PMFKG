package gui;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Label;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import logic.Ball;
import logic.Engine;
import logic.TurnResult;

public class GUI extends JFrame
{	
	// Engine
	Engine engine;
	
	// Window
	Container content;
	
	// Elements
	JPanel pnlInfo;
	JLabel lblR;
	JLabel lblY;
	JLabel lblNaPotezu;
	
	JPanel pnlGrid;
	Card[][] grid;
	
	JPanel pnlCtrl;
	JButton btnNewGame;
	
	public GUI(int h, int w)
	{
		engine = new Engine(h, w);
		grid = new Card[h][w];
		
		// Window Setup
		content = getContentPane();
		setBounds(1000, 250, 500, 500);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		// Panel Grid
		pnlGrid = new JPanel(new GridLayout(h, w));
		for (int i = 0; i < engine.getHeight(); i++) {
			for (int j = 0; j < engine.getWidth(); j++) 
			{
				Card btn = new Card();
				btn.r = i;
				btn.c = j;
				btn.setPreferredSize(new Dimension(101, 101));
				
				btn.addActionListener(new ActionListener()
				{	
					@Override
					public void actionPerformed(ActionEvent e) {
						Card me = (Card)e.getSource();
						TurnResult res = engine.placeBall(me.c);
						update(res);
					}
				});
				
				pnlGrid.add(btn);
				grid[i][j] = btn;
			}
		}
		
		// Info
		JPanel t;
		pnlInfo = new JPanel(new BorderLayout());
		lblR = new JLabel();
		lblY = new JLabel();
		lblNaPotezu = new JLabel();
		pnlInfo.add(t = new JPanel(), BorderLayout.WEST);
		t.add(lblR);
		pnlInfo.add(t = new JPanel(), BorderLayout.CENTER);
		t.add(new JLabel("Na potezu: "));
		t.add(lblNaPotezu);
		pnlInfo.add(t = new JPanel(), BorderLayout.EAST);
		t.add(lblY);
		
		// New Game Button
		pnlCtrl = new JPanel();
		btnNewGame = new JButton("Nova Igra");
		btnNewGame.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				init();
			}
		});
		pnlCtrl.add(btnNewGame);
		
		// Add Elements
		content.add(pnlInfo, BorderLayout.NORTH);
		content.add(pnlGrid, BorderLayout.CENTER);
		content.add(pnlCtrl, BorderLayout.SOUTH);
		
		// Window SHOW
		pack();
		setVisible(true);
		
		init();
	}
	
	private void init()
	{
		engine.init();
		update(TurnResult.NONE);
		
		/*for (int i = 0; i < engine.getHeight(); i++) {
			for (int j = 0; j < engine.getWidth(); j++) {
				grid[i][j].setIcon(new ImageIcon("img/prazno_polje.png"));
			}
		}*/
	}
	
	private void update(TurnResult turnResult)
	{
		// Grid
		for (int i = 0; i < engine.getHeight(); i++) {
			for (int j = 0; j < engine.getWidth(); j++) 
			{
				if(engine.readTable(i, j) == Ball.RED) {
					//System.out.println("RED");
					grid[i][j].setIcon(new ImageIcon("img/crveno_polje.png"));
					
				}
				else if(engine.readTable(i, j) == Ball.YELLOW) {
					//System.out.println("YELLOW");
					grid[i][j].setIcon(new ImageIcon("img/zuto_polje.png"));
				}
				else {
					//System.out.println("EMPTY");
					grid[i][j].setIcon(new ImageIcon("img/prazno_polje.png"));
				}
			}
		}
		
		// Info
		lblR.setText("Broj poteza crvenog: " + engine.getRedTurns());
		lblY.setText("Broj poteza zutog: " + engine.getYelTurns());
		
		if(engine.getOnTurn() == Ball.RED)
			lblNaPotezu.setIcon(new ImageIcon("img/red_small.png")); // Info
		else
			lblNaPotezu.setIcon(new ImageIcon("img/yellow_small.png")); // Info
		
		// Check Game State (WIN)
		if(turnResult == TurnResult.WIN)
		{
			System.out.println("WIN" + engine.getOnTurn());
			String message = "Pobednik je " + ((engine.getOnTurn() == Ball.RED)? "Crveni" : "Zuti") + "\n";
			message += "Novu igru zelite li Vi?";
			String title = "Na zalost, kraj je igre ...";
			if(JOptionPane.YES_OPTION == JOptionPane.showConfirmDialog(null, message, title, JOptionPane.YES_NO_OPTION)) {
				init();
			}
			else {
				System.exit(0);
			}
		}
		
		// za svaki slucaj
		revalidate();
		repaint();
	}

}
