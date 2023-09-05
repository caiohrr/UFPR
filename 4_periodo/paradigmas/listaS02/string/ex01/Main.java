import java.util.Scanner;

public class Main {

        public static void main(String[] args) {
                Scanner scan = new Scanner(System.in);
                String entrada = scan.nextLine();

                int palavras = entrada.split("\\s").length;
                System.out.printf("A string possui %d palavras.\n", palavras);
        }
}
