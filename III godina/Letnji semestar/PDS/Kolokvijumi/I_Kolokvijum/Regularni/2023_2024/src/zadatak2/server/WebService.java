package zadatak2.server;

import zadatak2.protocol.IClient;
import zadatak2.protocol.IAdmin;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class WebService extends UnicastRemoteObject implements IAdmin, IClient {
    private int[][] matrix = {
            {1, 1, 1},
            {1, 1, 1},
            {1, 1, 1}
    };

    protected WebService() throws RemoteException {

    }

    @Override
    public void ChangeMatrix(int[][] matrix) throws RemoteException {
        synchronized (this.matrix) {
            this.matrix = matrix;

            System.out.println("Matrica je promenjena");
        }
    }

    @Override
    public int[][] multiply(int[][] matrix) throws RemoteException {
        synchronized (this.matrix) {
            System.out.println("Pocinjem sa racunanjem...");

            int[][] mat = new int[matrix.length][matrix[0].length];

            for (int i = 0; i < matrix.length; i++)
                for (int j = 0; j < matrix[i].length; j++)
                    mat[i][j] = this.matrix[i][j] + matrix[i][j];

            System.out.println("Zavrseno sa racunanjem");

            return mat;
        }
    }
}
