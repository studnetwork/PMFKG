public class Sanker extends Thread
{
	Pivnica pivnica;
	
	public Sanker(Pivnica pivnica)
	{
		this.pivnica = pivnica;
	}
	
	@Override
	public void run() 
	{
		super.run();
		
		for(int i = 0; i < 25; i++)
		{
			try {
				pivnica.natociPivo();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
