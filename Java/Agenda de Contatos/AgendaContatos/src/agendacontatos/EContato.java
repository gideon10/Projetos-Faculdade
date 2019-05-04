package agendacontatos;

import java.util.Calendar;

public class EContato extends Contato {
    
    private String email;
    private String homepage;
    
    public EContato() {
    }

    public EContato(String email, String homepage, Calendar dtNascimento, String nome) {
        super(dtNascimento, nome);
        this.email = email;
        this.homepage = homepage;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getHomepage() {
        return homepage;
    }

    public void setHomepage(String homepage) {
        this.homepage = homepage;
    }

    @Override
    public String getDados() {
        return super.getDados() 
        + "\nEmail: " + email + "\n"
        + "Homepage: " + homepage; 
    }
}
