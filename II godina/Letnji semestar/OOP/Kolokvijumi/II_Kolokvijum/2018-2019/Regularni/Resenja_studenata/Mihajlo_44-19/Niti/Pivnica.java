public class Pivnica 
{
	private int sto;
	private int brojPiva;
	
	public Pivnica()
	{
		this.sto = 0;
		this.brojPiva = 0;
	}
	
	synchronized public void natociPivo() throws Exception
	{
		while(brojPiva == 5)
		{
			System.out.println("Sanker ceka...");
			wait();
		}
		
		System.out.println("Sanker dodaje pivo na sto!");
		try {
			Thread.sleep(2000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		brojPiva++;
		
		if(brojPiva == 5) notifyAll();
		
		System.out.println("Broj piva na stolu: " + brojPiva);
	}
	
	synchronized public void popijPivo() throws Exception
	{
		sto++;
		while(sto < 5 || brojPiva == 0)
		{
			System.out.println("Gost ceka...");
			wait();
		}
		
		System.out.println("Gost pocinje da ispija!");
		try {
			Thread.sleep(2000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		brojPiva--;
		
		if(brojPiva == 0) notifyAll();
		
		System.out.println("Broj piva na stolu: " + brojPiva);
	}
}
