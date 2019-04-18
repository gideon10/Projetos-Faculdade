
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Stack;
import java.util.StringTokenizer;


public class MaquinaVirtual {
    
    private String nomeArquivo;
    
    private ArrayList<String> opAritLog; 
    private ArrayList<String> opDesv;
    private ArrayList<String> opMovDados;
    private ArrayList<String> opES;
    
    private HashMap<String, Double> registrador;
    private final int SIZE_MEMO= 1024;
    private int qtdInstrucoes;
    private double[] memoriaDados;
    private String[] memoriaInstrucoes;
    private String instrucaoAtual;
    Stack<Double> pilha;
    private int pc;
    
    public MaquinaVirtual() {
    
    }
   
    public MaquinaVirtual(String nomeArquivo) {
        this.nomeArquivo= nomeArquivo;
        opAritLog= new ArrayList<>(Arrays.asList("add", "sub", "mul", "div", "mod", "pot", "and", "or", "not"));  
        opDesv= new ArrayList<>(Arrays.asList("jump", "beq", "bne", "blt", "ble", "bgt", "bge"));
        opMovDados= new ArrayList<>(Arrays.asList("load", "store", "mov", "push", "pop"));
        opES= new ArrayList<>(Arrays.asList("read", "write")); 
        registrador = new HashMap<String,Double>() {{
            put("r0", 0.0);
            put("r1", 0.0);
            put("r2", 0.0);
            put("r3", 0.0);
            put("r4", 0.0);
            put("r5", 0.0);
            put("r6", 0.0);
            put("r7", 0.0);
            put("r8", 0.0);
            put("r9", 0.0);
        }};
        qtdInstrucoes= 0;
        memoriaDados= new double[SIZE_MEMO];
        memoriaInstrucoes= new String[SIZE_MEMO];
        pilha= new Stack<>();
        pc= 0;       
    }
    
    private void lerArquivo() {
        try(FileReader fr= new FileReader(new File(nomeArquivo));
            BufferedReader br= new BufferedReader(fr)) {
            
            int i= 0;
            String linha= "";
            while(i<SIZE_MEMO && (linha= br.readLine()) != null) {
                if(!linha.isEmpty()) {
                    memoriaInstrucoes[i]= linha;
                    i++;
                }
            }
            qtdInstrucoes= i;
        } catch(IOException ex) {
            System.out.println("Erro na leitura do arquivo!");
        }
    }
    
