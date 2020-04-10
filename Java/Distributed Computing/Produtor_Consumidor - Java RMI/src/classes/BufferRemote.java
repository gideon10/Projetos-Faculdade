package classes;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface BufferRemote extends Remote {
    
    public boolean add(int item) throws RemoteException;
    public int remove() throws RemoteException; 
    
}
