import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

import javax.swing.ImageIcon;

public class Test {

	public static void main(String[] args) {
		ucitajFajl("mapa.csv");
	}
	
	public static void ucitajFajl(String fileName) 
	{
		
		try
		{
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)));
			
			String linija;
			String[] kolone;
			int i = 0;
			
			while ( (linija = br.readLine()) != null) 
			{
				kolone = linija.split(",");
				
				for (int j = 0; j < kolone.length; j++) 
				{	
					ImageIcon ic = new ImageIcon();
					
					kolone[j].trim();
					
					if(kolone[j].equals("zid"))
					{
						// TO DO
						System.out.print(" " + kolone[j]);
					}
					else if(kolone[j].equals("prazno"))
					{
						// TO DO
						System.out.print(" " + kolone[j]);
					}
					if(kolone[j].equals("coveculjak"))
					{
						// TO DO
						System.out.print(" " + kolone[j]);
					}
					if(kolone[j].equals("kutija"))
					{
						// TO DO
						System.out.print(" " + kolone[j]);
					}
					if(kolone[j].equals("cilj"))
					{
						// TO DO
						System.out.print(" " + kolone[j]);
					}
					if(kolone[j].equals("ciljKutija"))
					{
						// TO DO
						System.out.print(" " + kolone[j]);
					}
				}
				
				i++;
				System.out.println();
				
			}
			
			br.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
