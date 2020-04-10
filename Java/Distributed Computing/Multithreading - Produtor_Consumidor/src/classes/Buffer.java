package classes;

import java.util.concurrent.LinkedBlockingQueue;

public class Buffer {
    
    private final int capacity;   
    private LinkedBlockingQueue<Integer> buffer_lbq;
    public int item;

    public Buffer(int capacity) {
        this.capacity = capacity;
        this.buffer_lbq = new LinkedBlockingQueue<>(this.capacity);
    }
    
    public boolean isFull() {
        return (this.buffer_lbq.remainingCapacity() == 0);
    }
    
    public boolean isEmpty() {
        return buffer_lbq.isEmpty();
    }
    
    public String getState() {
        if(this.isFull()) {
            return "full!";
        }
        if(this.isEmpty()) {
            return "empty!";
        }
        return "with space!";
    }
    
    public void add(int value) {
        buffer_lbq.add(value);
    }
    
    public int remove() {
        return buffer_lbq.remove();
    }
}
