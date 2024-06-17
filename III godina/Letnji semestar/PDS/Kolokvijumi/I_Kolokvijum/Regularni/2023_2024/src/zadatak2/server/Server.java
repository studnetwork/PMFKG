package zadatak2.server;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {
    public final static int PORT = 1234;

    public static void main(String[] args) {
        try {
            WebService webService = new WebService();

            LocateRegistry.createRegistry(PORT);
            Naming.rebind("//localhost:" + PORT + "/WebService", webService);
        } catch (RemoteException | MalformedURLException e) {
            e.printStackTrace();
        }

    }
}
