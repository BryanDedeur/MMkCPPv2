//
// Created by Bryan on 11/3/2020.
//

#include "Path.h"

#include <climits>


Path::Path() : path(), cost(INT_MAX) {

} // default constructor THINGS WILL BREAK WITH DIJKSTRAS IF COST IS NOT INT_MAX

Path::Path(int cst) : path() , cost(cst) {

} // path struct constructor

ostream& operator<<(ostream& os, const Path& path) {
    for (const int& itr : path.path) {
        os << itr << ' ';
    }
    if (path.cost > 100) {
        path.cost;
    }
    os << "cost: " << path.cost;
    return os;
}

Path& Path::operator=(Path other) { // Assignment operator copying struct
    this->path.clear();
    for (const int& itr : other.path) {
        this->path.push_back(itr);
    }
    this->cost = other.cost;
    return *this;
}

// assignment operator override to help with combining paths together
Path& Path::operator+=(const Path &rhsPath) {
    for (const int& itr : rhsPath.path) {
        if (!this->path.empty()) {
            if (!(itr == this->path.back())) {
                this->path.push_back(itr);
            }
        } else {
            this->path.push_back(itr);
        }
    }

    if (this->cost > 100 || rhsPath.cost > 100) {
        this->cost = this->cost;
    }

    this->cost += rhsPath.cost;
    return *this;
}

//// assignment operator override to help with combining paths together
//Path& Path::operator+(const Path &rhsPath) {
//    Path newPath = Path(0);
//    // TODO fix this
//    if (!this->path.empty()) {
//        for (const int& itr : this->path) {
//            newPath.path.push_back(itr);
//        }
//    }
//
//    if (!rhsPath.path.empty()) {
//        for (const int& itr : rhsPath.path) {
//            newPath.path.push_back(itr);
//        }
//    }
//
//    newPath = rhsPath.cost + this->cost;
//    return newPath;
//}