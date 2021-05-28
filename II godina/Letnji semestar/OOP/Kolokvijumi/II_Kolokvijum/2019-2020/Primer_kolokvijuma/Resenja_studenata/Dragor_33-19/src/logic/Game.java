package logic;

public class Game
{
	// Table
	private Field[][] table;
	private int tableWidth;
	private int tableHeight;
	private int N;
	
	// States
	private int hits;
	private int attempts;
	private int opened;
	private Field toCheck[];
	
	/* Construct */
	
	public Game(int tableHeight, int tableWidth)
	{
		this.tableWidth = tableWidth;
		this.tableHeight = tableHeight;
		N = tableWidth * tableHeight;
		
		init();
	}
	
	/* Table */
	
	public void init()
	{
		table = new Field[tableHeight][tableWidth];
		toCheck = new Field[2];
		
		// New Random Table Data
		int[] randIds = randIdArr(N);
		for (int i = 0; i < tableHeight; i++) {
			for (int j = 0; j < tableWidth; j++) {
				table[i][j] = new Field(randIds[i*tableWidth+j]);
				System.out.print(table[i][j].getId() + " "); //DEBUG
			}
			System.out.println(); //DEBUG
		}
		
		hits = 0;
		attempts = 0;
		opened = 0;
	}
	
	public boolean openField(int i, int j)
	{
		if(opened == toCheck.length)
			return false;
		
		table[i][j].open();
		toCheck[opened] = table[i][j];
		opened++;
		
		System.out.println("opened (" + opened + "): " + table[i][j].getId() + "(" + i + "," + j + ")"); //DEBUG
		
		if(opened == toCheck.length)
			return true;
		else
			return false;
	}
	
	public void closeField(int i, int j)
	{
		if(opened == 0)
			return;
		
		table[i][j].close();
		opened--;
		toCheck[opened] = null;
		
		System.out.println("closed: " + table[i][j].getId() + "(" + i + "," + j + ")"); //DEBUG
	}
	
	public boolean hitCheck()
	{
		for (int i = 0; i < toCheck.length; i++) {
			if(toCheck[i] == null)
				return false;
		}
		
		int n = toCheck.length;
		boolean hit = true;
		int id = toCheck[0].getId();
		
		for (int i = 1; i < toCheck.length; i++) {
			if(toCheck[i].getId() != id) {
				hit = false;
				System.out.println("NOT SAME"); //DEBUG
				break;
			}
		}
		
		if(!hit) {
			for (int i = 0; i < toCheck.length; i++) {
				toCheck[i].close();
			}
		}
		else {
			for (int i = 0; i < toCheck.length; i++) {
				toCheck[i].dissable();
			}
			hits++;
		}
		
		attempts++;
		opened = 0;
		toCheck = new Field[n];
		
		return hit;
	}
	
	/* Get & Set */
	
	public Field[][] getTable() {
		return table;
	}
	
	public int getAttempts() {
		return attempts;
	}
	
	public int getHits() {
		return hits;
	}
	
	/* Helpers */
	
	private int[] randIdArr(int len)
	{
		int[] arr = new int[len];
		 
		for (int i = 0; i < arr.length; i++)
			arr[i] = i/2;
		 
		int j, t;
		for (int i = 0; i < arr.length; i++)
		{
			j = (int)(Math.random()*(len-1));
			t = arr[j];
			arr[j] = arr[i];
			arr[i] = t;
		}
		
		/*//DEBUG
		for (int i = 0; i < arr.length; i++)
			System.out.println(arr[i]);
		*/
		
		return arr;
	}
}
