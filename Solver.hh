#include <iostream>
#include <istream>
#include <vector>
#include <map>

using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;

struct flight {
    int orig, dest, start, end;
    flight (int o, int d, int s, int e) : orig(o), dest(d), start(s), end(e) {}
};

struct Edge {
  // from u, to v, with capacity c, and flow f
  int u, v, c, f;
  Edge(int u, int v, int c, int f) : u(u), v(v), c(c), f(f) {}
  int flow(int w) { return u == w ? f : (-f); }
  int cap(int w) { return u == w ? (c - f) : f; }
  int to(int w) { return u == w ? v : u; }
  void add(int w, int nf) { f += (u == w ? nf : (-nf)); }
};

typedef vector<Edge> VE;

class Solver {
    public:
        enum Algorithm {
            EdmondsKarp,
            FordFulkerson
        };

        Solver();
        void read();
        void read(istream &file);
        VVI solve_v1(Algorithm a);
        VVI solve_v2(Algorithm a);
        VVI get_results(int k, int s_ini, int t_ini, int num_flights, VVI &adj, VE &edges);

    private: 
        static const int INF;
        // Dinics algorithm
        bool bfs(int s, int t, VI & distance, const VVI & adj, const VE & edges);
        int dfs (int u, int t, int fval, const VI & distance, const VVI & adj, VE & edges, VI & index);
        int dinic(int s, int t, VVI & adj, VE & edges);
        vector<flight> _flights;

        // Edmond Karp's algorithm
        void augment_ek(int v, int minEdge, VVI &res, VI &p, int &f, int s);
        void edmond_karp(VVI &res, int s, int t);
};
