package gui;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.HeadlessException;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Iterator;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.Timer;

import engine.Engine;
import engine.IshodPoteza;
import engine.SadrzajPolja;

public class GUI extends JFrame {
	private Engine engine;
	private int visina;
	private int sirina;
	private int brojJedinstvenih;
	private int buttonHeight;
	private int buttonWidth;
	private boolean stopTimer;

	private Container guiContentPane;
	private JPanel gridPanel;
	private JButton novaIgraButton;
	private JButton[][] dugmici;
	private JLabel skorLabel;
	private JButton prethodnoPritusnutButton;

	
	public GUI(int brojJedinstvenih, final int sirina, final int visina) {
		super("Igra memorije");
		this.visina = visina;
		this.sirina = sirina;
		this.brojJedinstvenih = brojJedinstvenih;
		
		buttonHeight = 64;
		buttonWidth = 64;
		
		stopTimer = false;
		final Timer t = new Timer(900, new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				Timer t = (Timer) e.getSource();
				t.stop(); 
				t.restart();
				osveziGrafiku();
			}
		} );
		
		prethodnoPritusnutButton = null;
		
		engine = new Engine(brojJedinstvenih, visina, sirina);
		
		guiContentPane = getContentPane();
		
		gridPanel = new JPanel(new GridLayout(visina, sirina, 2, 2));
		
		JButton tempButton;
		
		dugmici = new Dugme[visina][sirina];
		
		for (int i = 0; i < visina; i++) {
			for (int j = 0; j < sirina; j++) {
				tempButton = new Dugme(i, j);
				
				tempButton.setPreferredSize(new Dimension(buttonHeight,buttonWidth));
				tempButton.addActionListener(new ActionListener() {
					
					@Override
					public void actionPerformed(ActionEvent e) {
						Dugme d = (Dugme) e.getSource();
						
						IshodPoteza ishodPoteza = engine.odigrajPotez(d.getI(), d.getJ());
						
						if( ishodPoteza == IshodPoteza.ODIGRAN_POTEZ ) {
							osveziGrafiku();
							proveriIshod(ishodPoteza, d, t);
						}
						else {
							System.out.println("GUI:\n\ttempButton.actionPerformed:" 
												+ "Nemoguc potez (" + d.getI() + ", " + d.getJ() + ")" );
						}
						
					} // KRAJ actionPerformed
				});
				gridPanel.add(tempButton);
				dugmici[i][j] = tempButton;
			} // KRAJ forJ
		} // KRAJ forI
		
		novaIgraButton = new JButton("Nova igra");
		novaIgraButton.addActionListener( new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				engine.init();
				osveziGrafiku();
			}
		});
		
		skorLabel = new JLabel();
		
		guiContentPane.add(skorLabel, BorderLayout.NORTH);
		guiContentPane.add(gridPanel, BorderLayout.CENTER);
		guiContentPane.add(novaIgraButton, BorderLayout.SOUTH);
		
		pack();
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
		osveziGrafiku();
	}
	
	public void osveziGrafiku() {
		skorLabel.setText("Trenutni skor: " + engine.getSkor() );
		Dugme tempDugme;
		
		for (int i = 0; i < visina; i++) {
			for (int j = 0; j < sirina; j++) {
				
				if( engine.getSadrzaljPolja(i, j) == SadrzajPolja.NEVIDLJIV ) {
					dugmici[i][j].setText("");
					dugmici[i][j].setEnabled(true);
				}
				else {
					dugmici[i][j].setText(""+engine.getVrednostPolja(i, j));
					dugmici[i][j].setEnabled(false);
				}
			}
		}
	}
	
	private void proveriIshod(IshodPoteza ishodPoteza, Dugme d, Timer t) {
		ishodPoteza = engine.proveriIshod(d.getI(), d.getJ());
		
		if( ishodPoteza == IshodPoteza.POKLAPANJE ) {
			osveziGrafiku();
		}
		else if( ishodPoteza == IshodPoteza.NEPOKLAPANJE ) {
	        t.start();
		}
		else if( ishodPoteza == IshodPoteza.KRAJ ){
			osveziGrafiku();
			
			String poruka = "Igra je zavrsena. Da li zelite da pokrenete novu igru?";
			
			int resp = JOptionPane.showConfirmDialog(null, poruka, "Kraj igre",  JOptionPane.YES_NO_OPTION );
			
			if( resp == JOptionPane.YES_OPTION ) {
				engine.init();
				osveziGrafiku();
			}
			else {
				System.exit(0);
			}
		}
	}
}
