import java.util.Scanner;

public class Main {
        public static void main(String[] args) {
                Scanner scan = new Scanner(System.in);
                String nome = scan.nextLine();
                char inicial = nome.charAt(0);
                String sobrenome = nome.substring(nome.lastIndexOf(" ") + 1);

                System.out.printf("%s, %c.\n", sobrenome, Character.toUpperCase(inicial));
        }
}
