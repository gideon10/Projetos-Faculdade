package test;

import classes.Buffer;
import classes.Consumer;
import classes.Worker;
import java.util.Scanner;

public class MultithreadingTest {
    public static void main(String[] args) {
        
        int N = 0; // amount workers.
        int M = 0; // amount consumers.
        int C = 0; // buffer's capacity.
        
        Scanner in = new Scanner(System.in);
        System.out.print("Amount workers: ");
        N = in.nextInt();
        System.out.print("Amount consumers: ");
        M = in.nextInt();
        System.out.print("Buffer's capacity: ");
        C = in.nextInt();
        
        Buffer bff = new Buffer(C);
        
        System.out.println("\nActions \t\t\t\t Buffer's state\n------------------------------------------------------------\n");
        
        Thread[] workers = new Thread[N];
        for(int i=0; i<N; i++) {
            workers[i] = new Thread(new Worker(bff));
            workers[i].start();
        } 
        
        Thread[] consumers = new Thread[M];
        for(int i=0; i<M; i++) {
            consumers[i] = new Thread(new Consumer(bff));
            consumers[i].start();
        }

    }
}
