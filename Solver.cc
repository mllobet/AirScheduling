#include "Solver.hh"
#include <queue>

const int Solver::INF = 1000000000;

Solver::Solver(){
    
}

void Solver::read() {
    Solver::read(cin);
}

/*
 * Reads a problem instance
 */
void Solver::read(istream &is) {
    int orig, dest, start, end;
    while (is >> orig >> dest >> start >> end) {
        _flights.push_back(flight(orig, dest, start, end));
    }
}

/*
 * Solves version 1 of the problem, returns a list of crew assignations, one
 * per element
 */
VVI Solver::solve_v1(Algorithm a) {
    // Build graph

    // create 2 nodes per flight v_i and t_i (where v_i is in pos 2*i and t_i in 2*i + 1)
    int size = _flights.size()*2 + 4;
    int s = size - 2;
    int t = size - 1;
    int s_ini = s - 2;
    int t_ini = s - 1;
    VVI res(size, VI(size));
    VI demands(size);

    map<int,VI> city_flights; 
    for (int i = 0; i < int(_flights.size()); ++i) {
        int orig = _flights[i].orig; 
        //res[2*i][2*i+1] = 1; // set the capacity between the 2 nodes to 1
        if (city_flights.find(orig) == city_flights.end()) {
            city_flights[orig] = VI();
        }
        city_flights[orig].push_back(2*i); 
    }

    // add connecting flights
    for (int i = 0; i < int(_flights.size()); ++i) {
        for (int flight: city_flights[_flights[i].dest]) {
            if (_flights[i].end + 15 <= _flights[flight].start) {
                res[2*i+1][flight] = 1;
            }
        }
    }

    // source and drain initial connections 
    for (int i = 0; i < int(_flights.size()); ++i){
        res[s_ini][2*i] = 1;
        res[t_ini][2*i+1] = 1; 
    } 

    // source and drain connections to set demand 
    for (int i = 0; i < int(_flights.size()); ++i) {
        res[s][2*i+1]++;
        res[t][2*i]++;
    }

    // actual algorithm has to set up the source and drain connections to s_ini and d_ini

    
    switch (a) {
        case EdmondsKarp :
            break;
        case FordFulkerson :
            break;
    }
    return VVI();
}

VVI Solver::solve_v2(Algorithm a) {
    // Build graph
    
    switch (a) {
        case EdmondsKarp :
            break;
        case FordFulkerson :
            break;
    }
    return VVI();
}

// Edmonds Karp's

void Solver::augment_ek(int v, int minEdge, VVI &res, VI &p, int &f, int s) {
    if (v == s) {
        f = minEdge;
        return;
    }
    else if (p[v] != -1) {
        Solver::augment_ek(p[v], min(minEdge, res[p[v]][v]), res, p, f, s);
        res[p[v]][v] -= f;
        res[v][p[v]] += f;
    }
}

void Solver::edmond_karp(VVI & res, int s, int t) {
    int mf, f;
    mf = f = 0;
    VI p;
    while (true) {
        f = 0; 
        // run BFS
        VI dist(res.size(), INF); dist[s] = 0;
        queue<int> q; q.push(s);
        p.assign(res.size(), -1); //BFS spanning tree, from s to t!
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int v = 0; v < res.size(); ++v) {
                if (res[u][v] > 0 && dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    p[v] = u;
                }
            }
        }   
        Solver::augment_ek(t, INF, res, p, f, s);
        if (f == 0) break;
        mf += f;
    }
}




// DINIC

// BFS to build the residual graph and distances for level graph.
// Returns true if there is a path from s to t with cap > 0
bool Solver::d_bfs(int s, int t, VI & distance, VVI & flow, VVI & cap) {
  queue<int> q;
  q.push(s);
  for (int i = 0; i < int(flow.size()); ++i) distance[i] = -1;
	distance[s] = 0;

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v = 0; v < int(flow.size()); ++v) {
      if (distance[v] == -1 and flow[u][v] < cap[u][v]) {
        q.push(v);
        distance[v] = distance[u]+1;
      }
    }
  }
  return distance[t] != -1;
}
 
int Solver::d_dfs (int u, int t, int fval, const VI & distance, VVI & flow, VVI & cap, VI & index) {
	if (!fval)  return 0;
	if (u == t)  return fval;
  int & v = index[u];
  while (v < int(flow.size())) {
    int c = cap[u][v] - flow[u][v];
    if (distance[u]+1 == distance[v] and c > 0) {
      int f = d_dfs(v, t, min(fval, c), distance, flow, cap, index);
      if (f) {
        flow[u][v] += f;
        flow[v][u] -= f;
        return f;
      }
    }
    ++v;
  }
  return 0;
}
 
int Solver::dinic(int s, int t, VVI & flow, VVI & cap) {
	int fval = 0;
  VI distance(flow.size());
  while (d_bfs(s, t, distance, flow, cap)) {
    VI index(distance.size(), 0);
		while (int f = d_dfs(s, t, INF, distance, flow, cap, index)) fval += f;
	}
	return fval;
}
