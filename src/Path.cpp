//
// Created by Bryan on 11/3/2020.
//

#include "Path.h"

Path::Path() : path(), cost(INT_MAX) {

} // default constructor THINGS WILL BREAK WITH DIJKSTRAS IF COST IS NOT INT_MAX

Path::Path(int cst) : path() , cost(cst) {

} // path struct constructor

Path& Path::operator=(Path other) { // Assignment operator copying struct
    this->path.clear();
    for (const int& itr : other.path) {
        int it = itr;
        this->path.push_back(it);
    }
    this->cost = other.cost;
    return *this;
}

// assignment operator override to help with combining paths together
Path& Path::operator+=(const Path &rhsPath) {
    for (const int& itr : rhsPath.path) {
        int it = itr;
        this->path.push_back(it);
    }
    this->cost += rhsPath.cost;
    return *this;
}