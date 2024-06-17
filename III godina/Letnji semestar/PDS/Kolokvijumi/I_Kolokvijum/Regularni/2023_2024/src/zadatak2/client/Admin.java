package zadatak2.client;

import zadatak2.protocol.IAdmin;
import zadatak2.server.Server;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Scanner;

public class Admin {
    public static void main(String[] args) {
        try {
            IAdmin admin = (IAdmin) Naming.lookup("rmi://localhost:" + Server.PORT + "/WebService");

            Scanner scanner = new Scanner(System.in);

            while (true) {
                System.out.println("Dobrodosli, admin");
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

                System.out.println("Menjam matricu");

                admin.ChangeMatrix(mat);

                System.out.println("Matrica je promenjena");
            }
        } catch (NotBoundException | MalformedURLException | RemoteException e) {
            throw new RuntimeException(e);
        }
    }
}
