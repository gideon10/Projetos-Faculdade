package classes;

import java.rmi.RemoteException;
import java.util.concurrent.LinkedBlockingQueue;

public class BufferRemoteImpl implements BufferRemote {

    private final LinkedBlockingQueue<Integer> buffer_queue;
    private int capacity;
    
    public BufferRemoteImpl(int capacity) {
        this.capacity = capacity;
        buffer_queue = new LinkedBlockingQueue<>(this.capacity);
    }
    
    @Override
    public boolean add(int item) throws RemoteException {

        synchronized(buffer_queue) {
        
            if (buffer_queue.size() < capacity) {
                buffer_queue.add(item);
                return true;
            }

            return false;
        }
    }

    @Override
    public int remove() throws RemoteException {

        synchronized(buffer_queue) {
            if (!buffer_queue.isEmpty()) {
                return buffer_queue.remove();
            }

            return -1;
        }
    }
    
}
