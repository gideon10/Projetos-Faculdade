package agendacontatos;

import java.util.GregorianCalendar;

public class Main {

    public static void main(String[] args) {
        
        Agenda ag= new Agenda();

        Contato con= new Contato(new GregorianCalendar(2000, 8, 14), "José Santos");
        con.setTelefone(new Telefone("9999-9999", "Telefone residencial"));
        con.setTelefone(new Telefone("9989-0000", "Telefone celular"));
        
        ag.inserir(con);
        
        con= new Contato(new GregorianCalendar(1988, 5, 5), "André Silva");
        con.setTelefone(new Telefone("6565-9999", "Telefone residencial"));
        con.setTelefone(new Telefone("9989-1010", "Telefone celular"));
        
        ag.inserir(con);
                
        con= new Contato(new GregorianCalendar(1988, 5, 5), "Adolfo Silva");
        con.setTelefone(new Telefone("9999-1111", "Telefone residencial"));
        con.setTelefone(new Telefone("7744-0000", "Telefone celular"));
        
        ag.inserir(con);
        
        con= new Contato(new GregorianCalendar(1988, 5, 5), "Ferreira Silva");
        con.setTelefone(new Telefone("9999-9999", "Telefone residencial"));
        con.setTelefone(new Telefone("9989-0000", "Telefone celular"));
        
        ag.inserir(con);
        
        ContatoComercial cc= new ContatoComercial("Vendedor", "Antônio josé", "Lanchonete's Antônio");
        cc.setTelefone(new Telefone("5555-5555", "Telefone"));
        
        ag.inserir(cc);
        
        ag.inserir(new EContato("mario@gmail.com", "www.meusite.com.br", new GregorianCalendar(1964, 9, 4), "Mario alves"));
        
        ag.listarContatos();
    }
    
}
