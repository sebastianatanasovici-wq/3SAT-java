#include <iostream>
#include <vector>
using namespace std;

bool evalClause(vector<int>& clause, vector<int>& assign) {
    for (int lit : clause) {
        int var = abs(lit);
        if ((lit > 0 && assign[var] == 1) || (lit < 0 && assign[var] == 0))
            return true;
    }
    return false;
}

bool bruteSAT(vector<vector<int>>& formula, int n) {
    int total = 1 << n;
    
    for (int mask = 0; mask < total; mask++) {
        vector<int> assign(n+1);
        
        for (int i = 0; i < n; i++)
            assign[i+1] = (mask >> i) & 1;
        
        bool ok = true;
        for (auto& c : formula) {
            if (!evalClause(c, assign)) {
                ok = false;
                break;
            }
        }
        
        if (ok) return true;
    }
    
    return false;
}
