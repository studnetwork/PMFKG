package gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.GraphicsConfiguration;
import java.awt.GridLayout;
import java.awt.HeadlessException;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.ImageObserver;
import java.awt.image.ImageProducer;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JMenu;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.LayoutStyle;
import javax.swing.border.Border;
import javax.swing.plaf.basic.BasicInternalFrameTitlePane.TitlePaneLayout;

import engine.Position2D;

public class GUI extends JFrame
{
	Container content;
	
	JPanel[][] fields;
	int gridW;
	int gridH;
	
	Position2D[] snakePos;
	Position2D foodPos = new Position2D();
	
	JPanel grid;
	JPanel options;
	JPanel info;
	
	JLabel lblInfo;
	JLabel lblProf;
	JLabel lblTime;
	JComboBox cmboxProf;
	JComboBox cmboxTime;
	JLabel snakeImg;
	
	//JLabel imgLblHead = new JLabel();
	//JLabel imgLblTail = new JLabel();
	JLabel imgLblProf = new JLabel();
	
	String profStr = "";
	String timeStr = "";
	
	public JButton btn;
	
	// Some States
	private int tailNum = 5;
	
	
	public GUI(int gridWidth, int gridHeight)
	{	
		content = getContentPane();
		setBounds(new Rectangle(1000, 200, 800, 800));
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		// Grid Panel
		gridW = gridWidth;
		gridH = gridHeight;
		fields = new JPanel[gridWidth][gridHeight];
		grid = new JPanel(new GridLayout(gridWidth, gridHeight));
		grid.setBorder(BorderFactory.createLineBorder(Color.LIGHT_GRAY, 4));
		for (int i = 0; i < gridWidth; i++) {
			for (int j = 0; j < gridHeight; j++) {
				JPanel pan = new JPanel(new FlowLayout(FlowLayout.CENTER,0,0));
				fields[i][j] = pan;
				pan.setPreferredSize(new Dimension(40, 40));
				pan.setBackground(Color.WHITE);
				pan.setBorder(BorderFactory.createLineBorder(Color.LIGHT_GRAY, 1));
				grid.add(pan);
			}
		}
		
		// Options Panel
		options = new JPanel();
		options.setPreferredSize(new Dimension(200, 0));
		
		lblProf = new JLabel("Osoba: ");
		cmboxProf = new JComboBox<String>();
		cmboxProf.setFocusable(false);
		cmboxProf.addItem("osoba_1");
		cmboxProf.addItem("osoba_2");
		cmboxProf.addItem("osoba_3");
		options.add(lblProf);
		options.add(cmboxProf);
		
		lblTime = new JLabel("Brzina: ");
		cmboxTime = new JComboBox<String>();
		cmboxTime.setFocusable(false);
		cmboxTime.addItem("0.1 sec");
		cmboxTime.addItem("0.5 sec");
		cmboxTime.addItem("1.0 sec");
		options.add(lblTime);
		options.add(cmboxTime);

		snakeImg = new JLabel();
		snakeImg.setIcon(new ImageIcon("img/snake.png"));
		options.add(snakeImg);
		
		btn = new JButton("Nova igra");
		btn.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				reset();
			}
		});
		options.add(btn);
		
		// Info Panel
		info = new JPanel(new FlowLayout(FlowLayout.CENTER));
		lblInfo = new JLabel("info");
		info.add(lblInfo);
		
		// Adding Content
		content.add(grid, BorderLayout.CENTER);
		content.add(options, BorderLayout.EAST);
		content.add(info, BorderLayout.NORTH);
		
		reset();
		
		pack();
		setVisible(true);
	}
	
	public void reset()
	{
		timeStr = (String)cmboxTime.getSelectedItem();
		profStr = (String)cmboxProf.getSelectedItem();
	}
	
	public void g_update()
	{	
		int x, y;
		
		for (int i = 0; i < gridW; i++) {
			for (int j = 0; j < gridH; j++) {
				fields[i][j].removeAll();
			}
		}
		
		x = foodPos.getX();
		y = foodPos.getY();
		fields[x][y].add(new JLabel(new ImageIcon("img/" + profStr + ".png")));
		//System.out.println("img/" + profStr);
		
		x = snakePos[0].getX();
		y = snakePos[0].getY();
		fields[x][y].add(new JLabel(new ImageIcon("img/head.png")));
		for (int i = 1; i < snakePos.length; i++) {
			x = snakePos[i].getX();
			y = snakePos[i].getY();
			fields[x][y].add(new JLabel(new ImageIcon("img/tail" + i%tailNum + ".png")));
		}
		
		revalidate();
		repaint();
	}
	
	public boolean alert(String s)
	{
		//System.out.println("KRAJ IGRE !!!");
		return (JOptionPane.showConfirmDialog(null, s, "Zmijica", JOptionPane.YES_NO_OPTION) == JOptionPane.YES_OPTION )? true: false;
	}
	
	/* Get & Set */
	
	public void setSnakePos(Position2D[] snakePos) {
		this.snakePos = snakePos;
	}
	
	public void setFoodPos(Position2D pos)
	{
		foodPos = pos;
	}
	
	public void updateInfo(String s)
	{
		lblInfo.setText(s);
	}
	
	public int getTime()
	{	
		switch (timeStr) {
		case "1.0 sec":
			return 1000;
		case "0.5 sec":
			return 500;
		case "0.1 sec":
			return 100;
		default:
			return 300;
		}
	}
}
