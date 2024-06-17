package zadatak1;

import zadatak1.battleshipgame.*;
import zadatak1.protocol.Hit;
import zadatak1.protocol.Login;
import zadatak1.Server;

import java.beans.XMLDecoder;
import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.sql.SQLOutput;
import java.util.ArrayList;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try {
            ArrayList<Coordinate2D> arrayList = new ArrayList<>();
            arrayList.clear();
            arrayList.add(new Coordinate2D(1, 1));
            arrayList.add(new Coordinate2D(1, 2));
            arrayList.add(new Coordinate2D(1, 3));
            arrayList.add(new Coordinate2D(1, 4));
            Battleship battleship = new Battleship(arrayList);
            arrayList.clear();
            arrayList.add(new Coordinate2D(2, 1));
            arrayList.add(new Coordinate2D(2, 2));
            arrayList.add(new Coordinate2D(2, 3));
            Cruiser cruiser1 = new Cruiser(arrayList);
            arrayList.clear();
            arrayList.add(new Coordinate2D(2, 4));
            arrayList.add(new Coordinate2D(2, 5));
            arrayList.add(new Coordinate2D(2, 6));
            Cruiser cruiser2 = new Cruiser(arrayList);
            arrayList.clear();
            arrayList.add(new Coordinate2D(3, 1));
            arrayList.add(new Coordinate2D(3, 2));
            Destroyer destroyer1 = new Destroyer(arrayList);
            arrayList.clear();
            arrayList.add(new Coordinate2D(3, 3));
            arrayList.add(new Coordinate2D(3, 4));
            Destroyer destroyer2 = new Destroyer(arrayList);
            arrayList.clear();
            arrayList.add(new Coordinate2D(3, 5));
            arrayList.add(new Coordinate2D(3, 6));
            Destroyer destroyer3 = new Destroyer(arrayList);
            arrayList.clear();
            arrayList.add(new Coordinate2D(4, 1));
            Submarine submarine1 = new Submarine(arrayList);
            arrayList.clear();
            arrayList.add(new Coordinate2D(4, 2));
            Submarine submarine2 = new Submarine(arrayList);
            arrayList.clear();
            arrayList.add(new Coordinate2D(4, 3));
            Submarine submarine3 = new Submarine(arrayList);
            arrayList.clear();
            arrayList.add(new Coordinate2D(4, 4));
            Submarine submarine4 = new Submarine(arrayList);

            BattleshipMap battleshipMap = new BattleshipMap(battleship, cruiser1, cruiser2, destroyer1, destroyer2, destroyer3, submarine1, submarine2, submarine3, submarine4);

            Socket socket = new Socket(InetAddress.getByName("localhost"), Server.PORT);
            Scanner scanner = new Scanner(System.in);

            BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            System.out.print("Dobrodosli, unesite vase ime: ");

            String name = scanner.nextLine();

            Login login = new Login(name);

            System.out.println("Saljem prijavu serveru");

            bufferedWriter.write(login.toString() + "\n");
            bufferedWriter.flush();

            System.out.println(bufferedReader.readLine());
            System.out.println(bufferedReader.readLine());

            while (true) {
                String response = bufferedReader.readLine();

                if (response.startsWith("Izaberi")) {
                    System.out.println("Ciljaj kordinate");
                    System.out.print("x: ");
                    int x = scanner.nextInt();
                    System.out.print("y: ");
                    int y = scanner.nextInt();

                    Hit hit = new Hit(x, y);

                    bufferedWriter.write(hit.toString() + "\n");
                    bufferedWriter.flush();

                    String odgovor = bufferedReader.readLine();

                    System.out.println(odgovor);
                } else if (response.startsWith("Odgovori")) {
                    XMLDecoder decoder = new XMLDecoder(new ByteArrayInputStream(bufferedReader.readLine().getBytes()));
                    Object object = decoder.readObject();
                    decoder.close();
                    Hit hit;
                    if (object instanceof Hit) {
                        hit = (Hit) object;
                    } else
                        return;

                    System.out.println("Tvoj protivnik je gadjao (" + hit.x + ", " + hit.y + ")");

                    AttackResult attackResult = battleshipMap.underAttack(new Coordinate2D(hit.x, hit.y));

                    String result = "NISTA";

                    if (attackResult == AttackResult.MISS) {
                        System.out.println("Nije pogodio nista");
                    } else if (attackResult == AttackResult.HIT) {
                        System.out.println("Pogodio je deo broda");
                        result = "DEO";
                    } else {
                        System.out.println("Unistio je ceo brod");
                        result = "CEO";
                    }

                    if (!battleshipMap.hasHealthyShip())
                        result = "KRAJ";

                    bufferedWriter.write(result + "\n");
                    bufferedWriter.flush();
                } else if (response.startsWith("KRAJ")) {
                    System.out.println(response);
                    break;
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
