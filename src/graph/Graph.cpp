/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Jonathan Peters
 * @Date: 10/18/20
 */

#include "Graph.h"

using namespace std;

// Graph Constructor
Graph::Graph(string filename) : numEdges(0), numVertices(0), sumEdges(0) {

    SetGraphFromFile(filename);
    CacheExpensiveComputations();
}

Graph::~Graph() {
    //TODO auto generated destructor tab
}

ostream& operator<<(ostream& os, const Graph& graph) {
    os << "Graph: costs to get to any vertex" << endl;
    for (int i = 0; i < graph.numVertices; i++) {
        for (int j = 0; j < graph.numVertices; j++) {
            if (j == graph.numVertices - 1) {
                //os << graph.adjacencyMatrix[i][j];
            }
            else {
                //os << graph.adjacencyMatrix[i][j] << ",";
            }
        }
        os << endl;
    }
    return os;
}

void Graph::AddEdgeToAdjMatrix(int& v1, int& v2, float cost) {
    adjacencyMatrix[v1][v2] = cost;
    adjacencyMatrix[v2][v1] = cost;
}

void Graph::AddEdgeToEdges(int& v1, int& v2, float cost) {
    edges[numEdges] = Edge(numEdges, v1, v2, cost);

    if (v1 + 1 > numVertices) {
        numVertices = v1 + 1;
    } 
    
    if (v2 + 1 > numVertices) {
        numVertices = v2 + 1;
    }

    numEdges++;
    sumEdges += cost;
}

void Graph::SetGraphFromFile(string file) {
    if (FileExists(file)) {
        string fileFormat = ExtractFileFormat(file);

        if (fileFormat == ".csv") {
            ReadCSVFormat(file);
        }
        else if (fileFormat == ".dat") {
            ReadDATFormat(file);
        }
        else if (fileFormat == ".txt") {
            ReadTXTFormat(file);
        }
    }
    
    graphFile = file;
    graphName = ExtractNameOfFile(file);
}

void Graph::ReadCSVFormat(string file) {
    vector<string> lines = SplitFileByLines(file);
    int v1 = 0;
    for (string line : lines) {
        int v2 = 0;
        vector<float> numbers = ExtractNumbers(line);
        for (float number : numbers) {
            if (v2 > v1) { // ignore everything on other side of diagonal
                float cost = float(number);
                AddEdgeToAdjMatrix(v1, v2, cost);
                if (cost > 0) {
                    AddEdgeToEdges(v1, v2, cost);
                }
            }

            v2++;
        }
        v1++;
    }
}

void Graph::ReadDATFormat(string file) {
    vector<string> lines = SplitFileByLines(file);
    int count = 0;
    for (string line : lines) {
        count++;
        if (count > 10) { // reading edges
            vector<float> numbers = ExtractNumbers(line);
            if (numbers.size() > 2) { // this is a edge not the last line in the file
                int v1 = int(numbers[0]) - 1;
                int v2 = int(numbers[1]) - 1;
                float cost = float(numbers[2]);

                AddEdgeToAdjMatrix(v1, v2, cost);
                AddEdgeToEdges(v1, v2, cost);
            }
        }
    }
}

void Graph::ReadTXTFormat(string file) {
    vector<string> lines = SplitFileByLines(file);
    int count = 0;
    for (string line : lines) {
        count++;
        if (count > 3) { // reading edges
            vector<float> numbers = ExtractNumbers(line);
            if (numbers.size() > 2) { // this is a edge not the last line in the file
                int v1 = int(numbers[0]) - 1;
                int v2 = int(numbers[1]) - 1;
                float cost = float(numbers[2]);

                AddEdgeToAdjMatrix(v1, v2, cost);
                AddEdgeToEdges(v1, v2, cost);
            }
        }
    }
}

void Graph::WriteCacheFile(string file) {
    stringstream ss;
    for (int v1 = 0; v1 < numVertices; v1++) {
        for (int v2 = v1; v2 < numVertices; v2++) {
            if (cachedShortestPaths[v1][v2]->GetCost() != 0) {
                ss << -1 << " " << cachedShortestPaths[v1][v2]->GetCost() << " " << cachedShortestPaths[v1][v2]->vertexPath.size() << endl;
                for (int x = 0; x < cachedShortestPaths[v1][v2]->vertexPath.size(); x++) {
                    ss << cachedShortestPaths[v1][v2]->vertexPath[x] << " ";
                }
                ss << endl;
            }
        }
    }
    WriteToFile(ss, file);
}

