import java.util.Scanner;

public class Main {

        public static void main(String[] args) {

                Scanner scan = new Scanner(System.in);
                double[][] m1, m2;

                m1 = new double[3][3];
                m2 = new double[3][3];

                System.out.println("Leia a primeira matriz: ");
                for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                                m1[i][j] = scan.nextDouble();
                        }
                }

                System.out.println("Leia a segunda matriz: ");
                for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                                m2[i][j] = scan.nextDouble();
                        }
                }

                System.out.println("Resultado da soma: ");
                for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                                System.out.printf("%f ", m1[i][j] + m2[i][j]);
                        }
                        System.out.println("");
                }
        }
}
