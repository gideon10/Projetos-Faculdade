/*
   GRAMATICA CMPUC:
   
   PROGRAMA --------->  LISTA_INSTRUÇÕES
   LISTA_INSTRUÇÕES ->  INSTRUÇÃO ; LISTA_INSTRUÇÕES | E (ÉPSILON)
   INSTRUÇÃO -------->  ID = EXPRESSÃO
             -------->  ESCREVA(EXPRESSÃO)
             -------->  LEIA (ID)
   EXPRESSÃO -------->  TERMO RESTO1
   RESTO1 ----------->  +TERMO RESTO1 | -TERMO RESTO1 | E (ÉPSILON)
   TERMO ------------>  FATOR RESTO2
   RESTO2 ----------->  *FATOR RESTO2 | /FATOR RESTO2 | %FATOR RESTO2 | E (ÉPSILON)
   FATOR ------------>  BASE RESTO3 | (EXPRESSÃO)
   RESTO3 ----------->  ^EXPOENTE | E (ÉPSILON)
   BASE ------------->  ID | NUM
   EXPOENTE --------->  ID | NUM

*/


import java.util.Iterator;
import java.util.List;

public class Parser {
    
    private String input;
    private Lexer lex;
    private List<Token> listTokens;
    private Iterator<Token> it;
    private Token token;
    
    public Parser() { 
        input= ""; 
        lex= null;
        listTokens= null;
        it= null;
    }
    
    public Parser(String in) {
        input= in;
        lex= new Lexer(in);
        listTokens= lex.getListaTokens();
        it= listTokens.iterator();
    }
    
    private void proxToken() {
        if(it.hasNext()) {
            token= it.next();
        }
    }
    
    public void executeParser() {
        try {
            proxToken();
            listaInstrucoes();
        } catch(Exception e){
            e.printStackTrace();
            System.out.println(e.getMessage());
        }
    }
    
    private void listaInstrucoes() throws Exception {
        try {
            instrucao();
            if(token.getValor().equals(";")) {
                if(it.hasNext()) {
                    proxToken();
                    listaInstrucoes();
                } else {
                    System.out.println("\nAnálise sintática realizada com sucesso!");
                }
            } else {
                throw new Exception("ERRO SINTÁTICO: Delimitador ';' não encontrado!");
            }
        } catch(Exception e){
            throw e;
        }
    }
    
    private void instrucao() throws Exception {
        try {
            if(token.getTipo() == TipoToken.ID) {
                proxToken();
                if(token.getValor().equals("=")) {
                    proxToken();
                    expressao();
                } else { 
                    throw new Exception("ERRO SINTÁTICO: Operador de atribuição '=' não encontrado!");
                }    
            } else if(token.getTipo() == TipoToken.ESCREVA) {
                proxToken();
                if(token.getValor().equals("(")) {
                    proxToken();
                    expressao();
                    if(token.getValor().equals(")")) {
                        proxToken();
                    } else {
                        throw new Exception("ERRO SINTÁTICO: Delimitador ')' não encontrado!");
                    }
                } else {
                    throw new Exception("ERRO SINTÁTICO: Delimitador '(' não encontrado!");
                }
            } else if(token.getTipo() == TipoToken.LEIA) {
                proxToken();
                if(token.getValor().equals("(")) {
                    proxToken();
                    if(token.getTipo() == TipoToken.ID) {
                        proxToken();
                        if(token.getValor().equals(")")) {
                            proxToken();
                        } else {
                            throw new Exception("ERRO SINTÁTICO: Delimitador ')' não encontrado!");
                        }
                    } else {
                        throw new Exception("ERRO SINTÁTICO: ID não encontrado!");
                    }
                } else {
                    throw new Exception("ERRO SINTÁTICO: Delimitador '(' não encontrado!");
                }
            } else {
                throw new Exception("ERRO SINTÁTICO: Instrução inválida!");
            }
        } catch(Exception e) {
            throw e;
        }
    }
    
    private void expressao() throws Exception {     
        try {
            termo();
            resto1();
        } catch(Exception e) {
            throw e;
        }
    }
    
    private void resto1() throws Exception {
        try {
            if(token.getValor().equals("+") || token.getValor().equals("-")) {
                proxToken();
                termo();
                resto1();
            } //else --> EPSILON 
        } catch(Exception e) {
            throw e;
        }
    }

    private void termo() throws Exception {
        try {
            fator();
            resto2();
        } catch(Exception e) {
            throw e;
        }
    }
    
    private void resto2() throws Exception {
        try {
            if(token.getValor().equals("*") || token.getValor().equals("/") || token.getValor().equals("%")) {
                proxToken();
                fator();
                resto2();
            } //else --> EPSILON       
        } catch(Exception e) {
            throw e;
        }
    }
    
    private void fator() throws Exception {
        try {                    
            if(token.getValor().equals("(")) {
                proxToken();
                expressao();
                if(token.getValor().equals(")")) {
                    proxToken();
                } else {
                    throw new Exception("ERRO SINTÁTICO: Delimitador ')' não encontrado!");
                }
            } else {
                base();
                resto3();
            }
        } catch(Exception e) {
            throw e;
        }
    }
    
    private void resto3() throws Exception {
        try {
            if(token.getValor().equals("^")) {
                proxToken();
                expoente();
            } //else --> EPSILON
        
        } catch(Exception e) {
            throw e;
        }
    }
    
    private void base() throws Exception {
        try {
            if(token.getTipo() == TipoToken.ID || token.getTipo() == TipoToken.NUM) {
                proxToken();
            } else {
                throw new Exception("ERRO SINTÁTICO: Base não é identificador e nem número!");
            }    
        } catch(Exception e) {
            throw e;
        }
    }
    
    private void expoente() throws Exception {
        try {                    
            if(token.getTipo() == TipoToken.ID || token.getTipo() == TipoToken.NUM) {
                proxToken();
            } else {
                throw new Exception("ERRO SINTÁTICO: Expoente não é identificador e nem número!");
            }      
        } catch(Exception e) {
            throw e;
        }
    }
}
