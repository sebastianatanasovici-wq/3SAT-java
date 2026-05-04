#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Evaluar una cláusula
bool evalClause(vector<int>& clause, vector<int>& assign) {
    for (int lit : clause) {
        int var = abs(lit);

        if ((lit > 0 && assign[var] == 1) ||
            (lit < 0 && assign[var] == 0)) {
            return true;
        }
    }
    return false;
}

// Fuerza bruta
bool bruteSAT(vector<vector<int>>& formula, int n) {
    int total = 1 << n;

    for (int mask = 0; mask < total; mask++) {
        vector<int> assign(n + 1);

        // Generar asignación
        for (int i = 0; i < n; i++) {
            assign[i + 1] = (mask >> i) & 1;
        }

        bool ok = true;

        // Verificar cláusulas
        for (auto& clause : formula) {
            if (!evalClause(clause, assign)) {
                ok = false;
                break;
            }
        }

        // Si es solución
        if (ok) {
            cout << "Solución encontrada:\n";
            for (int i = 1; i <= n; i++) {
                cout << "x" << i << " = " << assign[i] << endl;
            }
            return true;
        }
    }

    return false;
}

int main() {

    cout << "Inicio del programa...\n";

    // Fórmula: (x1 ∨ ¬x2 ∨ x3) ∧ (¬x1 ∨ x2 ∨ x4)
    vector<vector<int>> formula = {
        {1, -2, 3},
        {-1, 2, 4}
    };

    int n = 10;

    auto inicio = chrono::high_resolution_clock::now();

    bool result = bruteSAT(formula, n);

    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    if (result) {
        cout << "La fórmula es SATISFACIBLE\n";
    } else {
        cout << "La fórmula NO es satisfacible\n";
    }

    cout << "Tiempo de ejecución: " << duracion.count() << " segundos\n";

    return 0;
}
