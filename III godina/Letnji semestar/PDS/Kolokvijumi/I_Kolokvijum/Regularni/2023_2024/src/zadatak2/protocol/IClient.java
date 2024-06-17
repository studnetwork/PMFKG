package zadatak2.protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IClient extends Remote {
    int[][] multiply(int[][] matrix) throws RemoteException;
}
