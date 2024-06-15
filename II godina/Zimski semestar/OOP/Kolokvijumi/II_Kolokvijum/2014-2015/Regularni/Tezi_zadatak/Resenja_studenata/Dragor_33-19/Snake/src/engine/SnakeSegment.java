package engine;

public class SnakeSegment extends FieldElement implements CanMove
{
	private SnakeSegment next = null;
	private Position2D lastPosition;
	
	/* Constructors */
	
	public SnakeSegment(Position2D pos)
	{
		super(pos);
		lastPosition = new Position2D(-1,-1);
	}
	
	public SnakeSegment() {
		this(new Position2D());
	}
	
	public SnakeSegment(int x, int y) {
		this(new Position2D(x, y));
	}
	
	/* Move */
	
	public void move(Position2D newPos)
	{
		lastPosition.set(position);
		position.set(newPos);
		
		if(next != null)
			next.move(lastPosition);
	}
	
	public void move(int x, int y)
	{
		move(new Position2D(x, y));
	}
	
	/* Add Segment */

	public void addSegment()
	{
		if(next == null)
			next = new SnakeSegment(lastPosition);
		else
			next.addSegment();
	}
	
	/* Collides */
	
	public boolean checkTailCollide(FieldElement el)
	{	
		if(next == null)
			return false;
		
		if(next.position.isOverlapping(el.position)) {
			System.out.println("OVERLAP!!! (" + next.position.getX() + "," + next.position.getY() + ")"); // DEBUG
			return true;
		}
		else
			return next.checkTailCollide(el);
	}
	
	/* Get & Set */
	
	public SnakeSegment getNext() {
		return next;
	}
	
	/* Debug */
	
	public void printPosition()
	{
		System.out.println(" pos: (" + position.getX() + "," + position.getY() + ")  last: (" + lastPosition.getX() + "," + lastPosition.getY() + ")");
		if(next != null)
			next.printPosition();
	}

}




