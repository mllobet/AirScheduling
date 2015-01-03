#include <iostream>
#include <istream>
#include <vector>
#include <map>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VII;

typedef struct {
    int orig, dest, start, end;
    flight (int o, int d, int s, int e) : orig(o), dest(d), start(s), end(e) {}
}flight;

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
        vector<flight> _flights;

        //void augment_ek(int v, int minEdge, VII res, VI &p, int &f, int s);
};
