//
// Created by bryan on 10/15/20.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "Options.h"
#include "Utils.h"
#include "Const.h"

#include <iostream>
#include <map>
#include <vector>
#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Path {
    vector<int> path; // vector because we don't know the size of the array
    int cost; // total cost to travel path

    Path() : path(vector<int>()), cost(INT_MAX) {} // default constructor THINGS WILL BREAK WITH DIJKSTRAS IF COST IS NOT INT_MAX
    Path(vector<int> pth, int cst) : path(pth) , cost(cst) {} // path struct constructor

    Path& operator=(Path other) { // Assignment operator copying struct
        this->path = vector<int>();
        for (int& itr : other.path) {
            this->path.push_back(itr);
        }
        this->cost = other.cost;
        return *this;
    }

    // assignment operator override to help with combining paths together
    Path& operator+=(const Path &rhsPath) {
        for (const int& it : rhsPath.path) {
            this->path.push_back(it);
        }
        this->cost += rhsPath.cost;
        return *this;
    }
};

//const int NUM_VERTICES_PER_EDGE = 2;
//const int MAX_NUM_VERTICES = 100;

class Graph {
    public:
        Graph();
        Graph(Options options);
        virtual ~Graph();

        void Init();

        pair<int, int>& GetVerticesOnEdge(int& edgeA); // always returns two vertices

        Path& GetShortestPathBetweenVertices(int& startVertex, int& endVertex);
        Path& GetShortestPathBetweenEdges(int& edgeA, int& edgeB);
        Path& GetShortestPathBetweenVertexAndEdge(int& vertex, int& edge);
        int& GetEdgeCost(int& vertexA, int& vertexB);
        int& GetOppositeVertexOnEdge(int& vertex, int& edge);

        int numVertices;
        int numEdges;
    private:
        void SetGraphFromFile(string file);

        int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES]; // for storing weighted graph

        void CalculateNumberOfEdges();
        Path cachedShortestPaths[MAX_VERTICES][MAX_VERTICES]; // for storing the path results from dijkstra's algorithm
        Path* cachedShortestPathBetweenEdges[MAX_EDGES][MAX_EDGES]; // for storing the shortest paths between two edges
        pair<int, int> cachedVerticesOnEdge[MAX_EDGES]; // for storing the association between edges and vertices

        int MinDistance(int dist[], bool sptSet[]);
        void Dijkstras(int startVertex);

};


#endif //SRC_GRAPH_H
