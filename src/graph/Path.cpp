//
// Created by Bryan Dedeurwaerder on 11/3/2020.
//

#include "Path.h"
#include "Graph.h"

#include <climits>

Path::Path() : vertexPath(), cost(0), graph(nullptr) {}

Path::Path(Graph* gph) : vertexPath(), cost(0), graph(gph) {

} 

Path::Path(Graph* gph, int& vertexStart) : vertexPath(), cost(0), graph(gph) {
    AddVertex(vertexStart);
}

Path::Path(Graph* gph, int& vertexStart, int& vertexEnd) : vertexPath(), cost(0), graph(gph) {
    AddVertex(vertexStart);
    AddVertex(vertexEnd);
}

Path::Path(Graph* gph, Edge& edgeStart) : vertexPath(), cost(0), graph(gph) {
    AddEdge(edgeStart);
}

Path::Path(Graph* gph, Edge& edgeStart, Edge& edgeEnd) : vertexPath(), cost(0), graph(gph) {
    AddEdge(edgeStart);
    AddEdge(edgeEnd);
}

void Path::Reset() {
    cost = 0;
    vertexPath.clear();
    edgePath.clear();
}

// Add the vertex regardless if the path makes sense
void Path::InsertVertex(int& vertexId) {
    if (vertexPath.size() == 0 && edgePath.size() == 0) {
        vertexPath.push_back(vertexId);
    }
    else if (vertexPath.size() > 0 && edgePath.size() == 0 && vertexId != vertexPath.back()) {
        edgePath.push_back(graph->GetEdge(vertexId, vertexPath.back()));
        vertexPath.push_back(vertexId);
        cost += edgePath.back().cost;
    }
    else if (vertexPath.size() > 0 && edgePath.size() > 0 && vertexId != vertexPath.back()) {
        edgePath.push_back(graph->GetEdge(vertexId, vertexPath.back()));
        vertexPath.push_back(vertexId);
        cost += edgePath.back().cost;
    }
}

// Adds a vertex and resolves the path
void Path::AddVertex(int& vertexId) {
    if (vertexPath.size() == 0 && edgePath.size() == 0) {
        vertexPath.push_back(vertexId);
    }
    else if (vertexId != vertexPath.back()) {
        if (graph->IsValidEdge(vertexPath.back(), vertexId)) {
            Edge edge = graph->GetEdge(vertexPath.back(), vertexId);
            edgePath.push_back(edge);
            vertexPath.push_back(vertexId);
            cost += edge.cost;
        }
        else {
            Path* shortestPath = graph->GetShortestPathBetweenVertices(vertexPath.back(), vertexId);
            for (int i = 0; i < shortestPath->vertexPath.size(); i++) {
                AddVertex(shortestPath->vertexPath[i]);
            }
        }
    }
}

