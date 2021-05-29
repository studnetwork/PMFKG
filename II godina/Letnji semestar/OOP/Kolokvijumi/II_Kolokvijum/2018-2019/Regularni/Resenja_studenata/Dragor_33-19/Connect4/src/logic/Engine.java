package logic;

public class Engine
{
	// Table
	private Ball[][] table;
	private int height;
	private int width;
	
	// Players
	private Ball onTurn;
	private int redTurns;
	private int yelTurns;
	
	public Engine(int h, int w)
	{
		// Table
		height = h;
		width = w;
		table = new Ball[h][w];
		
		init();
	}
	
	public void init()
	{
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				table[i][j] = Ball.EMPTY;
			}
		}
		
		onTurn = Ball.RED;
		redTurns = 0;
		yelTurns = 0;
	}
	
	public TurnResult placeBall(int c)
	{
		if(c < 0 || c >= width) 
			return TurnResult.ERROR;
		
		int i;
		for (i = 0; i < height && table[i][c] == Ball.EMPTY; i++);
		i--;
		
		if(i >= 0)
		{	
			//System.out.println("proslo");
			// Turn Successful
			table[i][c] = onTurn;
			
			if(onTurn == Ball.RED) redTurns++;
			else yelTurns++;
			
			if(CheckWin(i, c)) return TurnResult.WIN;
			
			onTurn = (onTurn == Ball.RED)? Ball.YELLOW : Ball.RED;
			
			if(redTurns + yelTurns == width * height)
				return TurnResult.DRAW;
			
			return TurnResult.NONE;
		}
		
		return TurnResult.ERROR;
	}
	
	private boolean CheckWin(int r, int c)
	{
		int count;
		
		// Vertical
		count = 1;
		for(int i = r-1, j = c; i >= 0 && count < 4 && table[i][j] == onTurn; i--) count++;
		for(int i = r+1, j = c; i < height && count < 4 && table[i][j] == onTurn; i++) count++;
		//System.out.println("count: " + count);
		if(count == 4) return true;
		
		// Horizontal
		count = 1;
		for(int i = r, j = c-1; j >= 0 && count < 4 && table[i][j] == onTurn; j--) count++;
		for(int i = r, j = c+1; j < width && count < 4 && table[i][j] == onTurn; j++) count++;
		//System.out.println("count: " + count);
		if(count == 4) return true;
		
		// Diagonal (/)
		count = 1;
		for(int i = r+1, j = c-1; j >= 0 && i < height && count < 4 && table[i][j] == onTurn; j--, i++) count++;
		for(int i = r-1, j = c+1; j < width && i >= 0 && count < 4 && table[i][j] == onTurn; j++, i--) count++;
		//System.out.println("count: " + count);
		if(count == 4) return true;
		
		// Diagonal (\)
		count = 1;
		for(int i = r-1, j = c-1; j >= 0 && i >= 0 && count < 4 && table[i][j] == onTurn; j--, i--) count++;
		for(int i = r+1, j = c+1; j < width && i < height && count < 4 && table[i][j] == onTurn; j++, i++) count++;
		//System.out.println("count: " + count);
		if(count == 4) return true;
		
		// None
		//System.out.println("false");
		return false;
	}

	/* Get & Set */
	
	public Ball readTable(int r, int c)
	{
		return table[r][c];
	}
	
	public int getHeight() {
		return height;
	}
	
	public int getWidth() {
		return width;
	}
	
	public Ball getOnTurn() {
		return onTurn;
	}
	
	public int getRedTurns() {
		return redTurns;
	}
	
	public int getYelTurns() {
		return yelTurns;
	}
}
