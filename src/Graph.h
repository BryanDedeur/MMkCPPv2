//
//
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph {
private:
    int[][] adjacencyMatrix; // for storing weighted graph
    int[][] shortestPaths; // for storing the results from dijkstras algorithm

    void computeShortestPaths();

public:
    Graph(int numberOfVertices);
    Graph(int[][] adjacencyMatrix);

    virtual ~Graph();

    void addEdge(int vertexA, int vertexB, int weight);

    // void removeEdge(); not so important now

    int[] getShortestPathBetweenEdges(int edge, int edge);
    int getTravelCost(int vertexA, int vertexB);
};


#endif //GRAPH_H
