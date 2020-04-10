package classes;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class Consumer implements Runnable {
    
    public Consumer() {}
    
    public void consume() {
    
        try {
        
            Registry registry = LocateRegistry.getRegistry("localhost", 1234);
            BufferRemote stub = (BufferRemote) registry.lookup("buffer");
            
            int item;
            while(true) {
                
                item = stub.remove();
                if(item == -1) {
                    System.out.println("Empty buffer \t Consumer (" + Thread.currentThread().getId() + ") tried to consume!\n");
                } else {
                    System.out.println("Buffer with items \t Consumer (" + Thread.currentThread().getId() + ") consumed item " + item + "!\n");
                }
                
                Thread.sleep(1000); // Aguarda por 1 segundo.
            }
        
        } catch(Exception ex) {
            System.out.println("Consumer exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    
    }

    @Override
    public void run() {
        consume();
    }
    
    public static void main(String[] args) {
        
        int M; // amount consumers.
        
        Scanner in = new Scanner(System.in);
        System.out.print("Amount consumers: ");
        M = in.nextInt();
        
        System.out.println("\nStatus \t\t\t Action\n");
        
        Thread[] consumers = new Thread[M];
        for(int i=0; i<M; i++) {
            consumers[i] = new Thread(new Consumer());
            consumers[i].start();
        }
        
    }
    
}
