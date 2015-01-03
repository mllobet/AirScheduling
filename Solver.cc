#include "Solver.hh"

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
VII Solver::solve_v1(Algorithm a) {
    // Build graph

    // create 2 nodes per flight v_i and t_i (where v_i is in pos 2*i and t_i in 2*i + 1)
    int size = _flights.size()*2 + 2;
    int s = size - 2;
    int d = size - 1;
    VII res(size, VI(size));
    VI demands(size);

    map<int,VI> city_flights; 
    for(int i = 0; i < _flights.size(); ++i) {
        int orig = _flights[i].orig; 
        //res[2*i][2*i+1] = 1; // set the capacity between the 2 nodes to 1
        if (city_flights.find(orig) == city_flights.end()) {
            city_flights[orig] = VI();
        }
        city_flights[orig].push_back(2*i); 
    }

    // add connecting flights
    for(int i = 0; i < _flights.size(); ++i) {
        for (int flight: city_flights[_flights[i].dest]) {
            if (_flights[i].end + 15 <= _flights[flight].start) {
                res[2*i+1][flight] = 1;
            }
        }
    }

    // source and drain initial connections 
    for(int i = 0; i < _flights.size(); ++i){
        res[s][2*i] = 1;
        res[d][2*i+1] = 1; 
    } 

    // source and drain connections to set demand 
    for(int i = 0; i < _flights.size(); ++i) {
        res[s][2*i+1]++;
        res[d][2*i]++;
    }

    
    switch (a) {
        case EdmondsKarp :
            break;
        case FordFulkerson :
            break;
    }
    return VII();
}

VII Solver::solve_v2(Algorithm a) {
    // Build graph
    
    switch (a) {
        case EdmondsKarp :
            break;
        case FordFulkerson :
            break;
    }
    return VII();
}

//void Solver::augment_ek(int v, int minEdge, VII res, VI &p, int &f, int s) {
//    if (v == s) {
//        f = minEdge;
//        return;
//    }
//    else if (p[v] != -1) {
//        augment(p[v], min(minEdge, res[p[v]][v]));
//        res[p[v]][v] -= f;
//        res[v][p[v]] += f;
//    }
//}
