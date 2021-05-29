package engine;

public class Snake
{
	private SnakeSegment head;
	private int length;
	private Position2D moveDir;
	
	public Snake(Position2D pos, Position2D dir)
	{
		head = new SnakeSegment(pos);
		moveDir = new Position2D(dir);
		length = 1;
		
		//System.out.println("new Snake: pos (), dir ()");
	}
	
	/* Move */
	
	public void setMoveDir(Position2D dir)
	{
		if(dir.getX() + moveDir.getX() != 0 && dir.getY() + moveDir.getY() != 0)
			moveDir.set(dir);
	}
	
	public boolean move()
	{
		Position2D pos = new Position2D(head.position);
		pos.move(moveDir);
		head.move(pos);
		
		boolean c = checkTailCollide(head); 
		if(c)
			System.out.println("Move Head Collide -> TRUE");
		
		return c;
	}

	public boolean moveHead(Position2D pos)
	{
		head.position.set(pos);
		boolean c = checkTailCollide(head);
		if(c)
			System.out.println("Move Head Collide -> TRUE");
		return c;
	}
	
	/* Checks */
	
	public boolean checkTailCollide(FieldElement e)
	{
		return head.checkTailCollide(e);
	}
	
	/* Eat */
	
	public void eat()
	{
		head.addSegment();
		length++;
	}
	
	/* Get & Set */
	
	public int getLength() {
		return length;
	}
	
	public SnakeSegment getHead() {
		return head;
	}
	
	public Position2D getHeadPosition() {
		return head.position;
	}
	
	/* Debug */
	
	public void print()
	{
		System.out.println("snake info:\n dir (" + moveDir.getX() + "," + moveDir.getY() + ")");
		head.printPosition();
	}
}





