#include <iostream>
#include <vector>
using namespace std;

bool evalClause(const vector<int>& clause, const vector<int>& assign) {
    for (int lit : clause) {
        int var = abs(lit);

        if (lit > 0 && assign[var] == 1) return true;
        if (lit < 0 && assign[var] == 0) return true;
    }
    return false;
}

bool solveSAT(const vector<vector<int>>& formula, vector<int>& assign, int idx, int n) {
    if (idx > n) {
        for (const auto& clause : formula)
            if (!evalClause(clause, assign))
                return false;
        return true;
    }

    assign[idx] = 0;
    if (solveSAT(formula, assign, idx + 1, n)) return true;

    assign[idx] = 1;
    if (solveSAT(formula, assign, idx + 1, n)) return true;

    return false;
}

int main() {
    vector<vector<int>> formula = {
        {1, -2, 3},
        {-1, 2, 4}
    };

    int n = 4;
    vector<int> assign(n + 1);

    if (solveSAT(formula, assign, 1, n))
        cout << "SATISFACIBLE" << endl;
    else
        cout << "NO SATISFACIBLE" << endl;

    return 0;
}
