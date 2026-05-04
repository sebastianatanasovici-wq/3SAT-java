#include <iostream>
#include <vector>
#include <map>
#include <chrono>
using namespace std;

typedef vector<vector<int>> Formula;

Formula simplify(Formula clauses, int literal) {
    Formula new_clauses;
    for (auto &clause : clauses) {
        bool satisfied = false;
        vector<int> new_clause;
        for (int lit : clause) {
            if (lit == literal) {
                satisfied = true;
                break;
            }
        }
        if (satisfied) continue;
        for (int lit : clause) {
            if (lit != -literal)
                new_clause.push_back(lit);
        }
        if (new_clause.empty()) return {};
        new_clauses.push_back(new_clause);
    }
    return new_clauses;
}

bool hasEmptyClause(const Formula &clauses) {
    for (auto &c : clauses)
        if (c.empty()) return true;
    return false;
}

bool dpll(Formula clauses, map<int,bool> &assignment) {
    if (clauses.empty()) return true;
    if (hasEmptyClause(clauses)) return false;

    int literal = clauses[0][0];

    assignment[abs(literal)] = true;
    if (dpll(simplify(clauses, literal), assignment)) return true;

    assignment[abs(literal)] = false;
    if (dpll(simplify(clauses, -literal), assignment)) return true;

    assignment.erase(abs(literal));
    return false;
}

int main() {
    Formula formula = {{1, -2, 3}, {-1, 2, 4}};
    map<int,bool> assignment;

    auto start = chrono::high_resolution_clock::now();
    bool result = dpll(formula, assignment);
    auto end = chrono::high_resolution_clock::now();

    int n = 4;

    if (result) {
        cout << "Solución encontrada:" << endl;
        for (int i = 1; i <= n; i++) {
            int val = assignment[i] ? 1 : 0;
            cout << "x" << i << " = " << val << endl;
        }
        cout << "La fórmula es SATISFACIBLE" << endl;
    } else {
        cout << "No existe solución" << endl;
        cout << "La fórmula es INSATISFACIBLE" << endl;
    }

    chrono::duration<double> diff = end - start;
    cout << "Tiempo de ejecución: " << diff.count() << " segundos" << endl;

    return 0;
}
