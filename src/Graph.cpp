//
// By Bryan D.
// Created: 10/15/2020
//

#include "Graph.h"

// Graph Constructor
// @param adjMatrix is an existing multi dim array
// @param numVerti is the number of vertices on the graph
Graph::Graph(int **adjMatrix, int numVerti) : numVertices(numVerti) {
    // deep copy adjMatrix param to class adjacency matrix
    adjacencyMatrix = new int*[numVerti];
    for (int i = 0; i < numVerti; i++) {
        adjacencyMatrix[i] = new int[numVerti];
        for (int j = 0; j < numVerti; j++) {
            adjacencyMatrix[i][j] = adjMatrix[i][j];
        }
    }
}


Graph::~Graph() {

}

void Graph::Init() {
    //cacheShortestPaths();
}

int *Graph::getShortestPathBetweenVertices(int startVertexA, int endVertexB) {
    // if path from a to b is cached
        // get cache
    // if not cached
        // compute dijkstra's

    return nullptr;
}

int *Graph::getShortestPathBetweenEdges(int edgeA, int edgeB) {
    // for each vertex in edge A
    for (int vertA : getVertices(edgeA)) {
        // find a path to each vertex in edge B
        for (int vertB : getVertices(edgeB)) {
            getShortestPathBetweenVertices(vertA, vertB)
        }
    }
    return nullptr;
}

void Graph::dijkstras(int startVertex) {

}




