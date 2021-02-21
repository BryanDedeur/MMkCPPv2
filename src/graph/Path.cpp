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

// checks if the vertex path, edge path, and cost all make sense
bool Path::SanityCheckPass() {
    if (vertexPath.size() > 1 && edgePath.size() > 0) {
        float tempCost = 0;
        for (int i = 0; i < vertexPath.size() - 1; i++) {
            if (!graph->IsValidEdge(vertexPath[i], vertexPath[i + 1])) {
                cout << "Invalid edge found" << endl;
                return false;
            }
            if (graph->GetEdge(vertexPath[i], vertexPath[i + 1]).id != edgePath[i].id) {
                cout << "Invalid vertex found" << endl;
                return false;
            }
            tempCost += edgePath[i].cost;
        }
        if (tempCost != cost) {
            cout << "Invalid cost" << endl;
            return false;
        }
    }
    return true;
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

void Path::InjectShortestPathToVertex(int& vertex, Path& shortestPath) {
    for (int i = 0; i < shortestPath.vertexPath.size(); i++) {
        AddVertex(shortestPath.vertexPath[i]);
    }
}

void Path::HandleFirstVertexNoEdges(int& vertex) {
    vertexPath.push_back(vertex);
}

void Path::HandleFirstVertexOneEdge(int& vertex) {
    vertexPath.push_back(vertex);
    vertexPath.push_back(graph->GetOppositeVertexOnEdge(vertex, edgePath.back()));
}

void Path::HandleSecondVertexNoEdges(int& vertex) {
    if (vertex != vertexPath.back()) {
        edgePath.push_back(graph->GetEdge(vertexPath.back(), vertex));
        cost += edgePath.back().cost;
        vertexPath.push_back(vertex);
    }
}

void Path::HandleAllOtherVertexCases(int& vertex) {
    if (vertex != vertexPath.back()) {
        if (graph->IsValidEdge(vertexPath.back(), vertex)) {
            Edge edge = graph->GetEdge(vertexPath.back(), vertex);
            edgePath.push_back(edge);
            vertexPath.push_back(vertex);
            cost += edge.cost;
        } else {
            InjectShortestPathToVertex(vertex, *graph->GetShortestPathBetweenVertices(vertexPath.back(), vertex));
        }
    }
}

// Adds a vertex and resolves the path
void Path::AddVertex(int& vertex) {
    if (vertexPath.size() == 0 && edgePath.size() == 0) {
        HandleFirstVertexNoEdges(vertex);
    } else if (vertexPath.size() == 0 && edgePath.size() == 1) {
        HandleFirstVertexOneEdge(vertex);
    } else if (vertexPath.size() == 1 && edgePath.size() == 0) {
        HandleSecondVertexNoEdges(vertex);
    } else if (vertexPath.size() > 0 && edgePath.size() > 0) {
        HandleAllOtherVertexCases(vertex);
    }
}

void Path::InjectShortestPathToEdge(Edge& edge, Path& shortestPath) {
    for (int i = 0; i < shortestPath.edgePath.size(); i++) {
        AddEdge(shortestPath.edgePath[i]);
    }
    AddEdge(edge);
}

void Path::HandleFirstEdgeNoStartingVertex(Edge& edge) {
    edgePath.push_back(edge);
    cost += edge.cost;
}

void Path::HandleFirstEdgeWithStartingVertex(Edge& edge) {
    if (!(edge.vertexA == vertexPath.back() || edge.vertexB == vertexPath.back())) {
        InjectShortestPathToEdge(edge, *graph->GetShortestPathBetweenVertexAndEdge(vertexPath.back(), edge));
    }
    else {
        edgePath.push_back(edge);
        vertexPath.push_back(graph->GetOppositeVertexOnEdge(vertexPath.back(), edge));
        cost += edge.cost;
    }
}

void Path::HandleSecondEdgeNoStartingVertex(Edge& edge) {
    if (!graph->EdgesAreConnectedByVertex(edge, edgePath.back())) {
        InjectShortestPathToEdge(edge, *graph->GetShortestPathBetweenEdges(edgePath.back(), edge));
    }
    else {
        int sharedVertex = graph->GetEdgesConnectingVertex(edgePath.back(), edge);
        int startVertex = graph->GetOppositeVertexOnEdge(sharedVertex, edgePath.back());
        vertexPath.push_back(startVertex);
        vertexPath.push_back(sharedVertex);
        edgePath.push_back(edge);
        vertexPath.push_back(graph->GetOppositeVertexOnEdge(sharedVertex, edgePath.back()));
        cost += edge.cost;
    }
}

void Path::HandleAllOtherEdgeCases(Edge& edge) {
    if (!graph->EdgesAreConnectedByVertex(edge, edgePath.back())) {
        InjectShortestPathToEdge(edge, *graph->GetShortestPathBetweenEdges(edgePath.back(), edge));
    }
    else {
        if (edge.id != edgePath.back().id) {
            int sharedVertex = graph->GetEdgesConnectingVertex(edgePath.back(), edge);
            if (sharedVertex != vertexPath.back()) {
                if (!graph->IsValidEdge(vertexPath.back(), sharedVertex))
                    cout << "HELP" << endl;
                vertexPath.push_back(sharedVertex);
                cost += edgePath.back().cost;
                edgePath.push_back(edgePath.back());
            }
        }

        // add any other edge
        int oppositeVertex = graph->GetOppositeVertexOnEdge(vertexPath.back(), edge);
        if (!graph->IsValidEdge(vertexPath.back(), oppositeVertex))
            cout << "HELP" << endl;
        vertexPath.push_back(oppositeVertex);
        edgePath.push_back(edge);
        cost += edge.cost;
    }
}

// Adds a edge and resolves the path
void Path::AddEdge(Edge& edge) {
    if (vertexPath.size() == 0 && edgePath.size() == 0) { 
        HandleFirstEdgeNoStartingVertex(edge);
    } else if (vertexPath.size() == 1 && edgePath.size() == 0) {
        HandleFirstEdgeWithStartingVertex(edge);
    } else if (vertexPath.size() == 0 && edgePath.size() == 1) { 
        HandleSecondEdgeNoStartingVertex(edge);
    } else {
        HandleAllOtherEdgeCases(edge);
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