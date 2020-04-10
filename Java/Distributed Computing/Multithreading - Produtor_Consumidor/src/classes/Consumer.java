package classes;

import java.util.Random;

public class Consumer implements Runnable {
        
    private final Buffer buffer;
    private int item;
    public static boolean flag;
    
    public Consumer(Buffer buffer) {
        this.buffer = buffer;
        item = 0;
    }
    
    public void consume() throws InterruptedException {
        
        synchronized(buffer) {

            while(buffer.isEmpty()) {
                System.out.println("\nConsumer (" + Thread.currentThread().getId() + ") - tried to consume." + " \t " + buffer.getState());
                buffer.wait();
            }
            
            item = buffer.remove();
            System.out.println("\nConsumer (" + Thread.currentThread().getId() + ") - consumed: " + item + " \t\t " + buffer.getState());

            buffer.notifyAll();
        }
        
        Random generator = new Random();
        int interval = (generator.nextInt(5) + 1) * 1000;
        Thread.sleep(interval);
    }
    
    @Override
    public void run() {
        
        while(true) {
            try {
                consume();
                
            } catch (InterruptedException ex) {
                System.out.println("C-Error: " + ex.getMessage());
                ex.printStackTrace();
            }
        }
    }
}
