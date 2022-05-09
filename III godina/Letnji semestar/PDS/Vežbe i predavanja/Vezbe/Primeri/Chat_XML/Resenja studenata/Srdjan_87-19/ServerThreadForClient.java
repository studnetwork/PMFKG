import java.beans.XMLDecoder;
import java.beans.XMLEncoder;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.util.HashMap;

public class ServerThreadForClient extends Thread {
	private static final String accessCode = "8719"; // fqu4Ld6s
	
	private HashMap<String, BufferedWriter> clients;
	private Socket clientSocket;
	private String clientName;
	
	public ServerThreadForClient(HashMap<String, BufferedWriter> clients, Socket clientSocket) {
		this.clients = clients;
		this.clientSocket = clientSocket;
	}

	@Override
	public void run() {
		try {
			BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(
					clientSocket.getOutputStream()));
			
			BufferedReader br = new BufferedReader(new InputStreamReader(
					clientSocket.getInputStream()));
			
			// Payload/request se prenosi kao XML (obicno je u XML ili JSON formatu)
			String requestAsXMLstring = br.readLine();
			
			XMLDecoder decoder = new XMLDecoder(new ByteArrayInputStream(
					requestAsXMLstring.getBytes()));
			
			Object requestObject = decoder.readObject();
			
			
			if(! (requestObject instanceof Login) ) {
				clientSocket.close();
				return;
			}
			
			Login loginRequest = (Login) requestObject;
			
			String code = loginRequest.getCode();
			
			// proveri da li request sadrzi validan access code
			if(! code.equals(accessCode)) {
				clientSocket.close();
				return;
			}
			
			clientName = loginRequest.getName();
			
			// sinhronizuj sa ostalim client thread-ovima kako ne bi doslo do greske
			// pri upisivanju
			synchronized (clients) {
				clients.put(clientName, bw);
			}
			
			// obavesti sve prijavljene klijente o prijavi novog korisnika
			broadcastMessage(
					new Message("Novi korisnik=" + clientName, "Server"));
			
			// posalji korisniku listu svih prijavljenih korisnika
			Message msg = new Message("Klijenti=" + clients.keySet(), "Server");
			bw.write(msg.toString() + "\n");
			bw.flush();
			
			PrivateMessage pm = null;
			
			// korisnik je sada prijavljen; nit ce obradjivati nove zahteve sve dok 
			// se korisnik ne odjavi
			while(true) {
				requestAsXMLstring = br.readLine();
				
				decoder = new XMLDecoder(new ByteArrayInputStream(
						requestAsXMLstring.getBytes()));
				
				requestObject = decoder.readObject();
				
				if(requestObject instanceof Logout) {
					BufferedWriter clientWriter = null;
					
					synchronized (clients) {
						clientWriter = clients.remove(clientName);
					}
					
					clientWriter.write(new Logout().toString() + "\n");
					clientWriter.flush();
					
					// zatvori sokect ukoliko je ostao otvoren
					if(clientSocket.isConnected())
						clientSocket.close();
					
					// obavesti preostale prijavljene korisnike o odjavi datog korisnika
					broadcastMessage(
							new Message("Korisnik " + clientName + " se odjavio", "Server"));
					
					// prekid petlje za obradu zahteva datog korisnika
					break;
				}
				// MORA da ide pre `if(requestObject instanceof Message)` jer PrivateMessage nasledjuje Message
				// pa posto je njegova instanca onda nikada ne bi doslo do izvrsavanja koda za PrivateMessage
				else if(requestObject instanceof PrivateMessage) {
					pm = (PrivateMessage) requestObject;
					pm.setSender(clientName);
					
					String recipientName = pm.getRecipient();
					BufferedWriter recipient = clients.get(recipientName);
					
					recipient.write(pm.toString() + "\n");
					recipient.flush();
				}
				else if(requestObject instanceof Message) {
					msg = (Message) requestObject;
					
					msg.setSender(clientName);
					broadcastMessage(msg);
				}
				else {
					System.out.println("Nepoznat tip zahteva: " + requestObject.getClass().getName());
					continue;
				}
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				clientSocket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	private void broadcastMessage(Message msg) {
		for (BufferedWriter clientWriter : clients.values()) {
			try {
				clientWriter.write(msg.toString() + "\n");
				clientWriter.flush();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
}
