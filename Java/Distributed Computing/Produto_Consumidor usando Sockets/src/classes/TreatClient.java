
package classes;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Random;

public class TreatClient implements Runnable {
    
    private Socket client;
    private final Buffer buffer;
    private int item;
    private String message;
    
    public TreatClient(Socket client, Buffer buffer) {
        this.client = client;
        this.buffer = buffer;
        this.item = 0;
        this.message = "";
    }
    
    public void produce(int data) throws InterruptedException {
        
        try {
            
            Random generator = new Random();
            synchronized(buffer) {

                OutputStream out = client.getOutputStream();
                String response = "";
                byte[] data_sent;
                
                if(buffer.isFull()) {

                    response = "0;0;2;" + data;
                    
                    data_sent = response.getBytes();
                    out.write(data_sent);
                    out.flush();

                } else {
                
                    buffer.add(data);
                    
                    response = "1;1;1;" + data;

                    data_sent = response.getBytes();
                    out.write(data_sent);
                    out.flush();  
                }       
                 
            } 
            
        } catch (Exception erro) {
            System.out.println("ERRO: " + erro.getMessage());
        }
        
    }

    public void consume() throws InterruptedException {
        
        try {
            
            synchronized(buffer) {

                OutputStream out = client.getOutputStream();
                String response = "";
                byte[] data_sent;
                
                if(buffer.isEmpty()) {

                    response = "2;2;5;-1";
                    
                    data_sent = response.getBytes();
                    out.write(data_sent);
                    out.flush();                

                } else {

                    item = buffer.remove();
                    
                    response = "2;2;4;" + item;
                    
                    data_sent = response.getBytes();
                    out.write(data_sent);
                    out.flush();         

                }
            }
        
        } catch (Exception erro) {
            System.out.println("ERRO: " + erro.getMessage());
        }
    }
    
    @Override
    public void run() {
        
        try {
            InputStream input = client.getInputStream();
            byte[] data_received = new byte[20];
            
            input.read(data_received);
            message = new String(data_received);
            
            System.out.println("Message received: " + message);
            
            String[] split_message = message.split(";");
                   
            if(split_message[1].equals("1")) {
            
                produce(Integer.parseInt(split_message[3].trim()));
            
            } else {
            
                consume();
                
            }
            
        } catch(Exception erro) {
            System.out.println("Erro: " + erro.getMessage());
            erro.printStackTrace();
        }
    }    
}
