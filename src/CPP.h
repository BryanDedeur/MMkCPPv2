//
// Created by Bryan on 11/3/2020.
//

#ifndef CPP_H
#define CPP_H

#include "Graph.h"
#include <vector>
#include <algorithm>


class CPP {
public:

    CPP();

    void Solve(Graph &graph);
    int shortestPathDistance;
    int numOddVertices;

    vector<int> oddVertices;
};


#endif //GA_PATH_H
