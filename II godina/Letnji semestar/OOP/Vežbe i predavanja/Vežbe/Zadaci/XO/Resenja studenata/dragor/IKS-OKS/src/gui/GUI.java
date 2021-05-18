package gui;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class GUI extends JFrame
{
	private JLabel lblStatus;
	private JButton btnReset;
	
	private JPanel pnlGrid = new JPanel(new GridLayout(3,3,1,1));
	private JButton[][] btnFields;
	private int N; 
	
	public GUI(int boardSize, ActionListener lsnField, ActionListener lsnReset)
	{	
		N = boardSize;
		
		// Window setup
		setBounds(300, 300, 500, 500); // x, y, width, height
		setTitle("XO Igra"); // naslov prozora
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		// Elements defined
		lblStatus = new JLabel("");
		btnReset = new JButton("Resetuj igru");
		btnReset.addActionListener(lsnReset);
		//pnlGrid = new JPanel(new GridLayout(N,N,1,1));
		btnFields = new JButton[N][N];
		
		for(int j = N-1; j >= 0; j--) {
			for(int i = 0; i < N; i++) 
			{
				btnFields[i][j] = new FieldButton(i, j);
				btnFields[i][j].setPreferredSize(new Dimension(100,100));
				btnFields[i][j].setText("");
				
				btnFields[i][j].addActionListener(lsnField);
				
				pnlGrid.add(btnFields[i][j]);
			}
		}
		
		// Elements setup
		getContentPane().add(lblStatus, BorderLayout.NORTH);
		getContentPane().add(pnlGrid, BorderLayout.CENTER);
		getContentPane().add(btnReset, BorderLayout.SOUTH);
		
		// Final setup
		pack(); // Cemu ovo slzi ... ? A uz to i ne radi ...
		setVisible(true);
	}
	
	public void clearButtons()
	{
		for(int j = N-1; j >= 0; j--) {
			for(int i = 0; i < N; i++) {
				btnFields[i][j].setText("");
				btnFields[i][j].setEnabled(true);
				btnFields[i][j].setIcon(null);
			}
		}
	}
	
	public void setLabelStatus(String text)
	{
		lblStatus.setText(text);
	}
	
	public boolean isYesOnDialog(String message, String title)
	{
		return (JOptionPane.showConfirmDialog(null, message, title, JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION)? true : false;
	}
}






