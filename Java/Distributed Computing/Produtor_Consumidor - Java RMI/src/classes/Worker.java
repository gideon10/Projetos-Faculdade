package classes;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Random;
import java.util.Scanner;

public class Worker implements Runnable {
    
    public Worker() {}
    
    public void produce() {
       
        try {
                    
            Registry registry = LocateRegistry.getRegistry("localhost", 1234);
            BufferRemote stub = (BufferRemote) registry.lookup("buffer");
            
            Random generator = new Random();
            int item;
            while(true) {
            
                item = generator.nextInt(101);
                if(stub.add(item)) {
                    System.out.println("Buffer available \t Worker (" + Thread.currentThread().getId() + ") produced item " + item + "!\n");
                } else {
                    System.out.println("Buffer full \t Worker (" + Thread.currentThread().getId() + ") tried to produce!\n");
                }
                
                Thread.sleep(1000); // Aguarda por 1 segundo.
            }
        
        
        } catch(Exception ex) {
            System.out.println("Worker exception: " + ex.getMessage());
            ex.printStackTrace();
        }
    }
    
    @Override
    public void run() {
        produce();
    }
    
    public static void main(String[] args) {
        
        int N; // amount workers.
        
        Scanner in = new Scanner(System.in);
        System.out.print("Amount workers: ");
        N = in.nextInt();
        
        System.out.println("\nStatus \t\t\t\t Action\n");
        
        Thread[] workers = new Thread[N];
        for(int i=0; i<N; i++) {
            workers[i] = new Thread(new Worker());
            workers[i].start();
        }
        
    }
    
}
