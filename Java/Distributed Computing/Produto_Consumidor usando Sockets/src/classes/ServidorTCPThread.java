package classes;

import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class ServidorTCPThread {
    
    public static void main(String[] args) throws Exception {
        
        int C; // buffer's capacity.
        
        Scanner in = new Scanner(System.in);        
        System.out.print("Buffer's capacity: ");
        C = in.nextInt();
        
        ServerSocket server = new ServerSocket(7777); // Servidor escutando a porta 7777...
        Buffer buffer = new Buffer(C);
        
        while(true) {
        
            Socket client = server.accept(); // O método accept() bloqueia a execução até que o servidor receba um pedido de conexão do cliente.

            Thread thread = new Thread(new TreatClient(client, buffer));
            thread.start();
        }
    }
}
