/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Jonathan Peters
 * @Date: 10/18/20
 */

#include "Graph.h"

using namespace std;

// Graph Constructor
Graph::Graph(string filename) : cachedShortestPaths(), adjacencyMatrix(), numEdges(0), numVertices(0), sumEdges(0) {

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
    fstream readFile;
    readFile.open(file, ios::in );

    if (!readFile.is_open()) {
        AssertWithErrorMessage("Cannot locate file: " + file, readFile.is_open());
        return;
    } else {
        string fileFormat = ExtractFileFormat(file);

        if (fileFormat == ".csv") {
            ReadCSVFormat(file);
        } else if (fileFormat == ".dat") {
            ReadDATFormat(file);
        } else if (fileFormat == ".txt") {
            ReadTXTFormat(file);
        }
    }
    readFile.close();
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

pair<int, int>* Graph::GetVerticesOnEdge(int& edge) {
    return &edges[edge].vpair;
}


Path* Graph::GetShortestPathBetweenVertices(const int& startVertex, const int& endVertex) {
    return &cachedShortestPaths[startVertex][endVertex];
}

// TODO return a tuple containing vertex to start from
Path* Graph::GetShortestPathBetweenEdges(int& edgeA, int& edgeB) {
    return &cachedShortestPathBetweenEdges[edgeA][edgeB];
}

Path* Graph::GetShortestPathBetweenVertexAndEdge(int& vertex, int& edge) {
    return &cachedShortestPathBetweenVerticesAndEdges[vertex][edge];
}


float& Graph::GetEdgeCost(int& vertexA, int& vertexB) {
    return adjacencyMatrix[vertexA][vertexB];
}

int& Graph::GetEdgeId(int& va, int& vb) {
    return cachedVertexToEdgeID[va][vb];
}

int& Graph::GetOppositeVertexOnEdge(int& vertex, int& edge) {
    if (edges[edge].vpair.first == vertex) {
        return edges[edge].vpair.second;
    }

    return edges[edge].vpair.first;
}

bool Graph::IsValidEdge(int& startVertex, int& endVertex) {
    return GetEdgeCost(startVertex, endVertex) > 0;
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
        cachedShortestPaths[startVertex][startVertex] = Path(0);
        cachedShortestPaths[startVertex][startVertex].path = paths[startVertex];

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

                    cachedShortestPaths[startVertex][v] = Path(dist[v]);
                    cachedShortestPaths[startVertex][v].path = paths[v];
                }
            }
        }
    }
}

void Graph::FindShortestPathsBetweenEdges() {
    for (int edgeA = 0; edgeA < numEdges; edgeA++) {
        for (int edgeB = 0; edgeB < numEdges; edgeB++) {
            pair<int, int>* verticesOnEdgeA = GetVerticesOnEdge(edgeA);
            pair<int, int>* verticesOnEdgeB = GetVerticesOnEdge(edgeB);

            Path* bestPath = GetShortestPathBetweenVertices(verticesOnEdgeA->first, verticesOnEdgeB->first);
            Path* tempPath = GetShortestPathBetweenVertices(verticesOnEdgeA->first, verticesOnEdgeB->second);
            if (bestPath->cost > tempPath->cost)
                bestPath = tempPath;
            tempPath = GetShortestPathBetweenVertices(verticesOnEdgeA->second, verticesOnEdgeB->first);
            if (bestPath->cost > tempPath->cost)
                bestPath = tempPath;
            tempPath = GetShortestPathBetweenVertices(verticesOnEdgeA->second, verticesOnEdgeB->second);
            if (bestPath->cost > tempPath->cost)
                bestPath = tempPath;

            cachedShortestPathBetweenEdges[edgeA][edgeB] = *bestPath;
        }
    }
}

void Graph::FindShortestPathsBetweenVerticesAndEdges() {
    for (int vertex = 0; vertex < numVertices; vertex++) {
        for (int edge = 0; edge < numEdges; edge++) {
            pair<int, int>* verticesOnEdge = GetVerticesOnEdge(edge);
            if (cachedShortestPaths[vertex][verticesOnEdge->first].cost < cachedShortestPaths[vertex][verticesOnEdge->second].cost) {
                cachedShortestPathBetweenVerticesAndEdges[vertex][edge] = cachedShortestPaths[vertex][verticesOnEdge->first];
            }
            else {
                cachedShortestPathBetweenVerticesAndEdges[vertex][edge] = cachedShortestPaths[vertex][verticesOnEdge->second];
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

void Graph::CacheExpensiveComputations() {
    // Compute dijkstras shortest paths for all vertices
    ComputeDijkstras();

    // Find shortest paths between all edges
    FindShortestPathsBetweenEdges();

    // Find shortest paths between all vertices and edges
    FindShortestPathsBetweenVerticesAndEdges();

    // Find all vertex edge associations
    FindAllVertexToEdgeIDs();
}





