package engine;

public class Position2D
{
	private int x;
	private int y;
	
	public Position2D()
	{
		this(0, 0);
	}
	
	public Position2D(int x, int y)
	{
		set(x, y);
	}
	
	public Position2D(Position2D pos)
	{
		set(pos);
	}
	
	public void set(int x, int y)
	{
		this.x = x;
		this.y = y;
	}
	
	public void set(Position2D pos)
	{
		set(pos.x, pos.y);
	}
	
	public int getX() {
		return x;
	}
	
	public int getY() {
		return y;
	}
	
	public void move(Position2D mov)
	{
		set(x+mov.x, y+mov.y);
	}
	
	/* Checks */
	
	public boolean isOverlapping(Position2D pos)
	{
		if(x == pos.x && y == pos.y)
			return true;
		else
			return false;
	}
}
