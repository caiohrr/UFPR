import java.util.Scanner;

public class Main {
        public static void main(String[] args) {
                
                Scanner scan = new Scanner(System.in);
                int num = scan.nextInt();

                if (num % 2 == 0)
                        System.out.printf("%d e par.\n", num);
                else
                        System.out.printf("%d e impar\n.", num);
        }
}
