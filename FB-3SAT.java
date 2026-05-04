import java.util.*;

public class SAT {

    static boolean evalClause(int[] clause, int[] assign) {
        for (int lit : clause) {
            int var = Math.abs(lit);
            if ((lit > 0 && assign[var] == 1) ||
                (lit < 0 && assign[var] == 0)) {
                return true;
            }
        }
        return false;
    }

    static boolean bruteSAT(List<int[]> formula, int n) {
        int total = 1 << n;

        for (int mask = 0; mask < total; mask++) {
            int[] assign = new int[n + 1];

            for (int i = 0; i < n; i++) {
                assign[i + 1] = (mask >> i) & 1;
            }

            boolean ok = true;
            for (int[] clause : formula) {
                if (!evalClause(clause, assign)) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                System.out.println("Solución encontrada:");
                for (int i = 1; i <= n; i++) {
                    System.out.println("x" + i + " = " + assign[i]);
                }
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        List<int[]> formula = new ArrayList<>();
        formula.add(new int[]{1, -2, 3});
        formula.add(new int[]{-1, 2, 4});

        int n = 4;

        long inicio = System.nanoTime();
        boolean res = bruteSAT(formula, n);
        long fin = System.nanoTime();

        double tiempo = (fin - inicio) / 1e9;

        System.out.println(res ? "La fórmula es SATISFACIBLE"
                               : "La fórmula NO es satisfacible");
        System.out.println("Tiempo de ejecución: " + tiempo + " segundos");
    }
}
