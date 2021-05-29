import java.util.ArrayList;
import java.util.List;

public class Test 
{
	public static void main(String[] args) 
	{
		Pivnica pivnica = new Pivnica();
		
		List<Gost> gosti = new ArrayList<Gost>();
		
		Sanker sanker = new Sanker(pivnica);
		
		for(int i = 0; i < 5; i++)
		{
			gosti.add(new Gost(pivnica));
		}
		
		sanker.start();
		
		for(int i = 0; i < 5; i++)
		{
			gosti.get(i).start();
		}
	}
}
