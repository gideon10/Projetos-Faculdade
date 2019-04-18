
public class TestParser {
    
    public static void main(String[] args) {
        
        Lexer lex= new Lexer("/home/oem/Desktop/Puc/Compiladores/AnalisadorSintatico/file/test.txt");
       
        System.out.println("Executa Lexer!\n");
        lex.exibirListaTokens();
        
        System.out.println("Executa Parser!");
        Parser pars= new Parser("/home/oem/Desktop/Puc/Compiladores/AnalisadorSintatico/file/test.txt"); 
        pars.executeParser();
    }
}
