//
// Created by Bryan on 11/3/2020.
//

#ifndef GA_PATH_H
#define GA_PATH_H

#include <ostream>
#include <vector>
using std::vector;
using std::ostream;

class Path {
public:

    Path();
    Path(float cst);

    friend ostream& operator<<(ostream& os, const Path& path);

    Path& operator=(Path other);

    // assignment operator override to help with combining paths together
    Path& operator+=(const Path &rhsPath);
    Path& operator+(const Path &rhsPath);

    vector<int> path; // vector because we don't know the size
    float cost; // total cost to travel path
};


#endif //GA_PATH_H
