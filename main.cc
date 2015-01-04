#include <iostream>
#include "Solver.hh"

using namespace std;

void print_results(const vector<vector<int> > &results) {
    cout << results.size() << endl;
    for (int i = 0; i < int(results.size()); ++i) {
        for (int j = 0; j < int(results[i].size()); ++j) {
            cout << (j?" ":"") << results[i][j];
        }
        cout << endl;
    }
}

int main(){
    Solver s;
    s.read();
}
