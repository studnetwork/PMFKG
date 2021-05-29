import java.awt.KeyEventDispatcher;
import java.awt.KeyboardFocusManager;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import javax.swing.Timer;

import engine.*;
import gui.GUI;

public class Game
{
	
	static int mapWidth = 16;
	static int mapHeight = 15;
	
	static Map map;
	static GUI gui;
	static Snake snake;
	static Food food;
	
	static Timer t;
	static int delay;
	static int score;
	
	static KeyboardFocusManager manager;

	public static void main(String[] args)
	{
		t = new Timer(300, new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent arg0) {
				g_update();
			}
		});
		
		manager = KeyboardFocusManager.getCurrentKeyboardFocusManager();
		manager.addKeyEventDispatcher(new KeyEventDispatcher() {
			
			@Override
			public boolean dispatchKeyEvent(KeyEvent e) {
				//System.out.println("KEYYYYYY");
				if(e.getID() == KeyEvent.KEY_PRESSED)
				{
					switch (e.getKeyCode()) {
					case KeyEvent.VK_UP:
						//System.out.println("KEY UP !!!");
						snake.setMoveDir(new Position2D(-1,0));
						break;
					case KeyEvent.VK_DOWN:
						//System.out.println("KEY DOWN !!!");
						snake.setMoveDir(new Position2D(1,0));
						break;
					case KeyEvent.VK_LEFT:
						//System.out.println("KEY LEFT !!!");
						snake.setMoveDir(new Position2D(0,-1));
						break;
					case KeyEvent.VK_RIGHT:
						//System.out.println("KEY RIGHT !!!");
						snake.setMoveDir(new Position2D(0,1));
						break;
					default:
						break;
					}
				}
				return false;
			}
		});
		
		gui = new GUI(mapHeight, mapWidth);
		reset();
		
		gui.btn.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				reset();
			}
		});
		
		t.start();
	}
	
	public static void g_update()
	{
		map.update();
			
		if(map.ate()) {
			map.spawnFood();
			food = map.getFood();
			score++;
		}
		
		//System.out.println("score: " + score);
		//snake.print(); // DEBUG
		//map.getSnakePositions(); // DEBUG
		
		gui.setSnakePos(map.getSnakePositions());
		gui.setFoodPos(food.getPostition());
		gui.updateInfo("Pojeli ste " + score + " nastavnika");
		gui.g_update();
		
		if(map.isEnd()) {
			//System.out.println("bite itself !!!");
			t.stop();
			if(gui.alert("Kraj Igre! Zelite li da pokrenete ponovo igru?"))
				reset();
			return;
		}
	}
	
	public static void reset()
	{
		gui.reset();
		delay = gui.getTime();
		t.stop();
		t.setDelay(delay);
		t.start();
		
		score = 0;
		map = new Map(mapHeight, mapWidth);
		
		snake = map.getSnake();
		food = map.getFood();
	}
}