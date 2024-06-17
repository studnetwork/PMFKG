package zadatak2.protocol;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IAdmin extends Remote {
    void ChangeMatrix(int[][] matrix) throws RemoteException;
}