void Graph::ReadCacheFile(string file) {
    vector<string> lines = SplitFileByLines(file);
    for (string line : lines) {
        vector<float> numbers = ExtractNumbers(line);
        if (numbers.size() > 0) { 
            if (numbers[0] != -1) {
                // numbers is a vertex list

                int startv = int(numbers.front());
                int endv = int(numbers.back());

                cachedShortestPaths[startv][startv] = new Path(this, startv, startv);
                cachedShortestPaths[endv][endv] = new Path(this, endv, endv);

                cachedShortestPaths[startv][endv] = new Path(this, startv, startv);
                cachedShortestPaths[endv][startv] = new Path(this, endv, endv);

                for (int i = 1; i < numbers.size(); i++) {
                    int v = int(numbers[i]);
                    cachedShortestPaths[startv][endv]->InsertVertex(v);
                    v = int(numbers[numbers.size() - 1 - i]);
                    cachedShortestPaths[endv][startv]->InsertVertex(v);
                }
                cachedShortestPaths[startv][endv]->SanityCheckPass();
                cachedShortestPaths[endv][startv]->SanityCheckPass();
            }
        }
    }
}

void Graph::OutputToFile(string file) {
    stringstream ss;
    ss << numVertices << endl;
    ss << numEdges << endl;
    for (int i = 0; i < numVertices; i++) {
        for (int j = i; j < numVertices; j++) {
            if (adjacencyMatrix[i][j] > 0) {
                ss << i << " " << j << " " << adjacencyMatrix[i][j] << endl;
            }
        }
    }
    WriteToFile(ss, file);
}

Path* Graph::GetShortestPathBetweenVertices(const int& startVertex, const int& endVertex) {
    return cachedShortestPaths[startVertex][endVertex];
}

// TODO return a tuple containing vertex to start from
Path* Graph::GetShortestPathBetweenEdges(Edge& edgeA, Edge& edgeB) {
    return cachedShortestPathBetweenEdges[edgeA.id][edgeB.id];
}

Path* Graph::GetShortestPathBetweenVertexAndEdge(int& vertex, Edge& edge) {
    return cachedShortestPathBetweenVerticesAndEdges[vertex][edge.id];
}

Edge Graph::GetEdge(int& id) {
    return edges[id];
}

Edge Graph::GetEdge(int& va, int& vb) {
    int edgeId = cachedVertexToEdgeID[va][vb];
    return edges[edgeId];
}

float& Graph::GetEdgeCost(int& vertexA, int& vertexB) {
    return adjacencyMatrix[vertexA][vertexB];
}

int& Graph::GetOppositeVertexOnEdge(int& vertex, Edge& edge) {
    if (edge.vpair.first == vertex) {
        return edge.vpair.second;
    }

    return edge.vpair.first;
}

bool Graph::IsValidEdge(int& startVertex, int& endVertex) {
    if (adjacencyMatrix.find(startVertex) != adjacencyMatrix.end()) {
        if (adjacencyMatrix[startVertex].find(endVertex) != adjacencyMatrix[startVertex].end()) {
            return (adjacencyMatrix.at(startVertex).at(endVertex) > 0);
        }
    }
    return false;
}

bool Graph::EdgesAreConnectedByVertex(Edge& edgeA, Edge& edgeB) {
    if (cachedNeighborEdges[edgeA.id][edgeB.id] == -1) {
        return false;
    }
    return true;
}

int Graph::GetEdgesConnectingVertex(Edge& edgeA, Edge& edgeB) {
    return cachedNeighborEdges[edgeA.id][edgeB.id];
}

