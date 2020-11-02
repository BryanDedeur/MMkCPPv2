//
// Created by bryan on 10/15/20.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "Options.h"
#include "Utils.h"
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

    Path() : path(), cost(INT_MAX) {} // default constructor
    Path(vector<int> pth, int &cst) : path(pth) , cost(cst) {} // path struct constructor
};

const int NUM_VERTICES_PER_EDGE = 2;
const int MAX_NUM_VERTICES = 100;

class Graph {
    public:
        Graph(Options options);
        Graph(float **adjacencyMatrix, int numVertices);
        virtual ~Graph();

        void Init();

        pair<int, int>* GetVerticesOnEdge(int edgeA); // always returns two vertices

        Path* GetShortestPathBetweenVertices(int startVertex, int endVertex);
        Path* GetShortestPathBetweenEdges(int edgeA, int edgeB);

        int numVertices;
        int numEdges;
    private:
        void SetGraphFromFile(string file);

        int** adjacencyMatrix; // for storing weighted graph

        void CalculateNumberOfEdges();
        map<int, map<int, Path>> cachedShortestPaths; // for storing the path results from dijkstra's algorithm
        map<int, map<int, Path>> cachedShortestPathBetweenEdges; // for storing the shortest paths between two edges
        map<int, pair<int, int>> cachedVerticesOnEdge; // for storing the association between edges and vertices

        int MinDistance(int dist[], bool sptSet[]);
        void Dijkstras(int startVertex);

};


#endif //SRC_GRAPH_H
