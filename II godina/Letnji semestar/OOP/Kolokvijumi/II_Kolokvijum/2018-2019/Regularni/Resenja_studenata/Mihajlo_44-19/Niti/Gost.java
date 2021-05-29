public class Gost extends Thread
{
	Pivnica pivnica;
	
	public Gost(Pivnica pivnica)
	{
		this.pivnica = pivnica;
	}
	
	@Override
	public void run() 
	{
		super.run();
		
		for(int i = 0; i < 5; i++)
		{
			try {
				pivnica.popijPivo();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
