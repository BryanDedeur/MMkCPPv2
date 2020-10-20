//
// Created by bryan on 10/15/20.
//

#ifndef GRAPH_H
#define GRAPH_H

class Graph {
    public:
        Graph(int **adjacencyMatrix, int numVertices);
        virtual ~Graph();

        void Init();

        struct Path {
            int* path; // list of vertices
            int cost; // total cost to travel path
        };

    int* getShortestPathBetweenVertices(int vertexA, int vertexB);
        int* getShortestPathBetweenEdges(int edgeA, int edgeB);

    private:

        int numVertices;
        int** adjacencyMatrix; // for storing weighted graph

        Path*** cachedShortestPaths; // for storing the path results from dijkstra's algorithm
        // dim 1 index: starting vertex
        // dim 2 index: ending vertex
        // dim 3 index: path struct containing path and cost


    void dijkstras(int startVertex);

        //void cacheShortestPaths(); // dijkstra's only cache as we encounter the need for calcuating
};


#endif //SRC_GRAPH_H
