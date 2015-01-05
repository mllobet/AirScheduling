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
 * Solves the problem, returns a list of crew assignations, one
 * per element
 */
VVI Solver::solve(Algorithm a, Version version) {
    // Build graph

    // create 2 nodes per flight v_i and t_i (where v_i is in pos 2*i and t_i in 2*i + 1)
    int size = _flights.size()*2 + 4;
    int s = size - 2;
    int t = size - 1;
    int s_ini = s - 2;
    int t_ini = s - 1;

    int capacity = 1;
    if (version == V2) capacity = INF;

    VVI graph(size);
    VE edges;

    map<int,VI> city_flights; 
    for (int i = 0; i < int(_flights.size()); ++i) {
        int orig = _flights[i].orig; 
        if (city_flights.find(orig) == city_flights.end()) {
            city_flights[orig] = VI();
        }
        city_flights[orig].push_back(2*i); 
    }

    // add connecting flights
    for (int i = 0; i < int(_flights.size()); ++i) {
        for (int f: city_flights[_flights[i].dest]) {
            if (_flights[i].end + 15 <= _flights[f/2].start) {
                add_edge(graph, edges, 2*i+1, f, capacity);
            }
        }
    }

    // Add edge in each flight only if version2
    if (version == V2) {
      for (int i = 0; i < int(_flights.size()); ++i) {
        add_edge(graph, edges, 2*i, 2*i+1, INF);
      }
    }

    // source and drain initial connections 
    for (int i = 0; i < int(_flights.size()); ++i){
        add_edge(graph, edges, s_ini, 2*i, 1);
        add_edge(graph, edges, 2*i+1, t_ini, 1);
    } 

    // source and drain connections to set demand 
    for (int i = 0; i < int(_flights.size()); ++i) {
        add_edge(graph, edges, s, 2*i+1, 1);
        add_edge(graph, edges, 2*i, t, 1);
    }

    int source_edge = add_edge(graph, edges, s, s_ini, 0); 
    int sink_edge = add_edge(graph, edges, t_ini, t, 0); 
    
    int num_flights = _flights.size();

    // binary search in (low, high]
    int low = 0, high = num_flights;
    while (low+1 < high) {
      // Reset graph
      for (Edge &e : edges) {
          e.f = 0;
      }

      int mid = (high-low)/2 + low;
      edges[source_edge].c = edges[sink_edge].c = mid;

      int ans;
      if (a == EdmondsKarp) {
          ans = edmond_karp(s, t, graph, edges);
      }
      else {
          ans = dinic(s, t, graph, edges);
      }

      if (ans >= num_flights + mid) {
          high = mid;
      }
      else {
          low = mid;
      }
    }

    // Run last time to run with k = high
    edges[source_edge].c = edges[sink_edge].c = high;
    if (a == EdmondsKarp) {
        edmond_karp(s, t, graph, edges);
    }
    else {
        dinic(s, t, graph, edges);
    }
    return get_results(high, s_ini, t_ini, num_flights, graph, edges);
}

// Edmonds Karp's
int Solver::edmond_karp(int s, int t, VVI & graph, VE & edges) {
    int mFlow = 0;
    while (true) {
        queue<int> q;
        q.push(s);
        VI pred(graph.size(), -1);
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            if (pred[t] != -1) break;
            for (int i : graph[cur]) {
                Edge e = edges[i];
                int v = e.to(cur);
                if (pred[v] == -1 and e.cap(cur) > 0) {
                    pred[v] = i;
                    q.push(v);
                }
            }
        }
        if (pred[t] == -1) break;
        int df = INF;
        int u = t;
        while (u != s) {
            int v = edges[pred[u]].to(u);
            df = min(df, edges[pred[u]].cap(v));
            u = v;
        }
        u = t;
        while (u != s) {
            int v = edges[pred[u]].to(u);
            edges[pred[u]].add(v, df);
            u = v;
        }
        mFlow += df;
    }
    return mFlow;
}

// DINIC

// BFS to build the residual graph and distances for level graph.
// Returns true if there is a path from s to t with cap > 0
bool Solver::bfs(int s, int t, VI & distance, const VVI & graph, const VE & edges) {
    queue<int> q;
    q.push(s);
    for (int i = 0; i < int(distance.size()); ++i) distance[i] = -1;
    distance[s] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i : graph[u]) {
            Edge edge = edges[i];
            int v = edge.to(u);
            if (edge.cap(u) > 0 and distance[v] == -1) {
                q.push(v);
                distance[v] = distance[u]+1;
            }
        }
    }
    return distance[t] != -1;
}
 
int Solver::dfs (int u, int t, int fval, const VI & distance, const VVI & graph, VE & edges, VI & index) {
    if (!fval)  return 0;
    if (u == t)  return fval;
    int & ind = index[u];
    while (ind < int(graph[u].size())) {
        Edge & edge = edges[graph[u][ind]];
        int v = edge.to(u);
        int c = edge.cap(u);

        if (distance[u]+1 == distance[v] and c > 0) {
            int f = dfs(v, t, min(fval, c), distance, graph, edges, index);
            if (f) {
                edge.add(u, f);
                return f;
            }
        }
        ++ind;
    }
    return 0;
}
 
int Solver::dinic(int s, int t, VVI & graph, VE & edges) {
    int fval = 0;
    VI distance(graph.size());
    while (bfs(s, t, distance, graph, edges)) {
        VI index(distance.size(), 0);
        while (int f = dfs(s, t, INF, distance, graph, edges, index))
            fval += f;
    }
    return fval;
}

int Solver::add_edge(VVI &graph, VE &edges, int u, int v, int cap) {
    graph[u].push_back(edges.size());
    graph[v].push_back(edges.size());
    edges.push_back(Edge(u, v, cap, 0));

    return edges.size() - 1;
}

// RESULTS. This modifies the residual graph
// k is the number of pilots.
// s_ini the source before applying nodes' demand
// t_ini the sink before applying nodes' demand
VVI Solver::get_results(int k, int s_ini, int t_ini, int num_flights, VVI &graph, VE &edges) {
    VI act(graph.size(), 0);
    vector<bool> taken(num_flights, false);
    VVI results(k);
    for (int id = 0; id < k; ++id) {
        int u = s_ini;
        while (u != t_ini) {
            int & ind = act[u];
            bool found = false;
            while (!found and ind < int(graph[u].size())) {
                Edge & e = edges[graph[u][ind]];
                int v = e.to(u);
                if (e.flow(u) > 0) {
                    e.add(u, -1);
                    u = v;
                    found = true;
                }
                else {
                    ++ind;
                }
            }
            if (u != t_ini) {
                int flight_id = u/2;
                if (!taken[flight_id]) {
                    results[id].push_back(flight_id+1);
                    taken[flight_id] = true;
                }
                ++u; // Go to second node of that flight
            }
        }
    }
    return results;
}

