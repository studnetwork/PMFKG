package zadatak2.client;

import zadatak2.protocol.IClient;
import zadatak2.server.Server;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.sql.SQLOutput;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try {
            IClient client = (IClient) Naming.lookup("rmi://localhost:" + Server.PORT + "/WebService");

            Scanner scanner = new Scanner(System.in);

            while (true) {
                System.out.println("Dobrodosli, klijent");
                System.out.print("Unesi broj kolona: ");
                int m = scanner.nextInt();
                System.out.print("Unesi broj vrsta: ");
                int n = scanner.nextInt();

                int[][] mat = new int[m][n];

                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        System.out.print("Unesi mat[" + i + "][" + j + "] (CEO BROJ): ");

                        mat[i][j] = scanner.nextInt();
                    }
                }

                int[][] result = client.multiply(mat);

                System.out.println("Rezultujuca matrica: ");

                for (int i = 0; i < result.length; i++) {
                    for (int j = 0; j < result[i].length; j++) {
                        System.out.print(result[i][j] + " ");
                    }

                    System.out.println();
                }
            }
        } catch (NotBoundException | MalformedURLException | RemoteException e) {
            e.printStackTrace();
        }
    }
}
