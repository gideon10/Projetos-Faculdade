package agendacontatos;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class Agenda {
    
    private ArrayList<ContatoBasico> contatos;
    
    public Agenda() {
        contatos= new ArrayList<>();
    }
    
    public void inserir(ContatoBasico con) {
        contatos.add(con);
    }
    
    public ContatoBasico buscarNome(String nome) {
        for(ContatoBasico con : contatos) {
            if(con.getNome().equalsIgnoreCase(nome)) {
                return con;
            }
        }
        return null;
    }
    
    public ContatoBasico buscarEmail(String email) {
        for(ContatoBasico con : contatos) {
            if(con instanceof EContato) {
                EContato econ= (EContato) con;
                if(econ.getEmail().equalsIgnoreCase(email)) {
                    return econ;
                }
            }       
        }
        return null;
    }
    
    public void listarContatos() {
        Collections.sort(contatos, new Comparator<ContatoBasico>() {
            @Override
            public int compare(ContatoBasico o1, ContatoBasico o2) {
                return o1.getNome().compareToIgnoreCase(o2.getNome());
            }        
        });
        
        System.out.println("Todos os contatos na agenda:\n");
        for(ContatoBasico con : contatos) {
            System.out.println(con.getDados() + "\n");
        }
    }
    
}
