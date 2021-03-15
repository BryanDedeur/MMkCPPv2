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
        int largestNumEdgesConnectedToAnyVertex;


        // operator overrides
        friend ostream& operator<<(ostream& os, const Graph& graph);

        Path* GetShortestPathBetweenVertices(const int& startVertex, const int& endVertex);
        Path* GetShortestPathBetweenEdges(Edge& edgeA, Edge& edgeB);
        Path* GetShortestPathBetweenVertexAndEdge(int& vertex, Edge& edge);

        Edge GetEdge(int& id);
        Edge GetEdge(int& vertexA, int& vertexB);

        float& GetEdgeCost(int& vertexA, int& vertexB);

        int& GetOppositeVertexOnEdge(int& vertex, Edge& edge);
        int GetEdgesConnectingVertex(Edge& edgeA, Edge& edgeB);

        bool IsValidEdge(int& startVertex, int& endVertex);
        bool EdgesAreConnectedByVertex(Edge& edgeA, Edge& edgeB);

        vector<Edge*> GetEdgesConnectedToVertex(int& vertex);

        void OutputToFile(string file);

        void AddEdgeToAdjMatrix(int& v1, int& v2, float cost);
        void AddEdgeToEdges(int& v1, int& v2, float cost);

        string graphName;

    private:
        string graphFile;

        map<int, map<int, float>> adjacencyMatrix;
        map<int, Edge> edges;

        map<int, map<int, Path*>> cachedShortestPaths;
        map<int, map<int, Path*>> cachedShortestPathBetweenEdges;
        map<int, map<int, Path*>> cachedShortestPathBetweenVerticesAndEdges;
        map<int, map<int, int>> cachedVertexToEdgeID;
        map<int, map<int, int>> cachedNeighborEdges;
        map<int, vector<Edge*>> cachedVertexEdges;


        // file reading
        void SetGraphFromFile(string file);
        void ReadCSVFormat(string file);
        void ReadDATFormat(string file);
        void ReadTXTFormat(string file);

        void WriteCacheFile(string file);
        void ReadCacheFile(string file);

        float MinDistance(vector<float> dist, vector<bool> visited);
        void ComputeDijkstras();

        void FindShortestPathsBetweenEdges();
        void FindShortestPathsBetweenVerticesAndEdges();
        void FindAllVertexToEdgeIDs();
        void FindAllNeighboringEdges();
        void FindVertexEdges();

        void CacheExpensiveComputations();


};


#endif //SRC_GRAPH_H
