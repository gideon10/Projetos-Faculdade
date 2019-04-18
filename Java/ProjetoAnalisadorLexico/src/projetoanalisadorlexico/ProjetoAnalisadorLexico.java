package projetoanalisadorlexico;

public class ProjetoAnalisadorLexico {

    public static void main(String[] args) {
        AnalisadorLexico lex= new AnalisadorLexico("/home/oem/Desktop/Puc/Compiladores/ProjetoAnalisadorLexico/file/fonte.txt");
        
        lex.exibirListaTokens();
        lex.exibirTabelaDeSimbolos();
    } 
}
