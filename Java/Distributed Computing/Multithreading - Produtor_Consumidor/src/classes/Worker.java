package classes;

import java.util.Random;

public class Worker implements Runnable {
    
    private final Buffer buffer;
    private int item;
    
    public Worker(Buffer buffer) {
        this.buffer = buffer;
        this.item = 0;
    }
    
    public void produce() throws InterruptedException {
                   
        Random generator = new Random();
        synchronized(buffer) {

            while(buffer.isFull()) {
                System.out.println("\nWorker (" + Thread.currentThread().getId() + ") - tried to produce." + " \t " + buffer.getState());
                buffer.wait();
            }
            
            
            item = generator.nextInt(101);
            buffer.add(item);
            System.out.println("\nWorker (" + Thread.currentThread().getId() + ") - Produced: " + item + " \t\t " + buffer.getState());

            buffer.notifyAll();
        } 
        
        int interval = (generator.nextInt(5) + 1) * 1000;
        
        Thread.sleep(interval);
    }

    @Override
    public void run() {
        
        while(true) {
            
            try {
                produce();
                
            } catch (InterruptedException ex) {
                System.out.println("W-Error: " + ex.getMessage());
                ex.printStackTrace();
            }
        }
    }
    
}
