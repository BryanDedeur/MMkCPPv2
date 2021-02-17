//
// Created by bryan on 10/15/20.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "../Utils.h"
#include "Path.h"
#include "Edge.h"

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Graph {
    public:
        Graph(string filename);

        virtual ~Graph();

        int numVertices;
        int numEdges;
        float sumEdges;

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

        void OutputToFile(string file);

        void AddEdgeToAdjMatrix(int& v1, int& v2, float cost);
        void AddEdgeToEdges(int& v1, int& v2, float cost);

    private:
        map<int, map<int, float>> adjacencyMatrix;
        map<int, Edge> edges;

        map<int, map<int, Path>> cachedShortestPaths;
        map<int, map<int, Path>> cachedShortestPathBetweenEdges;
        map<int, map<int, Path>> cachedShortestPathBetweenVerticesAndEdges;
        map<int, map<int, int>> cachedVertexToEdgeID;


        // file reading
        void SetGraphFromFile(string file);
        void ReadCSVFormat(string file);
        void ReadDATFormat(string file);
        void ReadTXTFormat(string file);

        float MinDistance(vector<float> dist, vector<bool> visited);
        void ComputeDijkstras();

        void FindShortestPathsBetweenEdges();
        void FindShortestPathsBetweenVerticesAndEdges();
        void FindAllVertexToEdgeIDs();

        void CacheExpensiveComputations();


};


#endif //SRC_GRAPH_H
