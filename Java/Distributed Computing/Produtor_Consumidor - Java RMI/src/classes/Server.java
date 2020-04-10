package classes;

import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class Server {
    public static void main(String[] args) throws RemoteException {
        
        try {

            int C; // buffer's capacity.
            LocateRegistry.createRegistry(1234);
            Registry registry = LocateRegistry.getRegistry(1234);
        
            Scanner in = new Scanner(System.in);

            System.out.print("Buffer's capacity: ");
            C = in.nextInt();

            BufferRemoteImpl bff_remote = new BufferRemoteImpl(C);
            BufferRemote stub = (BufferRemote) UnicastRemoteObject.exportObject(bff_remote, 0);

            while(true) {

                registry.rebind("buffer", stub);

            }
        
        } catch(Exception ex) {
            System.out.println("Server exception: " + ex.getMessage());
            ex.printStackTrace();
        }
        
    }
}
