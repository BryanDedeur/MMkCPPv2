//
// Created by bryan on 10/15/20.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "Options.h"
#include "Utils.h"
#include "Const.h"
#include "Path.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;

//const int NUM_VERTICES_PER_EDGE = 2;
//const int MAX_NUM_VERTICES = 100;

class Graph {
    public:
        Graph(Options* options);

        virtual ~Graph();

        void Init();

        // operator overrides
        friend ostream& operator<<(ostream& os, const Graph& graph);

        pair<int, int>* GetVerticesOnEdge(int& edgeA); // always returns two vertices

        Path* GetShortestPathBetweenVertices(const int& startVertex, const int& endVertex);
        Path* GetShortestPathBetweenEdges(int& edgeA, int& edgeB);
        Path* GetShortestPathBetweenVertexAndEdge(int& vertex, int& edge);
        float& GetEdgeCost(int& vertexA, int& vertexB);
        int& GetEdgeId(int& vertexA, int& vertexB);

        int& GetOppositeVertexOnEdge(int& vertex, int& edge);

        bool IsValidEdge(int& startVertex, int& endVertex);

        int& GetEdgesConnectedToVertex(int& vertex);
        void OutputToFile(string file);

        int numVertices;
        int numEdges;
        float sumEdges;


    private:
        float adjacencyMatrix[MAX_VERTICES][MAX_VERTICES]; // for storing weighted graph
        int MinDistance(float dist[], bool sptSet[]);

        Path cachedShortestPaths[MAX_VERTICES][MAX_VERTICES]; // for storing the path results from dijkstra's algorithm
        Path cachedShortestPathBetweenEdges[MAX_EDGES][MAX_EDGES]; // for storing the shortest paths between two edges
        pair<int, int> cachedVerticesOnEdge[MAX_EDGES]; // for storing the association between edges and vertices

        void SetGraphFromFile(string file);

        void CalculateNumberOfEdges();

        void Dijkstras(int startVertex);

};


#endif //SRC_GRAPH_H
