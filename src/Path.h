//
// Created by Bryan on 11/3/2020.
//

#ifndef GA_PATH_H
#define GA_PATH_H

#include <vector>
using std::vector;

class Path {
public:

    Path();
    Path(int cst);

    Path& operator=(Path other);

    // assignment operator override to help with combining paths together
    Path& operator+=(const Path &rhsPath);

    vector<int> path; // vector because we don't know the size of the array
    int cost; // total cost to travel path
};


#endif //GA_PATH_H
