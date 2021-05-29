package engine;

public class Map
{
	// Map
	private int width;
	private int height;
	
	// States
	private boolean isEnd;
	private boolean ate;
	
	// Elements
	private Food food;
	
	// Snake
	private Snake snake;
	private Position2D snakeMovDir = new Position2D();
	
	/* Constructors */
	
	public Map(int width, int height)
	{	
		this.width = width;
		this.height = height;
		
		snake = new Snake(getRandomMapPosition(), getRandomDirection());
		food = new Food(getRandomMapPosition());
		
		isEnd = false;
		ate = false;
	}
	
	/* Update */
	
	public void update()
	{
		boolean isEnd;
		
		isEnd = snake.move();
		Position2D headPos = snake.getHeadPosition();
		
		// Head X over map border
		if(headPos.getX() < 0)
			isEnd = snake.moveHead(new Position2D(width-1, headPos.getY()));
		else if(headPos.getX() >= width)
			isEnd = snake.moveHead(new Position2D(0, headPos.getY()));
		
		// Head Y over map border
		if(headPos.getY() < 0)
			isEnd = snake.moveHead(new Position2D(headPos.getX(), height-1));
		else if(headPos.getY() >= height)
			isEnd = snake.moveHead(new Position2D(headPos.getX(), 0));
		
		// Is End
		if(isEnd)
			this.isEnd = true;
			
		// Eat Check
		if(snake.getHeadPosition().isOverlapping(food.position)) {
			snake.eat();
			Food newFood = new Food();
			do {
				newFood.position.set(getRandomMapPosition());
			} while (newFood.position.isOverlapping(food.position) || snake.checkTailCollide(newFood));
			
			food = newFood;
			ate = true;
		}
		
	}
	
	/* State Checks */
	
	public boolean isEnd()
	{
		return isEnd;
	}
	
	public boolean ate()
	{
		if(ate) {
			ate = false;
			return true;
		}
		
		return false;
	}
	
	/* Get & Set */
	
	public Snake getSnake() {
		return snake;
	}
	
	public Food getFood() {
		return food;
	}
	
	public void setSnakeMovDir(Position2D snakeMovDir) {
		this.snakeMovDir.set(snakeMovDir);
	}
	
	public Position2D[] getSnakePositions()
	{
		int l = snake.getLength();
		Position2D[] p = new Position2D[l];
		int i = 0;
		
		SnakeSegment s = snake.getHead();
		while(i < l)
		{
			p[i++] = new Position2D(s.position);
			s = s.getNext();
		}	
		
		return p;
	}
	
	public void spawnFood()
	{
		food = new Food(getRandomMapPosition());
	}
			
	
	/* Helpers */
	
	private Position2D getRandomMapPosition()
	{
		int x = (int)Math.round(Math.random() * (width-1));
		int y = (int)Math.round(Math.random() * (height-1));
		
		return new Position2D(x, y);
	}
	
	private Position2D getRandomDirection()
	{
		int x, y;
		x = y = 0;
		
		boolean xy = ((int)(Math.random()*10) % 2 == 1)? true : false;
		//System.out.println("xy: " + xy);
		
		int r = ((int)(Math.random()*10) % 2 == 1)? 1 : -1;
		//System.out.println("r: " + r);
		
		if(xy) x = r;
		else y = r;
		
		return new Position2D(x, y);
	}
}
