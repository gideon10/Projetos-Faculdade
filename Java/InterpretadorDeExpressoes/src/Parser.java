/*
   GRAMATICA CMPUC:
   
   PROGRAMA --------->  LISTA_INSTRUÇÕES
   LISTA_INSTRUÇÕES ->  INSTRUÇÃO ; LISTA_INSTRUÇÕES | E (ÉPSILON)
   INSTRUÇÃO -------->  ID = EXPRESSÃO | LEIA ID | ESCREVA EXPRESSÃO
   EXPRESSÃO -------->  TERMO RESTO1
   RESTO1 ----------->  +TERMO RESTO1 | -TERMO RESTO1 | E (ÉPSILON)
   TERMO ------------>  FATOR RESTO2
   RESTO2 ----------->  *FATOR RESTO2 | /FATOR RESTO2 | %FATOR RESTO2 | E (ÉPSILON)
   FATOR ------------>  BASE RESTO3
   RESTO3 ----------->  ^EXPRESSÃO | E (ÉPSILON)
   BASE ------------->  ID | NUM | (EXPRESSÃO)

*/


import java.util.Iterator;
import java.util.List;
import java.util.Stack;
import java.util.Scanner;

public class Parser {
    
    private String input;
    private Lexer lex;
    private List<Token> listTokens;
    private Iterator<Token> it;
    private Token token;
    private Stack stack;
    
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
        stack= new Stack();
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
                String key= token.getValor();
                proxToken();
                if(token.getValor().equals("=")) {
                    proxToken();
                    expressao();
                    double valor= Double.parseDouble(stack.pop().toString());
                    lex.getTabIdentificadores().replace(key, valor);
                } else { 
                    throw new Exception("ERRO SINTÁTICO: Operador de atribuição '=' não encontrado!");
                }    
            } else if(token.getTipo() == TipoToken.LEIA) {
                proxToken();
                if(token.getTipo() == TipoToken.ID) {
                    System.out.print(token.getValor() + "<<");
                    Scanner entrada= new Scanner(System.in);
                    lex.getTabIdentificadores().replace(token.getValor(), entrada.nextDouble());
                    proxToken();
                } else {
                    throw new Exception("ERRO SINTÁTICO: ID não encontrado!");
                }
            } else if(token.getTipo() == TipoToken.ESCREVA) {
                proxToken();
                expressao();
                System.out.println(">>" + stack.pop().toString());
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
                if(token.getValor().equals("+")) {
                    proxToken();
                    termo();
                    double operador2= Double.parseDouble(stack.pop().toString());
                    double operador1= Double.parseDouble(stack.pop().toString());
                    double result= operador1 + operador2;
                    stack.push(result);
                    resto1();
                } else {
                    proxToken();
                    termo();
                    double operador2= Double.parseDouble(stack.pop().toString());
                    double operador1= Double.parseDouble(stack.pop().toString());
                    double result= operador1 - operador2;
                    stack.push(result);
                    resto1();
                }
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
                if(token.getValor().equals("*")) {
                    proxToken();
                    fator();
                    double operador2= Double.parseDouble(stack.pop().toString());
                    double operador1= Double.parseDouble(stack.pop().toString());
                    double result= operador1 * operador2;
                    stack.push(result);
                    resto2();
                } else if(token.getValor().equals("/")) {
                    proxToken();
                    fator();
                    double operador2= Double.parseDouble(stack.pop().toString());
                    if(operador2 == 0) {
                        throw new Exception("ERRO SEMÂNTICO: Divisão por zero!");
                    } else {
                        double operador1= Double.parseDouble(stack.pop().toString());
                        double result= operador1 / operador2;
                        stack.push(result);
                        resto2();
                    }
                } else {
                    proxToken();
                    fator();
                    double operador2= Double.parseDouble(stack.pop().toString());
                    if(operador2 == 0) {
                        throw new Exception("ERRO SEMÂNTICO: Divisão por zero!");
                    } else {
                        double operador1= Double.parseDouble(stack.pop().toString());
                        double result= operador1 % operador2;
                        stack.push(result);
                        resto2();
                    }  
                }
            } //else --> EPSILON       
        } catch(Exception e) {
            throw e;
        }
    }
    
    private void fator() throws Exception {
        try {                    
            base();
            resto3();
        } catch(Exception e) {
            throw e;
        }
    }
    
    private void resto3() throws Exception {
        try {
            if(token.getValor().equals("^")) {
                proxToken();
                expressao();
                double operador2= Double.parseDouble(stack.pop().toString());
                double operador1= Double.parseDouble(stack.pop().toString());
                double result= Math.pow(operador1, operador2);
                stack.push(result);
            } //else --> EPSILON
        } catch(Exception e) {
            throw e;
        }
    }
    
    private void base() throws Exception {
        try {
            if(token.getValor().equals("(")) {
                proxToken();
                expressao();
                if(token.getValor().equals(")")) {
                    proxToken();
                } else {
                    throw new Exception("ERRO SINTÁTICO: Delimitador ')' não encontrado!");
                }
            } else if(token.getTipo() == TipoToken.ID || token.getTipo() == TipoToken.NUM) {               
                if(token.getTipo() == TipoToken.ID) {
                    stack.push(lex.getTabIdentificadores().get(token.getValor()));
                } else {
                    stack.push(token.getValor());
                }
                proxToken();
            } else {
                throw new Exception("ERRO SINTÁTICO: Instrução inválida!");
            }
        } catch(Exception e) {
            throw e;
        }
    }
}
