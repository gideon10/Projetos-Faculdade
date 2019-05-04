package agendacontatos;

public class ContatoComercial extends ContatoBasico {

    private String atividade;
    private String funcionario;

    public ContatoComercial(String atividade, String funcionario, String nome) {
        super(nome);
        this.atividade = atividade;
        this.funcionario = funcionario;
    }

    @Override
    public String getDados() {
        return super.getDados() 
        + "Atividade: " + atividade + "\n"
        + "Funcionário Sr(a): " + funcionario;
    }    
}
