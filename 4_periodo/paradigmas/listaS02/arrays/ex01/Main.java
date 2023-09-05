import java.util.Scanner;

public class Main {
        public static void main(String[] args) {
                Scanner scan = new Scanner(System.in);
                int num = 10;
                double media = 0;
                int[] arr = new int[num];

                for (int i = 0; i < num; i++) {
                        arr[i] = scan.nextInt();
                        media += arr[i];
                }
                media = media/num;

                System.out.printf("Media das idades: %f\n", media);
                System.out.println("As seguintes idades estao acima da media: ");

                for (int i = 0; i < num; i++) {
                        if (arr[i] > media)
                                System.out.printf("%d\n", arr[i]);
                }
        }
}
