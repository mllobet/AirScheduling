#include <iostream>
#include <istream>
#include <vector>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VII;

class Solver {
    public:
        enum Algorithm {
            EdmondsKarp,
            FordFulkerson
        };

        Solver();
        void read();
        void read(istream &file);
        VII solve_v1(Algorithm a);
        VII solve_v2(Algorithm a);

    private: 
        VII _problem;

        //void augment_ek(int v, int minEdge, VII res, VI &p, int &f, int s);
};
