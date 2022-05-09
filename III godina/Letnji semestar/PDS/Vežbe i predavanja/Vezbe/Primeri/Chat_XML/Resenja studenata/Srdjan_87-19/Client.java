import java.beans.XMLDecoder;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;

// accessCode = "8719"

public class Client {
	
	public static void main(String[] args) {
		Socket socket = null;
		try {
			socket = new Socket(InetAddress.getByName("localhost"), Server.PORT);
			
			BufferedReader br = new BufferedReader(new InputStreamReader(
					socket.getInputStream()));
			
			BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(
					socket.getOutputStream()));
			
			Thread communicationToServerThread = new Thread(new Runnable() {
				
				@Override
				public void run() {
					String clientName;
					String accessCode;
					
					Scanner scanner = new Scanner(System.in);
						
					System.out.println("Enter your name: ");
					clientName = scanner.nextLine(); 

					System.out.println("\nEnter chat access code: ");
					accessCode = scanner.nextLine(); 
					
					System.out.println(
							String.format("\nEntered data: name=%s, code=%s", clientName, accessCode));
					
					// posalji zahtev za prijavu
					Login loginRequest = new Login(clientName, accessCode);
					try {
						bw.write(loginRequest.toString() + "\n");
						bw.flush();
					} catch (IOException e) {
						e.printStackTrace();
					}	
						
					// petlja koja obradjuje korisnicki unos //
					
					String msgStr = null;
					Message msg = null;
					String userInput = null;
					String[] inputParts = null;
					
					System.out.println("\n====\nCHAT\n====\n");
					System.out.println("Commands:");
					System.out.println("   LOGOUT\n" 
									 + "   ALL: message to everyone in the chat\n"
									 + "   some_user: this is a private message\n");
					
					while(true) {
						
						userInput = scanner.nextLine().trim(); 
						
						while(userInput.equals(""))
							userInput = scanner.nextLine().trim(); 
						
						if(userInput.equals("LOGOUT")) {
							try {
								bw.write(new Logout().toString() + "\n");
								bw.flush();
							} catch (IOException e) {
								e.printStackTrace();
							}
							
							// prekid petlje za obradu unosa
							break;
						}
						
						inputParts = userInput.split(":");
						
						// nastavlja sa sledecim prolazom ako format poruke nije ispravan
						if(inputParts.length < 2) {
							System.out.println("Invalid message format. Valid format is 'RECIPIENT: message content'\n");
							continue;
						}
						
						if(inputParts[0].equals("ALL")) {
							msgStr = new Message(inputParts[1], null).toString();
						}
						else {
							msgStr = new PrivateMessage(inputParts[1], null, inputParts[0]).toString();
						}
						
						// posalji poruku
						try {
							bw.write(msgStr + "\n");
							bw.flush();
						} catch (IOException e) {
							e.printStackTrace();
						}
					}
				}
			});
			
			Thread communicationFromServerThread = new Thread(new Runnable() {
				
				@Override
				public void run() {
					String requestSerializedAsXML = null;
					XMLDecoder decoder = null;
					Object requestObject = null;
					Message msg = null;
					while(true) {
						try {
							requestSerializedAsXML = br.readLine();
							decoder = new XMLDecoder(new ByteArrayInputStream(
									requestSerializedAsXML.getBytes()));
							
							requestObject = decoder.readObject();
							
							if(requestObject instanceof Logout) {
								break;
							}
							else if(requestObject instanceof Message) {
								msg = (Message) requestObject;
								System.out.println(msg.getSender() + ": " + msg.getContent());
							}
							
						} catch (IOException e) {
							e.printStackTrace();
						}
						
						
					}
				}
					
			});
			
			communicationToServerThread.start();
			communicationFromServerThread.start();
			
			communicationToServerThread.join();
			communicationFromServerThread.join();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		} finally {
			try {
				socket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

}
