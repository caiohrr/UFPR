public class Telefone {
        int ddi = 0;
        int ddd = 0;
        long numero = 0;

        void cadastrarNumero(int ddi, int ddd, int num) {
                this.ddi = ddi;
                this.ddd = ddd;
                this.numero = num;
        }

        void exibirNumero() {
                System.out.printf("+%d (%d) %d\n", this.ddi, this.ddd, this.numero);
        }
}
