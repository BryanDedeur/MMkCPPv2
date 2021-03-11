//
// Created by Bryan on 11/3/2020.
//

#include "Edge.h"

Edge::Edge() : id(0), vertexA(0), vertexB(0), cost(0) {

}

Edge::Edge(int identifier, int vA, int vB, float cst) : id(identifier), vertexA(vA), vertexB(vB), cost(cst) {
	vpair = std::pair<int, int>(vA, vB);
} 

Edge& Edge::operator=(Edge other) { // Assignment operator copying struct
	this->cost = other.cost;
	this->id = other.id;
	this->vertexA = other.vertexA;
	this->vertexB = other.vertexB;
	this->vpair = other.vpair;
    return *this;
}