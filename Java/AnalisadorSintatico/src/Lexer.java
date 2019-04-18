import static java.lang.Character.isDigit;
import static java.lang.Character.isLetter;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.List;

enum TipoToken { ID, NUM, OPR_AR, OPR_RL, OPR_LOG, DELIM, IF, ELSE, WHILE, ATRIB, ESCREVA, LEIA };

public class Lexer {
        
    private String nomeArquivo;
    private List<Token> listTokens;
    Hashtable<String,Integer> Identificadores;
    
    public Lexer() {
        nomeArquivo="";
    }

    public Lexer(String nomeArquivo) {
        this.nomeArquivo = nomeArquivo;
        listTokens= new ArrayList<>();
        Identificadores= new Hashtable<>();
    }
    
    public List<Token> getListaTokens() {
        if(listTokens.isEmpty()) {
            scanner();
        } 
        return listTokens;
    }
    
    public Hashtable<String,Integer> getTabIdentificadores() {
        if(listTokens.isEmpty()) {
            scanner();
        }
        return Identificadores;
    }
    
    private void scanner() {
        try(FileReader fr= new FileReader(new File(nomeArquivo));
            BufferedReader br= new BufferedReader(fr)) {
        
            String linha;
            while((linha= br.readLine()) != null) {
                String token;
                String opr_ar="+*/%^", opr_rel= "<>=!", delim="(),;.", simbols_nPermitidos="“#$&‘:?@[]_` ";
                int i= 0;
                while(i < linha.length()) {
                    
                    while(i<linha.length() && (linha.charAt(i)>122 || linha.charAt(i)==92 || simbols_nPermitidos.contains(Character.toString(linha.charAt(i)))))    
                        i++;	
                    
                    if(i<linha.length() && isLetter(linha.charAt(i))) { 
                        // começa com letra
                        token= "";
                        token+= linha.charAt(i);
                        i++;
                        while(i<linha.length() && (isLetter(linha.charAt(i)) || isDigit(linha.charAt(i)))) { 
                            token+= linha.charAt(i);
                            i++;
                        }
                        // Verifica se o token é uma palavra reservada ou um identificador.            
                        switch (token) {
                            case "and":     listTokens.add(new Token(TipoToken.OPR_LOG, token));
                                            break;
                            case  "or":     listTokens.add(new Token(TipoToken.OPR_LOG, token));
                                            break;
                            case "not":     listTokens.add(new Token(TipoToken.OPR_LOG, token));
                                            break;
                            case  "if":     listTokens.add(new Token(TipoToken.IF, ""));
                                            break;
                            case  "else":   listTokens.add(new Token(TipoToken.ELSE, ""));
                                            break;
                            case "while":   listTokens.add(new Token(TipoToken.WHILE, ""));
                                            break;
                            case "escreva": listTokens.add(new Token(TipoToken.ESCREVA, ""));
                                            break;
                            case "leia":    listTokens.add(new Token(TipoToken.LEIA, ""));
                                            break;
                            default:        listTokens.add(new Token(TipoToken.ID, token));
                                            Identificadores.put(token, 0);        
                        }
                    }

                    if(i<linha.length() && isDigit(linha.charAt(i))) {
                        token= "";
                        while(i<linha.length() && isDigit(linha.charAt(i))) { 
                            token+= linha.charAt(i);
                            i++;
                        }
                        if(i<linha.length() && !token.isEmpty() && linha.charAt(i) == '.') {
                            token+= '.';
                            i++;
                            while(i<linha.length() && isDigit(linha.charAt(i))) {
                                token+= linha.charAt(i);
                                i++;
                            }
                        }                
                        listTokens.add(new Token(TipoToken.NUM, token));
                    }
                                        
                    if(i<linha.length() && linha.charAt(i) == '-') {                        
                        /*token= "-";
                        Token prevToken= listTokens.get(listTokens.size()-1);  // Token anterior.
                        if(prevToken.getTipo() == TipoToken.ID || prevToken.getTipo() == TipoToken.NUM || prevToken.getValor().equals(")")) {
                            listTokens.add(new Token(TipoToken.OPR_AR, "-")); 
                            i++;
                        } else {
                            i++;
                            while(i<linha.length() && isDigit(linha.charAt(i))) {
                                token+= linha.charAt(i);
                                i++;
                            }
                            if(i<linha.length() && !token.equals("-") && linha.charAt(i) == '.') {
                                while(i<linha.length() && isDigit(linha.charAt(i))) {
                                    token+= linha.charAt(i);
                                    i++;
                                }
                            }
                            else if(token.equals("-")) {
                                listTokens.add(new Token(TipoToken.OPR_AR, "-")); 
                            }
                            else {
                                listTokens.add(new Token(TipoToken.NUM, token));
                            }
                        } */
                        token= "-";
                        boolean ok= true;
                        if(listTokens.size() > 0) {
                            Token prevToken= listTokens.get(listTokens.size()-1);  // Token anterior.
                            if(prevToken.getTipo() == TipoToken.ID || prevToken.getTipo() == TipoToken.NUM || prevToken.getValor().equals(")")) {
                                listTokens.add(new Token(TipoToken.OPR_AR, "-")); 
                                i++;
                                ok= false;
                            }
                        }
                        
                        if(ok) {
                            i++;
                            while(i<linha.length() && isDigit(linha.charAt(i))) {
                                token+= linha.charAt(i);
                                i++;
                            }
                            if(i<linha.length() && !token.equals("-") && linha.charAt(i) == '.') {
                                while(i<linha.length() && isDigit(linha.charAt(i))) {
                                    token+= linha.charAt(i);
                                    i++;
                                }
                            }
                            else if(token.equals("-")) {
                                listTokens.add(new Token(TipoToken.OPR_AR, "-")); 
                            }
                            else {
                                listTokens.add(new Token(TipoToken.NUM, token));
                            }
                        }
                    }

                    if(i<linha.length() && opr_ar.contains(Character.toString(linha.charAt(i)))) { // Verifica operadores aritméticos
                        listTokens.add(new Token(TipoToken.OPR_AR, Character.toString(linha.charAt(i))));
                        i++;
                    }
                    
                    if(i<linha.length() && delim.contains(Character.toString(linha.charAt(i)))) { // Verifica demilitadores
                        listTokens.add(new Token(TipoToken.DELIM, Character.toString(linha.charAt(i))));
                        i++;
                    }
           
                    for(int j=0; j<opr_rel.length(); j++) { // Verifica operadores relacionais e de atribuição
                        if(i<linha.length() && opr_rel.contains(Character.toString(linha.charAt(i)))) {
                            token= Character.toString(linha.charAt(i));
                            i++;
                            if(i<linha.length() && linha.charAt(i) == '=') {
                                token+= "=";
                                i++;
                            }
                            if(!token.equals("!")) {
                                if(!token.equals("=")) 
                                    listTokens.add(new Token(TipoToken.OPR_RL, token)); 
                                else 
                                    listTokens.add(new Token(TipoToken.ATRIB, token)); 
                            }
                        }
                    }
                
                }
            }
            
        } catch(IOException ex) {
            System.out.println("Erro na leitura do arquivo!\nErro: " + ex.getMessage());
        }
    }    
    
    public void exibirListaTokens() {
        if(listTokens.isEmpty()) {
            scanner();
        }
        System.out.println("Lista de tokens reconhecidos:\n");
        for(int i=0; i<listTokens.size(); i++) {
            System.out.println("Tipo: " + listTokens.get(i).getTipo());
            System.out.println("Valor: " + listTokens.get(i).getValor());
            System.out.println("\n");
        } 
    }
}
