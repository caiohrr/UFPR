import java.util.Scanner;

public class Main {

        public static void main(String[] args) {
                Scanner scan = new Scanner(System.in);
                int notas[][] = new int[4][2];
                int maior_nota = 0;
                
                for (int i = 0; i < 4; i++) {
                        System.out.printf("Aluno %d:\n", i + 1);
                        for (int j = 0; j < 2; j++) {
                                notas[i][j] = scan.nextInt();
                                if (notas[i][j] > maior_nota)
                                        maior_nota = notas[i][j];
                        }
                }
                for (int i = 0; i < 4; i++) {
                        System.out.printf("Maior nota do Aluno %d: ", i + 1);
                        if (notas[i][0] > notas[i][1])
                                System.out.printf("%d\n", notas[i][0]);
                        else
                                System.out.printf("%d\n", notas[i][1]);

                }

                System.out.printf("Maior nota de todas: %d\n", maior_nota);

        }
}