// Adds a edge and resolves the path
void Path::AddEdge(Edge& edge) {
    if (vertexPath.size() == 0 && edgePath.size() == 0) { 
        // add first edge
        edgePath.push_back(edge);
        cost += edge.cost;
    }
    else if (vertexPath.size() == 1 && edgePath.size() == 0) {
        if (edge.vertexA == vertexPath.back() || edge.vertexB == vertexPath.back()) {
            edgePath.push_back(edge);
            vertexPath.push_back(graph->GetOppositeVertexOnEdge(vertexPath.back(), edge));
            cost += edge.cost;
        }
        else {
            Path* shortestPath = graph->GetShortestPathBetweenVertexAndEdge(vertexPath.back(), edge);
            for (int i = 0; i < shortestPath->edgePath.size(); i++) {
                AddEdge(shortestPath->edgePath[i]);
            }
            //AddEdge(edge);
        }
    } 
    else if (vertexPath.size() == 0 && edgePath.size() > 0) { 
        if (!graph->EdgesAreConnectedByVertex(edge, edgePath.back())) {
            // fill in the path
            Path* shortestPath = graph->GetShortestPathBetweenEdges(edgePath.back(), edge);
            for (int i = 0; i < shortestPath->edgePath.size(); i++) {
                AddEdge(shortestPath->edgePath[i]);
            }
            //AddEdge(edge);
        }
        else {
            // add second edge, repair starting vertex
            int sharedVertex = graph->GetEdgesConnectingVertex(edgePath.back(), edge);
            // find opposite from shared vertex
            int startVertex = graph->GetOppositeVertexOnEdge(sharedVertex, edgePath.back());
            // add to vertex path
            vertexPath.push_back(startVertex);
            vertexPath.push_back(sharedVertex);
            edgePath.push_back(edge);
            vertexPath.push_back(graph->GetOppositeVertexOnEdge(sharedVertex, edgePath.back()));
            cost += edge.cost;
        }
    } else if (vertexPath.size() > 0 && edgePath.size() > 0) {
        if (!graph->EdgesAreConnectedByVertex(edge, edgePath.back())) {
            // fill in the path
            Path* shortestPath = graph->GetShortestPathBetweenEdges(edgePath.back(), edge);
            for (int i = 0; i < shortestPath->edgePath.size(); i++) {
                AddEdge(shortestPath->edgePath[i]);
            }
            //AddEdge(edge);
        }

        int sharedVertex = graph->GetEdgesConnectingVertex(edgePath.back(), edge);
        if (sharedVertex != vertexPath.back()) {
            vertexPath.push_back(sharedVertex);
            edgePath.push_back(edgePath.back());
            cost += edge.cost;
        }

        // add any other edge
        int oppositeVertex = graph->GetOppositeVertexOnEdge(vertexPath.back(), edge);
        vertexPath.push_back(oppositeVertex);
        edgePath.push_back(edge);
        cost += edge.cost;

    }
}

vector<Edge> Path::GetEdgePath() {
    return edgePath;
}

vector<int> Path::GetVertexPath() {
    return vertexPath;
}


const float Path::GetCost() {
    return cost;
}

ostream& operator<<(ostream& os, const Path& path) {
    os << "Vertex Path (" << path.vertexPath.size() << "): ";
    for (int i = 0; i < path.vertexPath.size(); i++) {
        if (i != path.vertexPath.size() - 1) {
            os << path.vertexPath[i] << ", ";
        }
        else {
            os << path.vertexPath[i] << endl;
        }
    }
    os << "Edge Path (" << path.edgePath.size() << "): ";
    for (int i = 0; i < path.edgePath.size(); i++) {
        if (i != path.edgePath.size() - 1) {
            os << path.edgePath[i].id << ", ";
        }
        else {
            os << path.edgePath[i].id << endl;
        }
    }
    os << "Path Cost: " << path.cost << endl;
    return os;
}

Path& Path::operator=(Path other) { // Assignment operator copying struct
    //this->vertexPath.clear();
    //for (const int& itr : other.vertexPath) {
    //    int it = itr;
    //    this->vertexPath.push_back(it);
    //}
    //this->cost = other.cost;
    return *this;
}

// assignment operator override to help with combining vertexPaths together
Path& Path::operator+=(const Path &rhsPath) {
    //for (const int& itr : rhsPath.vertexPath) {
    //    int it = itr;
    //    if (!this->vertexPath.empty()) {
    //        if (it != this->vertexPath.back()) {
    //            this->vertexPath.push_back(it);
    //        }
    //    } else {
    //        this->vertexPath.push_back(it);
    //    }
    //}
    //this->cost += rhsPath.cost;
    return *this;
}

//// assignment operator override to help with combining vertexPaths together
//Path& Path::operator+(const Path &rhsPath) {
//    Path newPath = Path(0);
//    // TODO fix this
//    if (!this->vertexPath.empty()) {
//        for (const int& itr : this->vertexPath) {
//            newPath.vertexPath.push_back(itr);
//        }
//    }
//
//    if (!rhsPath.vertexPath.empty()) {
//        for (const int& itr : rhsPath.vertexPath) {
//            newPath.vertexPath.push_back(itr);
//        }
//    }
//
//    newPath = rhsPath.cost + this->cost;
//    return newPath;
//}