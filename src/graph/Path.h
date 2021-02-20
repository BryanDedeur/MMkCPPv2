//
// Created by Bryan on 11/3/2020.
//

#ifndef GA_PATH_H
#define GA_PATH_H

#include "Edge.h"
#include <ostream>
#include <vector>

using std::vector;
using std::ostream;

class Graph; // forward declaration

class Path {
    public:
        Path();
        Path(Graph* graph);
        Path(Graph* gph, int& vertexStart);
        Path(Graph* graph, int& vertexStart, int& vertexEnd);
        Path(Graph* graph, Edge& edgeStart, Edge& edgeEnd);
        Path(Graph* gph, Edge& edgeStart);
        Path(Graph* graph, Edge& edgeStart, int& startVertex);

        void Reset();

        vector<int> vertexPath;
        vector<Edge> edgePath;

        void InsertVertex(int& vertexId);
        void AddVertex(int& vertexId);
        void AddEdge(Edge &edgeId);

        vector<Edge> GetEdgePath();
        vector<int> GetVertexPath();

        const float GetCost();


        friend ostream& operator<<(ostream& os, const Path& path);

        Path& operator=(Path other);

        // assignment operator override to help with combining paths together
        Path& operator+=(const Path &rhsPath);
        Path& operator+(const Path &rhsPath);

    private:
        Graph* graph;
        float cost; // total cost to travel the path

};


#endif //GA_PATH_H
