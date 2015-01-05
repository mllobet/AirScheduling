#include <iostream>
#include <fstream>
#include <istream>
#include <cstdio>
#include "Solver.hh"

using namespace std;

void print_results(string out_file, const vector<vector<int> > &results) {
    ofstream os(out_file);
    os << results.size() << endl;
    for (int i = 0; i < int(results.size()); ++i) {
        for (int j = 0; j < int(results[i].size()); ++j) {
            os << (j?" ":"") << results[i][j];
        }
        os << endl;
    }
}

void usage(string name) {
    cout << "usage: " << name << " input_file output_file version algorithm" << endl << endl;
    cout << "optional arguments:" << endl;
    cout << "-h: shows this help message" << endl << endl;
    cout << "version {1,2}" << endl;
    cout << "algorithm {ek,di} ek = Edmond Karp's, di = Dinic's" << endl;
    exit(-1);
}

int main(int argc, char *argv[]){
    if (argc < 5)
        usage(argv[0]);

    Solver s;
    ifstream i(argv[1]);
    istream &is = i;
    s.read(is);

    Solver::Algorithm a = Solver::EdmondsKarp;
    if (strncmp(argv[4],"ek",2)) a = Solver::EdmondsKarp;
    else if (strncmp(argv[4],"di",2)) a = Solver::EdmondsKarp;
    else usage(argv[0]);

    VVI solution;
    int version = atoi(argv[3]);
    if (version == 1) solution = s.solve_v1(a);
    else if (version == 2) solution = s.solve_v2(a);
    else usage(argv[0]);

    print_results(argv[2], solution);
}
