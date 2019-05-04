package agendacontatos;

public class Telefone {
    
    private String numero;
    private String tipo;

    public Telefone() {
    }
    
    public Telefone(String numero, String tipo) {
        this.numero = numero;
        this.tipo = tipo;
    }

    public String getNumero() {
        return numero;
    }

    public void setNumero(String numero) {
        this.numero = numero;
    }

    public String getTipo() {
        return tipo;
    }

    public void setTipo(String tipo) {
        this.tipo = tipo;
    }
    
    public String getTelefone() {
        return tipo + ": " + numero;
    }
}
