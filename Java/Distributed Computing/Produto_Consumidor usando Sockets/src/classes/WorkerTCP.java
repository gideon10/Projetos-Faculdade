package classes;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Random;
import java.util.Scanner;

public class WorkerTCP implements Runnable {
    
    private int id;
    private String server;
    private int port;
    private String message;
    private Socket server_connection;
    
    public WorkerTCP(int id, String server, int port) {
        this.id = id;
        this.server = server;
        this.port = port;
        this.message = "";
    }
    
    @Override
    public void run() {
        
        try {
            //server_connection = new Socket(server, port);

            Random generator = new Random();
            InputStream input;
            OutputStream out;
            byte[] data_received;
            String[] split_message;
            while(true) {
                
                server_connection = new Socket(server, port);

                message = "1;1;0;" + generator.nextInt(101);
                out = server_connection.getOutputStream();

                byte[] data_sent = message.getBytes();
                out.write(data_sent);
                out.flush();

                input = server_connection.getInputStream();
                data_received = new byte[20];
            
                input.read(data_received);
                message = new String(data_received);

                split_message = message.split(";");
                
                if(split_message[2].equals("1")) {
                    
                    System.out.println("Worker (" + this.id + "): produced " + split_message[3].trim() + " \t ARMAZENAMENTO OK!\n");
                
                } else {
                 
                    System.out.println("Worker (" + this.id + "): tried to produce " + split_message[3].trim() + " \t ARMAZENAMENTO ERRO!\n");
                    
                }
                
                Thread.sleep(1000); // Aguarda por 1 segundo.
            
            }    
            
        } catch(Exception erro) {
            System.out.println("ERRO: " + erro.getMessage());
            erro.printStackTrace();
        }

    }
    
    public static void main(String[] args) {
        
        int N; // amount workers.
        String server = "127.0.0.1";
        int port = 7777;
        
        Scanner in = new Scanner(System.in);
        System.out.print("Amount workers: ");
        N = in.nextInt();
        
        Thread[] workers = new Thread[N];
        for(int i=0; i<N; i++) {
            workers[i] = new Thread(new WorkerTCP(i+1, server, port));
            workers[i].start();
        }
        
    }
}
