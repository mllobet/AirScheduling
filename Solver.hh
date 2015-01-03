#include <iostream>
#include <istream>
#include <vector>
#include <map>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VII;
typedef vector<VI> VVI;

struct flight {
    int orig, dest, start, end;
    flight (int o, int d, int s, int e) : orig(o), dest(d), start(s), end(e) {}
};

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
        static const int INF;
        // Dinics algorithm
        int dinic(int s, int t, VVI & flow, VVI & cap);
        bool d_bfs(int s, int t, VI & distance, VVI & flow, VVI & cap);
        int d_dfs (int u, int t, int fval, const VI & distance, VVI & flow, VVI & cap, VI & index);
        vector<flight> _flights;

        //void augment_ek(int v, int minEdge, VII res, VI &p, int &f, int s);
};
