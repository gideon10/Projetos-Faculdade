/*
   GRAMATICA CMPUC v1.0:
   
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


import java.io.File;
import java.io.FileWriter;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Stack;

public class Parser {
    
    private String input;
    private Lexer lex;
    private List<Token> listTokens;
    private Iterator<Token> it;
    private Token token;
    private Stack stack;
    private String codeAssembly;
    private HashMap<String,Integer> hashVar;
    int pos; // índice de posição na memória
    
    public Parser() { 
        input= ""; 
        lex= null;
        listTokens= null;
        it= null;
        codeAssembly= "";
        pos= 0;
    }
    
    public Parser(String in) {
        input= in;
        lex= new Lexer(in);
        listTokens= lex.getListaTokens();
        it= listTokens.iterator();
        stack= new Stack();
        codeAssembly= "";
        hashVar= new HashMap<>();
        pos= 1;
    }
    
    private void proxToken() {
        if(it.hasNext()) {
            token= it.next();
        }
    }
    
    public void executeParser() {
        try (FileWriter fw= new FileWriter(new File("/home/oem/Desktop/Puc/Compiladores/Compilador/file/out.txt"))) {
            proxToken();
            listaInstrucoes();
            
            System.out.println("\nCódigo em Assembly gerado:\n\n" + codeAssembly);
            
            // GRAVA O CÓDIGO GERADO EM ASSEMBLY NO ARQUIVO out.txt.
            fw.write(codeAssembly);
            fw.flush();
            
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
                    System.out.println("\nCompilação realizada com sucesso!");
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
                    if(hashVar.containsKey(key)) {
                        codeAssembly += "pop r1\nstore r1," + hashVar.get(key) + "\n\n";
                    } else {
                        codeAssembly += "pop r1\nstore r1," + pos + "\n\n";
                        hashVar.put(key, pos);
                        pos++;
                    }                    
                } else { 
                    throw new Exception("ERRO SINTÁTICO: Operador de atribuição '=' não encontrado!");
                }    
            } else if(token.getTipo() == TipoToken.LEIA) {
                proxToken();
                if(token.getTipo() == TipoToken.ID) {
                    if(hashVar.containsKey(token.getValor())) {
                        codeAssembly += "read r1\nstore r1," + hashVar.get(token.getValor()) + "\n\n";
                    } else {
                        codeAssembly += "read r1\nstore r1," + pos + "\n\n";
                        hashVar.put(token.getValor(), pos);
                        pos++;
                    }                    
                    proxToken();
                } else {
                    throw new Exception("ERRO SINTÁTICO: ID não encontrado!");
                }
            } else if(token.getTipo() == TipoToken.ESCREVA) {
                proxToken();
                expressao();
                codeAssembly += "pop r1\nwrite r1\n\n";
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
                    codeAssembly += "pop r2\npop r1\nadd r3,r1,r2\npush r3\n";
                    resto1();
                } else {
                    proxToken();
                    termo();
                    codeAssembly += "pop r2\npop r1\nsub r3,r1,r2\npush r3\n";
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
                    codeAssembly += "pop r2\npop r1\nmul r3,r1,r2\npush r3\n";
                    resto2();
                } else if(token.getValor().equals("/")) {
                    proxToken();
                    fator();
                    codeAssembly += "pop r2\npop r1\ndiv r3,r1,r2\npush r3\n";
                    resto2();
                    
                } else { // %
                    proxToken();
                    fator();   
                    codeAssembly += "pop r2\npop r1\nmod r3,r1,r2\npush r3\n";
                    resto2();
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
                codeAssembly += "pop r2\npop r1\npot r3,r1,r2\npush r3\n";
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
                    if(hashVar.containsKey(token.getValor())) {
                        codeAssembly += "load r1," + hashVar.get(token.getValor()) + "\npush r1\n";
                    } else {
                        codeAssembly += "load r1," + pos + "\npush r1\n";
                        hashVar.put(token.getValor(), pos);
                        pos++;
                    }
                } else {
                    codeAssembly += "mov r1," + token.getValor() + "\npush r1\n";
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
