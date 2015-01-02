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
        VI trip{orig, dest, start, end};
        _problem.push_back(trip);
    }
}

/*
 * Solves version 1 of the problem, returns a list of crew assignations, one
 * per element
 */
VII Solver::solve_v1(Algorithm a) {
    // Build graph

    // v_i and t_i nodes (where v_i is in pos 2*i and t_i in 2*i + 1)
    int size = _problem.size()*2;
    VII res(size, VI(size));
    for (VI trip : _problem)
        res[trip[0]][trip[1]] = 1;



    
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
