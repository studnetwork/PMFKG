package zadatak1;

import zadatak1.protocol.Hit;
import zadatak1.protocol.Login;

import java.beans.XMLDecoder;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    public static int PORT = 4321;
    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(PORT);

            int N = 2;
            int tN = 0;

            while (true) {
                if (tN >= N) {
                    Socket rejectSocket = serverSocket.accept();
                    rejectSocket.close();
                }

                tN += 1;

                System.out.println("Partija " + tN + ": Trazim igrace");

                final Socket firstPlayer = serverSocket.accept();
                final BufferedWriter firstWriter = new BufferedWriter(new OutputStreamWriter(firstPlayer.getOutputStream()));
                final BufferedReader firstReader = new BufferedReader(new InputStreamReader(firstPlayer.getInputStream()));


                XMLDecoder decoder = new XMLDecoder(new ByteArrayInputStream(firstReader.readLine().getBytes()));
                Object obj = decoder.readObject();
                decoder.close();
                final Login firstLogin;
                if (obj instanceof Login) {
                    firstLogin = (Login) obj;
                    System.out.println("Partija " + tN + ": Nadjen prvi igrac " + firstLogin.name);
                } else
                    return;

                firstWriter.write("Tvoja prijava je prihvacena, smesten si u partiju " + tN + ". Ceka se na drugog igraca\n");
                firstWriter.flush();

                final Socket secondPlayer = serverSocket.accept();
                final BufferedWriter secondWriter = new BufferedWriter(new OutputStreamWriter(secondPlayer.getOutputStream()));
                final BufferedReader secondReader = new BufferedReader(new InputStreamReader(secondPlayer.getInputStream()));

                decoder = new XMLDecoder(new ByteArrayInputStream(secondReader.readLine().getBytes()));
                obj = decoder.readObject();
                final Login secondLogin;
                if (obj instanceof Login) {
                    secondLogin = (Login) obj;
                    System.out.println("Partija " + tN + ": Nadjen drugi igrac " + secondLogin.name);
                } else
                    return;

                secondWriter.write("Tvoja prijava je prihvacena, smesten si u partiju " + tN + ". Igra uskoro pocinje\n");
                secondWriter.flush();

                System.out.println("Partija " + tN + ": Svi igraci su nadjeni, pravim thread");

                firstWriter.write("Igra je zapocela, tvoj protivnik je " + secondLogin.name + "\n");
                firstWriter.flush();
                secondWriter.write("Igra je zapocela, tvoj protivnik je " + firstLogin.name + "\n");
                secondWriter.flush();

                final int matchId = tN;

                new Thread(() -> {
                    try {
                        boolean skipFirst = false;
                        boolean skipSecond = false;

                        String winner = "";

                        while (true) {
                            // Igrva prvo prvi protivnik;
                            if (!skipFirst) {
                                firstWriter.write("Izaberi\n");
                                firstWriter.flush();

                                XMLDecoder decoder1 = new XMLDecoder(new ByteArrayInputStream(firstReader.readLine().getBytes()));
                                Object obj1 = decoder1.readObject();
                                decoder1.close();

                                Hit firstHit;
                                if (obj1 instanceof Hit) {
                                    firstHit = (Hit) obj1;
                                    System.out.println("Partija " + matchId + ": " + firstLogin.name + " gadja kordinate (" + firstHit.x + ", " + firstHit.y + ")");
                                } else
                                    return;

                                secondWriter.write("Odgovori\n");
                                secondWriter.flush();

                                secondWriter.write(firstHit.toString() + "\n");
                                secondWriter.flush();

                                String response = secondReader.readLine();

                                if (response.startsWith("NISTA")) {
                                    firstWriter.write("Nisi nista pogodio!\n");
                                    firstWriter.flush();
                                    skipSecond = false;
                                } else if (response.startsWith("DEO")){
                                    firstWriter.write("Pogodio si deo broda!  Igras ponovo\n!");
                                    firstWriter.flush();

                                    firstWriter.write("Izaberi\n");
                                    firstWriter.flush();
                                    skipSecond = true;
                                } else if (response.startsWith("CEO")) {
                                    firstWriter.write("Unistio si ceo brod! Igras ponovo\n");
                                    firstWriter.flush();

                                    firstWriter.write("Izaberi\n");
                                    firstWriter.flush();
                                    skipSecond = true;
                                } else if (response.startsWith("KRAJ")){
                                    winner = firstLogin.name;
                                    break;
                                }
                            }

                            if (!skipSecond) {
                                secondWriter.write("Izaberi\n");
                                secondWriter.flush();

                                XMLDecoder decoder1 = new XMLDecoder(new ByteArrayInputStream(secondReader.readLine().getBytes()));
                                Object obj1 = decoder1.readObject();
                                decoder1.close();

                                Hit firstHit;
                                if (obj1 instanceof Hit) {
                                    firstHit = (Hit) obj1;
                                    System.out.println("Partija " + matchId + ": " + secondLogin.name + " gadja kordinate (" + firstHit.x + ", " + firstHit.y + ")");
                                } else
                                    return;

                                firstWriter.write("Odgovori\n");
                                firstWriter.flush();

                                firstWriter.write(firstHit.toString() + "\n");
                                firstWriter.flush();

                                String response = firstReader.readLine();

                                if (response.startsWith("NISTA")) {
                                    secondWriter.write("Nisi nista pogodio!  Igras ponovo\n");
                                    secondWriter.flush();
                                    skipFirst = false;
                                } else if (response.startsWith("DEO")){
                                    secondWriter.write("Pogodio si deo broda!  Igras ponovo\n!");
                                    secondWriter.flush();

                                    secondWriter.write("Izaberi\n");
                                    secondWriter.flush();
                                    skipFirst = true;
                                } else if (response.startsWith("CEO")) {
                                    secondWriter.write("Unistio si ceo brod! Igras ponovo\n");
                                    secondWriter.flush();

                                    secondWriter.write("Izaberi\n");
                                    secondWriter.flush();
                                    skipFirst = true;
                                } else if (response.startsWith("KRAJ")){
                                    winner = secondLogin.name;
                                    break;
                                }
                            }
                        }

                        firstWriter.write("KRAJ! Pobednik je " + winner + "\n");
                        firstWriter.flush();
                        secondWriter.write("KRAJ! Pobednik je " + winner + "\n");
                        secondWriter.flush();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                }).start();
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }
}
