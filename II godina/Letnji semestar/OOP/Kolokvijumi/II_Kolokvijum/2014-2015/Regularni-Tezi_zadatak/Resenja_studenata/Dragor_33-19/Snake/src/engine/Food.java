package engine;

public class Food extends FieldElement implements CanMove {

	public Food() 
	{
		super();
	}

	public Food(int x, int y)
	{
		super(x, y);
	}
	
	public Food(Position2D pos)
	{
		super(pos);	
	}
	
	/* Move */
	
	public void move(Position2D newPos)
	{
		position.set(newPos);
	}
	
	public void move(int x, int y)
	{
		move(new Position2D(x, y));
	}
	
	/* Get & Set */
	
	public Position2D getPostition() {
		return position;
	}
}
