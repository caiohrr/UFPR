public class Main {

        public static void main(String args[]) {

                Telefone telefone1 = new Telefone();
                telefone1.cadastrarNumero(55, 41, 991620911);
                Telefone telefone2 = new Telefone();
                telefone2.cadastrarNumero(55, 333, 991920918);
                Telefone telefone3 = new Telefone();
                telefone3.cadastrarNumero(55, 923, 991223331);
                Telefone telefone4 = new Telefone();
                telefone4.cadastrarNumero(99, 428, 991620911);
                Telefone telefone5 = new Telefone();
                telefone5.cadastrarNumero(134, 88, 991620911);

                Telefone[] telefones = {telefone1, telefone2, telefone3, telefone4, telefone5};

                for (int i = 0; i < 5; i++) {
                        telefones[i].exibirNumero();
                }
        }
}