// utility function for dijkstras
float Graph::MinDistance(vector<float> dist, vector<bool> visited) {
    // Initialize min value
   float min = FLT_MAX, min_index;

    for (int v = 0; v < numVertices; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// dijkstras in this implementation will not return anything because it will add the paths it finds to the cache
void Graph::ComputeDijkstras() {
    for (int startVertex = 0; startVertex < numVertices; startVertex++) {
        vector<float> dist;
        vector<bool> visited;
        vector<vector<int>> paths;

        for (int i = 0; i < numVertices; i++) {
            dist.push_back(FLT_MAX);
            visited.push_back(false);
            paths.push_back(vector<int>());
            paths[i].push_back(startVertex);
        }

        dist[startVertex] = 0;
        cachedShortestPaths[startVertex][startVertex] = new Path(this, startVertex, startVertex);

        for (int count = 0; count < numVertices - 1; count++) {
            int nearestUnvisitedVertex = MinDistance(dist, visited);

            visited[nearestUnvisitedVertex] = true;

            for (int v = 0; v < numVertices; v++) {
                if (!visited[v]     // not visited
                    && 0 < adjacencyMatrix[nearestUnvisitedVertex][v] // edge exists
                    && dist[nearestUnvisitedVertex] != FLT_MAX          // explored
                    && dist[nearestUnvisitedVertex] + adjacencyMatrix[nearestUnvisitedVertex][v] < dist[v]) {

                    dist[v] = dist[nearestUnvisitedVertex] + adjacencyMatrix[nearestUnvisitedVertex][v];

                    paths[v] = paths[nearestUnvisitedVertex];
                    paths[v].push_back(v);

                    cachedShortestPaths[startVertex][v] = new Path(this);
                    for (int i = 0; i < paths[v].size(); i++) {
                        cachedShortestPaths[startVertex][v]->InsertVertex(paths[v][i]);
                    }
                }
            }
        }
    }
}

void Graph::FindShortestPathsBetweenEdges() {
    for (int edgeA = 0; edgeA < numEdges; edgeA++) {
        for (int edgeB = 0; edgeB < numEdges; edgeB++) {
            Edge a = GetEdge(edgeA);
            Edge b = GetEdge(edgeB);

            Path* bestPath = GetShortestPathBetweenVertices(a.vertexA, b.vertexA);
            Path* tempPath = GetShortestPathBetweenVertices(a.vertexA, b.vertexB);
            if (bestPath->GetCost() > tempPath->GetCost())
                bestPath = tempPath;
            tempPath = GetShortestPathBetweenVertices(a.vertexB, b.vertexA);
            if (bestPath->GetCost() > tempPath->GetCost())
                bestPath = tempPath;
            tempPath = GetShortestPathBetweenVertices(a.vertexB, b.vertexB);
            if (bestPath->GetCost() > tempPath->GetCost())
                bestPath = tempPath;

            cachedShortestPathBetweenEdges[edgeA][edgeB] = bestPath;
        }
    }
}

void Graph::FindShortestPathsBetweenVerticesAndEdges() {
    for (int vertex = 0; vertex < numVertices; vertex++) {
        for (int edge = 0; edge < numEdges; edge++) {
            Edge e = GetEdge(edge);
            if (cachedShortestPaths[vertex][e.vertexA]->GetCost() < cachedShortestPaths[vertex][e.vertexB]->GetCost()) {
                cachedShortestPathBetweenVerticesAndEdges[vertex][edge] = cachedShortestPaths[vertex][e.vertexA];
            }
            else {
                cachedShortestPathBetweenVerticesAndEdges[vertex][edge] = cachedShortestPaths[vertex][e.vertexB];
            }
        }
    }
}

void Graph::FindAllVertexToEdgeIDs() {
    for (int edgeId = 0; edgeId < numEdges; edgeId++) {
        cachedVertexToEdgeID[edges[edgeId].vertexA][edges[edgeId].vertexB] = edgeId;
        cachedVertexToEdgeID[edges[edgeId].vertexB][edges[edgeId].vertexA] = edgeId;
    }
}

void Graph::FindAllNeighboringEdges() {
    for (int edgeId = 0; edgeId < numEdges; edgeId++) {
        for (int otherEdgeId = 0; otherEdgeId < numEdges; otherEdgeId++) {
            if (edgeId != otherEdgeId) {
                if (edges[edgeId].vertexA == edges[otherEdgeId].vertexA) {
                    cachedNeighborEdges[edgeId][otherEdgeId] = edges[edgeId].vertexA;
                }
                else if (edges[edgeId].vertexA == edges[otherEdgeId].vertexB) {
                    cachedNeighborEdges[edgeId][otherEdgeId] = edges[edgeId].vertexA;
                }
                else if (edges[edgeId].vertexB == edges[otherEdgeId].vertexA) {
                    cachedNeighborEdges[edgeId][otherEdgeId] = edges[edgeId].vertexB;
                }
                else if (edges[edgeId].vertexB == edges[otherEdgeId].vertexB) {
                    cachedNeighborEdges[edgeId][otherEdgeId] = edges[edgeId].vertexB;
                }
                else {
                    cachedNeighborEdges[edgeId][otherEdgeId] = -1;
                }
            }
        }
    }
}

void Graph::CacheExpensiveComputations() {
    // Find all vertex edge associations
    FindAllVertexToEdgeIDs();

    string cacheFile = "../src/graph/cached/" + graphName + ".cache";
    if (FileExists(cacheFile)) {
        ReadCacheFile(cacheFile);
    } else {
        // Compute dijkstras shortest paths for all vertices
        ComputeDijkstras();
        WriteCacheFile(cacheFile);
    }

    // Find shortest paths between all edges
    FindShortestPathsBetweenEdges();

    // Find shortest paths between all vertices and edges
    FindShortestPathsBetweenVerticesAndEdges();

    // Find all neighboring edges for every edge
    FindAllNeighboringEdges();

}





