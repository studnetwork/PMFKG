package logic;

public class Field
{
	private int id;
	private boolean opened;
	private boolean enabled;
	
	/* Construct */
	
	public Field(int id)
	{
		this.id = id;
		opened = false;
		enabled = true;
	}
	
	/* Get & Set */
	
	public int getId() {
		return id;
	}
	
	public boolean isOpened() {
		return opened;
	}
	
	public boolean isEnabled() {
		return enabled;
	}
	
	public void open() {
		this.opened = true;
	}
	
	public void close() {
		this.opened = false;
	}
	
	public void enable() {
		this.enabled = true;
	}
	
	public void dissable() {
		this.enabled = false;
	}
}
