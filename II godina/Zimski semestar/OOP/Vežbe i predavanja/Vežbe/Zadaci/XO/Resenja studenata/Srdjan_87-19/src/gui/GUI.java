package gui;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import logika.*;

public class GUI extends JFrame {
	private int prefSize;
	private int dim;
	private int buttonGap;
	
	private XO xo;
	
	private JLabel statusLbl;
	private JButton novaIgraDugme;
	private JButton[][] dugmici;
	private JPanel centralniPanel;
	private Container contPane;
	
	public GUI() {
		dim = 3;
		prefSize = 70;
		buttonGap = 1;
		
		statusLbl = new JLabel();
		novaIgraDugme = new JButton("Nova igra");
		novaIgraDugme.addActionListener( new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ae) {
				xo.init();
				osveziPrikaz();
			}
		});
		
		contPane = getContentPane();
		
		contPane.add(statusLbl, BorderLayout.NORTH);
		contPane.add(novaIgraDugme, BorderLayout.SOUTH);
		
		setTitle("XO Igra");
		setBounds(500, 500, 380, 380);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public GUI(int dim) {
		this();
		
		this.dim = dim;
		
		xo = new XO(dim);
		
		dugmici = new JButton[dim][dim];
		
		centralniPanel = new JPanel( new GridLayout(dim, dim, buttonGap, buttonGap));
		
		JButton tempButton;
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				tempButton = new Dugme(i,j);
				tempButton.setPreferredSize( new Dimension(prefSize, prefSize) );
				tempButton.addActionListener( new ActionListener() {
					
					@Override
					public void actionPerformed(ActionEvent ae) {
						
						Dugme d = (Dugme)ae.getSource();
						STATUS_IGRE trenStatus = xo.odigrajPotez(d.getCoorX(), d.getCoorY());
						
						if( trenStatus != STATUS_IGRE.U_TOKU ) {
							String poruka = "Pobedio je ";
							
							if( trenStatus == STATUS_IGRE.POBEDIO_X )
								poruka += "X";
							else if( trenStatus == STATUS_IGRE.POBEDIO_Y )
								poruka += "O";
							else
								poruka = "Nereseno je";
							
							poruka += ". Da li zelite da zapocnete novu igru?";

							osveziPrikaz();
							int status = JOptionPane.showConfirmDialog(null, poruka, "Kraj igre", JOptionPane.YES_NO_OPTION );
							
							if( status == JOptionPane.YES_OPTION )
								xo.init();
							else
								System.exit(0);
						}
						
						osveziPrikaz();
					}
				});
				
				dugmici[i][j] = tempButton;
				centralniPanel.add(tempButton);
			}
		}
		
		contPane.add(centralniPanel, BorderLayout.CENTER);

		osveziPrikaz();
		setVisible(true);
	}
	
	private void osveziPrikaz() {
		statusLbl.setText("Na potezu je: " + xo.getIgracNaPotezu());
		
		String oznaka;
		for (int i = 0; i < dim; i++) {
			for (int j = 0; j < dim; j++) {
				oznaka = xo.getOznaka(i, j);
				if(oznaka == "")
					dugmici[i][j].setEnabled(true);
				else 
					dugmici[i][j].setEnabled(false);
					
				dugmici[i][j].setText(oznaka);
			}
		}
	}

	public int getPrefSize() {
		return prefSize;
	}

	public void setPrefSize(int prefSize) {
		this.prefSize = prefSize;
	}

	public int getDim() {
		return dim;
	}

	public void setDim(int dim) {
		this.dim = dim;
	}

	public int getButtonGap() {
		return buttonGap;
	}

	public void setButtonGap(int buttonGap) {
		this.buttonGap = buttonGap;
	}

	public XO getXo() {
		return xo;
	}

	public void setXo(XO xo) {
		this.xo = xo;
	}

	public JButton[][] getDugmici() {
		return dugmici;
	}

	public void setDugmici(JButton[][] dugmici) {
		this.dugmici = dugmici;
	}

	public JPanel getCentralniPanel() {
		return centralniPanel;
	}

	public void setCentralniPanel(JPanel centralniPanel) {
		this.centralniPanel = centralniPanel;
	}

	public Container getContPane() {
		return this.contPane;
	}

	public void setContPane(Container contentPane) {
		this.contPane = contentPane;
	}
	
}
