//
// Created by bryan on 10/15/20.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "Options.h"
#include <iostream>


struct Path {
    int* path; // list of vertices
    int cost; // total cost to travel path
};

const int NUM_VERTICES_PER_EDGE = 2;

class Graph {
    public:
        Graph(Options options);
        Graph(int **adjacencyMatrix, int numVertices);
        virtual ~Graph();

        void Init();

        const int getNumVertices();
        const int getNumEdges();

        int* getVerticesOnEdge(int edgeA);

        Path* getShortestPathBetweenVertices(int vertexA, int vertexB);
        Path* getShortestPathBetweenEdges(int edgeA, int edgeB);

        void print();

    private:
        int numVertices;
        int numEdges;
        int** adjacencyMatrix; // for storing weighted graph

        void setAdjacencyMatrix(int** otherMatrix, int numVerti);
        void calculateNumberOfEdges();
        Path*** cachedShortestPaths; // for storing the path results from dijkstra's algorithm
        // dim 1 index: starting vertex
        // dim 2 index: ending vertex
        // dim 3 index: path struct containing path and cost

        void dijkstras(int startVertex);

        //void cacheShortestPaths(); // dijkstra's only cache as we encounter the need for calcuating
};


#endif //SRC_GRAPH_H
