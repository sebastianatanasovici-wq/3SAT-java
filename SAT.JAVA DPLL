import java.util.*;

public class SAT {

    static List<List<Integer>> simplify(List<List<Integer>> clauses, int literal) {
        List<List<Integer>> newClauses = new ArrayList<>();
        for (List<Integer> clause : clauses) {
            if (clause.contains(literal)) continue;
            List<Integer> newClause = new ArrayList<>();
            for (int lit : clause) {
                if (lit != -literal) {
                    newClause.add(lit);
                }
            }
            if (newClause.isEmpty()) return null;
            newClauses.add(newClause);
        }
        return newClauses;
    }

    static boolean hasEmptyClause(List<List<Integer>> clauses) {
        for (List<Integer> c : clauses) {
            if (c.isEmpty()) return true;
        }
        return false;
    }

    static boolean dpll(List<List<Integer>> clauses, Map<Integer, Boolean> assignment) {
        if (clauses.isEmpty()) return true;
        if (hasEmptyClause(clauses)) return false;

        int literal = clauses.get(0).get(0);

        assignment.put(Math.abs(literal), true);
        if (dpll(simplify(clauses, literal), assignment)) return true;

        assignment.put(Math.abs(literal), false);
        if (dpll(simplify(clauses, -literal), assignment)) return true;

        assignment.remove(Math.abs(literal));
        return false;
    }

    public static void main(String[] args) {
        List<List<Integer>> formula = new ArrayList<>();
        formula.add(Arrays.asList(1, -2, 3));
        formula.add(Arrays.asList(-1, 2, 4));

        Map<Integer, Boolean> assignment = new HashMap<>();

        long start = System.nanoTime();
        boolean result = dpll(formula, assignment);
        long end = System.nanoTime();

        int n = 4;

        if (result) {
            System.out.println("Solución encontrada:");
            for (int i = 1; i <= n; i++) {
                int val = assignment.getOrDefault(i, false) ? 1 : 0;
                System.out.println("x" + i + " = " + val);
            }
            System.out.println("La fórmula es SATISFACIBLE");
        } else {
            System.out.println("No existe solución");
            System.out.println("La fórmula es INSATISFACIBLE");
        }

        double tiempo = (end - start) / 1e9;
        System.out.println("Tiempo de ejecución: " + tiempo + " segundos");
    }
}
