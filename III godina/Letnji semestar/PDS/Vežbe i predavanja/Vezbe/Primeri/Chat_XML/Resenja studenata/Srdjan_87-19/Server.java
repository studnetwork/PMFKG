import java.io.BufferedWriter;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;

public class Server {
	
	public static final short PORT = 6789;
	
	public static void main(String[] args) {
		
		HashMap<String, BufferedWriter> clients = new HashMap<String, BufferedWriter>(); 
		
		try {
			ServerSocket serverSocket = new ServerSocket(PORT);
			
			// prihvata nove zahteva za konekciju i za svaku pravi novi thread koji je opsluzuje
			while(true) {
				System.out.println("\nListening...");
				Socket socket = serverSocket.accept();

				System.out.println("Connection request accepted. " + socket);
				ServerThreadForClient clientThread = new ServerThreadForClient(clients, socket);
				clientThread.start();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
