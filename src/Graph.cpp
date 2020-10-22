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

int* Graph::getVertices(int edgeA) {
    int vertices[2];
    return vertices;
}


Path* Graph::getShortestPathBetweenVertices(int startVertexA, int endVertexB) {
    // if path from a to b is cached
        // get cache
    // if not cached
        // compute dijkstra's
    Path* path = new Path();
    return path;
}

Path* Graph::getShortestPathBetweenEdges(int edgeA, int edgeB) {
    int* verticesOnEdgeA = getVertices(edgeA);
    int* verticesOnEdgeB = getVertices(edgeB);

    Path* bestPath = nullptr;

    for (int i = 0; i < NUM_VERTICES_PER_EDGE; i++) {
        for (int j = 0; j < NUM_VERTICES_PER_EDGE; j++) {
            Path* tempPath = getShortestPathBetweenVertices(verticesOnEdgeA[i], verticesOnEdgeB[j]);
            if (bestPath == nullptr || bestPath->cost > tempPath->cost) {
                bestPath = tempPath;
            }
        }
    }
    return bestPath;
}

void Graph::dijkstras(int startVertex) {

}




