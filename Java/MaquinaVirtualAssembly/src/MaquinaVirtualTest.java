
public class MaquinaVirtualTest {
    public static void main(String[] args) {
        MaquinaVirtual mv= new MaquinaVirtual("/home/oem/Desktop/Puc/Compiladores/MaquinaVirtualAssembly/file/programTest.txt");
       
        System.out.println("Executando Máquina Virtual...\n");
        mv.executarMaquinaVirtual();
    }
}
