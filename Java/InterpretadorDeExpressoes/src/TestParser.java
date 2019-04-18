
public class TestParser {
    
    public static void main(String[] args) {
        
        Lexer lex= new Lexer("/home/oem/Desktop/Puc/Compiladores/InterpretadorDeExpressoes/file/test.txt");
       
        System.out.println("Executando Lexer...\n");
        lex.exibirListaTokens();
        
        System.out.println("Executando Parser...  e Interpretando comandos...\n");
        Parser pars= new Parser("/home/oem/Desktop/Puc/Compiladores/InterpretadorDeExpressoes/file/test.txt"); 
        pars.executeParser();
    }
}
