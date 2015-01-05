#include <iostream>
#include <fstream>
#include <istream>

#include <cstdio>
#include <cstring>
#include <ctime>

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
    cout << "usage: " << name << " input_file output_file version algorithm [-t or -s]" << endl << endl;
    cout << "optional arguments:" << endl;
    cout << "-h: shows this help message" << endl << endl;
    cout << "-t: prints only input file name and time to compute solution" << endl;
    cout << "-s: prints only input file name and number of pilots in solution" << endl;
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
    Solver::Version v = Solver::V1;
    if (version == 1) v = Solver::V1;
    else if (version == 2) v = Solver::V2;
    else usage(argv[0]);

    double ti = clock();
    solution = s.solve(a, v);
    double t = (clock() - ti) / double(CLOCKS_PER_SEC);

    if (argc == 6) { // print time measurements
        if (strncmp(argv[5],"-s",3)) {
            cout << argv[1] << ',' << t << endl;
        } else if (strncmp(argv[5],"-t",3)) {
            cout << argv[1] << ' ' << solution.size() << endl;
        } else {
            usage(argv[0]);
        }
    } else {
        print_results(argv[2], solution);
    }

}
