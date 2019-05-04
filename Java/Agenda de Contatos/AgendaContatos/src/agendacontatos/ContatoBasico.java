package agendacontatos;

import java.util.ArrayList;

abstract public class ContatoBasico {
    
    protected String nome;
    protected ArrayList<Telefone> telefones;

    public ContatoBasico() {
        nome= "";
        telefones= new ArrayList<>();
    }

    public ContatoBasico(String nome) {
        this.nome = nome;
        this.telefones = new ArrayList<>();
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getDados() {
        String str= "Nome: " + nome + "\n";
        for(Telefone tf : telefones) {
            str += tf.getTelefone() + "\n";
        }
        return str;
    }

    public void setTelefone(Telefone telefone) {
        telefones.add(telefone);
    }
    
}
