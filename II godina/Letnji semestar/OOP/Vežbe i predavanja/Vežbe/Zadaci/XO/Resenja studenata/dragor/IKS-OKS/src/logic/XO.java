package logic;

public class XO
{
	private Field[][] board;
	private int N;
	private GameState gameState;
	private Field lastTurn;
	private Field onTurn;
	private int lastX;
	private int lastY;
	
	public XO()
	{
		this(3);
	}
	
	public XO(int boardSize)
	{
		N = boardSize;
		board = new Field[N][N];
	}
	
	public GameState play(int x, int y) throws Exception
	{
		if(gameState != GameState.IN_PROGRESS)
			throw new Exception("Igra nije pocela!");
		
		if(onTurn == Field.N)
			throw new Exception("Niko nije na potezu?!");
		
		if(board[x][y] != Field.N)
			throw new Exception("Zauzeto polje!");
		
		board[x][y] = onTurn;
		lastTurn = onTurn;
		lastX = x;
		lastY = y;
		
		GameState state = checkEnd(lastTurn);
		
		if(state == GameState.IN_PROGRESS) {
			onTurn = (onTurn == Field.X)? Field.O : Field.X;
		}
		else {
			onTurn = Field.N;
			gameState = state;
		}
		
		return gameState;
	}
	
	private GameState checkEnd(Field lastPlayed)
	{
		boolean ind;
		GameState winner = (lastPlayed == Field.X)? GameState.X_WIN : GameState.O_WIN;
			
		// Vertical
		ind = true;
		for (int i = 0; i < N; i++) {
			if(board[i][lastY] != onTurn) {
				ind = false;
				break;
			}
		}
		if(ind) return winner;
		
		// Horizontal
		ind = true;
		for (int i = 0; i < N; i++) {
			if(board[lastX][i] != onTurn) {
				ind = false;
				break;
			}
		}
		if(ind) return winner;
		
		// Main Diagonal
		if(lastX == lastY)
		{
			ind = true;
			for (int i = 0; i < N; i++) {
				if(board[i][i] != onTurn) {
					ind = false;
					break;
				}
			}
			if(ind) return winner;
		}
		
		// Main Diagonal
		if(lastX + lastY == N-1)
		{
			ind = true;
			for (int i = 0; i < N; i++) {
				if(board[i][N-1-i] != onTurn) {
					ind = false;
					break;
				}
			}
			if(ind) return winner;
		}
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if(board[i][j] == Field.N)
					return GameState.IN_PROGRESS;
			}
		}
		
		return GameState.DRAW;
	}

	public GameState newGame()
	{
		clearBoard();
		
		onTurn = Field.X; // X uvek igra prvi ??
		lastTurn = Field.N;
		gameState = GameState.IN_PROGRESS;
		return gameState;
	}
	
	public void clearBoard()
	{
		int boardSize = board.length;
		
		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				board[i][j] = Field.N;
	}
	
	/* State Checking */
	
	public GameState getGameState() {
		return gameState;
	}
	
	public Field getOnTurn() {
		return onTurn;
	}
	
	public Field getLastTurn() {
		return lastTurn;
	}
	
	/*public int getLastX() {
		return lastX;
	}
	
	public int getLastY() {
		return lastY;
	}*/
}