    private boolean isNumber(String str) {
        try {
            Double.parseDouble(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
    
    private void buscarInstrucao() {
        instrucaoAtual= memoriaInstrucoes[pc];
        pc++;
    }
    
    private void decodificarInstrucao() throws Exception {
        StringTokenizer lexer= new StringTokenizer(instrucaoAtual, " \t\n\r\f,;");
        try {
            
            if(lexer.countTokens() > 1 && lexer.countTokens() < 5) {       
                
                String opcode= lexer.nextToken();
                if(opAritLog.contains(opcode)) {
                    String regDest= lexer.nextToken();
                    if(!registrador.containsKey(regDest)) { throw new Exception("ERRO: Registrador de destino inválido!"); }
                    String regOp1= lexer.nextToken();
                    if(!registrador.containsKey(regOp1)) { throw new Exception("ERRO: Primeiro operando inválido!"); }
                    String regOp2= "";
                    if(!opcode.equals("not")) {
                        regOp2= lexer.nextToken();
                        if(!registrador.containsKey(regOp2) && !isNumber(regOp2)) { throw new Exception("ERRO: Segundo operando inválido!"); }
                    }
                    
                    System.out.println("\nOperador aritmético/lógico: " + opcode);
                    System.out.println("Reg. Destino: " + regDest);
                    System.out.println("Reg. Operando 1: " + regOp1);
                    System.out.println("Reg. Operando 2: " + regOp2);
                    System.out.print("Pressione ENTER para continuar...");
                    System.in.read();
                    
                    opAritLog(opcode,regDest, regOp1, regOp2);  

                } else if(opDesv.contains(opcode)) {
                                       
                    if(opcode.equals("jump")) { 
                        String pos= lexer.nextToken();
                        if(!isNumber(pos) || Integer.parseInt(pos) < 1 || Integer.parseInt(pos) > qtdInstrucoes) { throw new Exception("ERRO: Posição de memória inválida!"); }
                      
                        System.out.println("\nOperador de desvio: " + opcode);
                        System.out.println("Posicao de desvio: " + pos);
                        System.out.print("Pressione ENTER para continuar...");
                        System.in.read();
                        
                        pc= Integer.parseInt(pos);  // Salta para a posição de memória especificada. 
                        pc--; // Decrementa porque a memóriaDeInstruções(vetor) começa da posição 0. 
                    } else {
                        String regOp1= lexer.nextToken();
                        if(!registrador.containsKey(regOp1)) { throw new Exception("ERRO: Primeiro operando de comparação inválido!"); }
                 
                        String regOp2= lexer.nextToken();
                        if(!registrador.containsKey(regOp2)) { throw new Exception("ERRO: Segundo operando de comparação inválido!"); }
                        String pos= lexer.nextToken();
                        if(!isNumber(pos) || Integer.parseInt(pos) < 1 || Integer.parseInt(pos) > qtdInstrucoes) { throw new Exception("ERRO: Posição de memória inválida!"); }
                     
                        System.out.println("\nOperador de desvio: " + opcode);
                        System.out.println("Reg. Operando 1: " + regOp1);
                        System.out.println("Reg. Operando 2: " + regOp2);
                        System.out.println("Posicao de desvio: " + pos);
                        System.out.print("Pressione ENTER para continuar...");
                        System.in.read();
                                       
                        opDesvCond(opcode, regOp1, regOp2, pos);
                    }
                
                } else if(opMovDados.contains(opcode)) {
                  
                    if(lexer.countTokens() < 4) { 
                        String reg= lexer.nextToken();
                        if(lexer.countTokens() == 0) { // Se, verdadeiro, então é uma operação usando a pilha.
                            if(!registrador.containsKey(reg)) { throw new Exception("ERRO: Registrador de pilha inválido!"); }

                            System.out.println("\nOperador de pilha: " + opcode);
                            System.out.println("Reg: " + reg);
                            System.out.print("Pressione ENTER para continuar...");
                            System.in.read();
                            
                            opPilha(opcode, reg);
                            
                        } else if(opcode.equals("mov")) {
                            if(!registrador.containsKey(reg)) { throw new Exception("ERRO: Registrador de destino inválido!"); }
                            String regSrc= lexer.nextToken();
                            if(!registrador.containsKey(regSrc) && !isNumber(regSrc)) { throw new Exception("ERRO: Segundo operando inválido!"); }
                            
                            System.out.println("\nOperador de movimentação: " + opcode);
                            System.out.println("Reg. Destino: " + reg);
                            System.out.println("Reg. Origem: " + regSrc);
                            System.out.print("Pressione ENTER para continuar...");
                            System.in.read();
                            
                            opMov(reg, regSrc);
                            
                        } else {
                            if(!registrador.containsKey(reg)) {
                                if(opcode.equals("load")) { throw new Exception("ERRO: Registrador de destino inválido!"); }
                                throw new Exception("ERRO: Registrador de origem inválido!");
                            }
                            String endereco= lexer.nextToken();
                            if(!isNumber(endereco) || Integer.parseInt(endereco) < 1 || Integer.parseInt(endereco) > qtdInstrucoes) { throw new Exception("ERRO: Endereço de memória inválido!"); }
                            
                            System.out.println("\nOperador de memória: " + opcode);
                            System.out.println("Reg: " + reg);
                            System.out.println("Endereço de memória: " + endereco);
                            System.out.print("Pressione ENTER para continuar...");
                            System.in.read();
                            
                            opMem(opcode, reg, endereco);
                        }
                        
                    } else {
                        throw new Exception("ERRO: Quantidade tokens inválida!");
                    }  
                } else if(opES.contains(opcode)) {
                    if(lexer.countTokens() == 1) {
                        String reg= lexer.nextToken();
                        if(!registrador.containsKey(reg)) { throw new Exception("ERRO: Registrador de E/S inválido!"); }
                    
                        System.out.println("\nOperador de E/S: " + opcode);
                        System.out.println("Reg: " + reg);
                        
                        opES(opcode, reg);
                    } else {
                        throw new Exception("ERRO: Quantidade de tokens inválida!");
                    }
                
                } else {
                    throw new Exception("ERRO: Opcode inválido!");
                }
                
            } else {
                throw new Exception("ERRO: Quantidade de tokens inválida!");
            }
        } catch(Exception ex) {
            throw ex;
        }
    }
    
    private void opAritLog(String opcode, String regDest, String regOp1, String regOp2) {
        switch(opcode) {
            case "add": if(registrador.containsKey(regOp2)) {
                            double resultado= registrador.get(regOp1) + registrador.get(regOp2);
                            registrador.replace(regDest, resultado);
                        } else {
                            double resultado= registrador.get(regOp1) + Double.parseDouble(regOp2);
                            registrador.replace(regDest, resultado);
                        }
                        break;
                        
            case "sub": if(registrador.containsKey(regOp2)) {
                            double resultado= registrador.get(regOp1) - registrador.get(regOp2);
                            registrador.replace(regDest, resultado);
                        } else {
                            double resultado= registrador.get(regOp1) - Double.parseDouble(regOp2);
                            registrador.replace(regDest, resultado);
                        }
                        break;
                        
            case "mul": if(registrador.containsKey(regOp2)) {
                            double resultado= registrador.get(regOp1) * registrador.get(regOp2);
                            registrador.replace(regDest, resultado);
                        } else {
                            double resultado= registrador.get(regOp1) * Double.parseDouble(regOp2);
                            registrador.replace(regDest, resultado);
                        }
                        break;
                        
            case "div": if(registrador.containsKey(regOp2)) {
                            double resultado= registrador.get(regOp1) / registrador.get(regOp2);
                            registrador.replace(regDest, resultado);
                        } else {
                            double resultado= registrador.get(regOp1) / Double.parseDouble(regOp2);
                            registrador.replace(regDest, resultado);
                        }
                        break;
                        
            case "mod": if(registrador.containsKey(regOp2)) {
                            double resultado= registrador.get(regOp1) % registrador.get(regOp2);
                            registrador.replace(regDest, resultado);
                        } else {
                            double resultado= registrador.get(regOp1) % Double.parseDouble(regOp2);
                            registrador.replace(regDest, resultado);
                        }
                        break;
                        
            case "pot": if(registrador.containsKey(regOp2)) {
                            double resultado= Math.pow(registrador.get(regOp1), registrador.get(regOp2));
                            registrador.replace(regDest, resultado);
                        } else {
                            double resultado= Math.pow(registrador.get(regOp1), Double.parseDouble(regOp2));
                            registrador.replace(regDest, resultado);
                        }
                        break;
                        
            case "and": if(registrador.containsKey(regOp2)) {
                            int resultado= registrador.get(regOp1).intValue() & registrador.get(regOp2).intValue();
                            registrador.replace(regDest, (double)resultado);
                        } else {
                            int resultado= registrador.get(regOp1).intValue() & Integer.parseInt(regOp2);
                            registrador.replace(regDest, (double)resultado);
                        }
                        break;
                        
            case "or":  if(registrador.containsKey(regOp2)) {
                            int resultado= registrador.get(regOp1).intValue() | registrador.get(regOp2).intValue();
                            registrador.replace(regDest, (double)resultado);
                        } else {
                            int resultado= registrador.get(regOp1).intValue() | Integer.parseInt(regOp2);
                            registrador.replace(regDest, (double)resultado);
                        }
                        break;
              
            case "not": registrador.replace(regDest, (double)(~registrador.get(regOp1).intValue()));
                        break; 
        }
    }
    
    private void opDesvCond(String opcode, String regOp1, String regOp2, String pos) {
        switch(opcode) {
            case "beq": if(registrador.get(regOp1).equals(registrador.get(regOp2))) {
                            pc= Integer.parseInt(pos);
                            pc--; // Decrementa porque a memóriaDeInstruções(vetor) começa da posição 0. 
                        }
                        break;
           
            case "bne": if(!registrador.get(regOp1).equals(registrador.get(regOp2))) {
                            pc= Integer.parseInt(pos);
                            pc--;
                        }
                        break;
            
            case "blt": if(registrador.get(regOp1) < registrador.get(regOp2)) {
                            pc= Integer.parseInt(pos);
                            pc--;
                        }
                        break;
           
            case "ble": if(registrador.get(regOp1) <= registrador.get(regOp2)) {
                            pc= Integer.parseInt(pos);
                            pc--;
                        }
                        break;
           
            case "bgt": if(registrador.get(regOp1) > registrador.get(regOp2)) {
                            pc= Integer.parseInt(pos);
                            pc--;
                        }
                        break;
          
            case "bge": if(registrador.get(regOp1) >= registrador.get(regOp2)) {
                            pc= Integer.parseInt(pos);
                            pc--;
                        }
                        break;
        }
    }
    
    private void opPilha(String opcode, String reg) {
        switch(opcode) {
            case "push":  pilha.push(registrador.get(reg));
                          break;
             
             case "pop":  if(!pilha.isEmpty()) {  // Só desempilha, se a pilha ñ estiver vazia.
                             registrador.replace(reg, pilha.pop());
                          }
                          break;
        }
    }
    
    private void opMov(String regDest, String regSrc) {
        if(registrador.containsKey(regSrc)) {
            registrador.replace(regDest, registrador.get(regSrc));
        } else {
            registrador.replace(regDest, Double.parseDouble(regSrc));
        }
    }
    
    private void opMem(String opcode, String reg, String endereco) {
        switch(opcode) {
            case "load":  registrador.replace(reg, memoriaDados[Integer.parseInt(endereco) - 1]);
                          break;
            case "store": memoriaDados[Integer.parseInt(endereco) - 1]= registrador.get(reg);
                          break;
        }
    }
    
    private void opES(String opcode, String reg) {
        switch(opcode) {
            case "read":  Scanner entrada;
                          String valor= "";
                          boolean ok= false;
                          do {
                             if(ok) { System.out.println("Entrada inválida, digite um número!\n"); }
                             ok= true;
                             entrada= new Scanner(System.in);
                          } while(!isNumber((valor= entrada.nextLine()))); 

                          registrador.replace(reg, Double.parseDouble(valor));
                          break;
            case "write": System.out.println(registrador.get(reg));
                          break;
        }
    }
    
    public void executarMaquinaVirtual() {
        lerArquivo();
        try {
            while(pc < qtdInstrucoes) { 
                buscarInstrucao();
                decodificarInstrucao();
            }
        } catch(Exception ex) {
            ex.printStackTrace();
            System.out.println(ex.getMessage());
        }
    }
}