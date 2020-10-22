//
// By Bryan D.
// Created: 10/15/2020
//

#include "Graph.h"

// Graph Constructor
Graph::Graph(Options options) {
    // TODO load graph from file options.datafile

    // Below is just a test
    const int numVerti = 10;
    // created with https://graphonline.ru/en/
    int** testGraph = (int **) malloc(numVerti * sizeof(int*));
    for (int i = 0; i < numVerti; i++) {
        testGraph[i] = (int *) malloc(numVerti * sizeof(int));
    }

    int exampleGraph[numVerti][numVerti] =
            {{0, 5, 7, -1, -1, -1, -1, -1, -1, -1},
             {5, 0, -1, 7, -1, -1, -1, 11, -1, -1},
             {7, -1, 0, 3, -1, -1, -1, -1, 11, -1},
             {-1, 7, 3, 0, 5, 5, -1, -1, -1, 1},
             {-1, -1, -1, 5, 0, -1, 11, 3, -1, -1},
             {-1, -1, -1, 5, -1, 0, 3, -1, 1, -1},
             {-1, -1, -1, -1, 11, 3, 0, -1, -1, -1},
             {-1, 11, -1, -1, 3, -1, -1, 0, -1, -1},
             {-1, -1, 11, -1, -1, 1, -1, -1, 0, -1},
             {-1, -1, -1, 1, -1, -1, -1, -1, -1, 0}};

    for (int i = 0; i < numVerti; i++) {
        for (int j = 0; j < numVerti; j++) {
            testGraph[i][j] = exampleGraph[i][j];
        }
    }

    setAdjacencyMatrix(testGraph, numVerti);
    calculateNumberOfEdges();
}

// Graph Constructor
// @param adjMatrix is an existing multi dim array
// @param numVerti is the number of vertices on the graph
Graph::Graph(int **adjMatrix, int numVerti) {
    setAdjacencyMatrix(adjMatrix, numVerti);
    calculateNumberOfEdges();
}


Graph::~Graph() {

}

// For debugging
void Graph::print() {
    std::cout << "Graph Adjacency Matrix:" << std::endl;
    for (int i = 0; i < numVertices; i++) {
        std::cout << "";
        for (int j = 0; j < numVertices; j++) {
            std::cout << adjacencyMatrix[i][j] << ", ";
        }
        std::cout << std::endl;
    }

}

// SetMatrix is utilized by initializer and constructor functions to set the class graph data
void Graph::setAdjacencyMatrix(int **otherMatrix, int numVerti) {

    numVertices = numVerti;

    adjacencyMatrix = new int*[numVerti];
    for (int i = 0; i < numVerti; i++) {
        adjacencyMatrix[i] = new int[numVerti];
        for (int j = 0; j < numVerti; j++) {
            adjacencyMatrix[i][j] = otherMatrix[i][j];
        }
    }
}

void Graph::calculateNumberOfEdges() {
    numEdges = 0;
    for (int i = 0; i < numVertices; i++) {
        for (int j = i; j < numVertices; j++) {
            // if weight is greater than 0 then valid edge
            if (adjacencyMatrix[i][j] > 0) {
                numEdges ++;
            }
        }
    }
}

void Graph::Init() {
    //cacheShortestPaths();
    // TODO implement, not sure what would be best for this though
}

const int Graph::getNumVertices() {
    return numVertices;
}

const int Graph::getNumEdges() {
    return numEdges;
}

int* Graph::getVerticesOnEdge(int edgeA) {
    int vertices[NUM_VERTICES_PER_EDGE];
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
    int* verticesOnEdgeA = getVerticesOnEdge(edgeA);
    int* verticesOnEdgeB = getVerticesOnEdge(edgeB);

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




