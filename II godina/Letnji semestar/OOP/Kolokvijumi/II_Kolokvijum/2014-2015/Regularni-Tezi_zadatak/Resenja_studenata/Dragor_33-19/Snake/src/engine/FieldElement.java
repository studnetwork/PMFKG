package engine;

public class FieldElement
{
	protected Position2D position = new Position2D();
	
	public FieldElement()
	{
		this(0, 0);
	}
	
	public FieldElement(int x, int y)
	{
		this(new Position2D(x, y));
	}
	
	public FieldElement(Position2D position)
	{
		this.position.set(position);
		//System.out.println("new field element created ("+position.getX()+","+position.getY()+")"); // DEBUG
	}
}
