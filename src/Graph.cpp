/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Jonathan Peters
 * @Date: 10/18/20
 */

#include "Graph.h"

using namespace std;

// Graph Constructor
Graph::Graph(Options* options) : cachedShortestPaths(), adjacencyMatrix(), numEdges(0), numVertices(0), sumEdges(0) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            adjacencyMatrix[i][j] = 0;
            cachedShortestPaths[i][j] = Path(-1);
        }
    }

    for (int i = 0; i < MAX_EDGES; i++) {
        for (int j = 0; j < MAX_EDGES; j++) {
            cachedShortestPathBetweenEdges[i][j] = Path(-1);
        }
        cachedVerticesOnEdge[i] = make_pair(INT_MAX, INT_MAX);
    }

    SetGraphFromFile(options->graphfile);

    CalculateNumberOfEdges();

    // pre cache everything so we can print it
    for (int i = 0; i < numVertices; i++) {
        Dijkstras(i);
    }
}

Graph::~Graph() {
    //TODO auto generated destructor tab

}

void Graph::Init() {
    //cacheShortestPaths();
    // TODO implement, this would be a good place to cache things ahead of time but not needed because caching happens regardless
}

ostream& operator<<(ostream& os, const Graph& graph) {
    os << "Graph: costs to get to any vertex" << endl;
    for (int i = 0; i < graph.numVertices; i++) {
        for (int j = 0; j < graph.numVertices; j++) {
            if (j == graph.numVertices - 1) {
                os << graph.adjacencyMatrix[i][j];
            }
            else {
                os << graph.adjacencyMatrix[i][j] << ",";
            }
        }
        os << endl;
    }
    return os;
}

void Graph::SetGraphFromFile(string file) {
    fstream readFile;
    readFile.open(file, ios::in );

    if (!readFile.is_open()) {
        AssertWithErrorMessage("Cannot locate file: " + file, readFile.is_open());
        return;
    } else {
        string line = "";
        string token = "";
        string fileFormat = ExtractFileFormat(file);

        if (fileFormat == ".csv") {
            int i = 0;
            while(getline(readFile, line, '\n')) {
                size_t pos = 0;
                int j = 0;
                int cost = 0;
                while((pos = line.find(',')) != std::string::npos) {
                    token = line.substr(0, pos);
                    cost = stoi(token);
                    if (i != j && cost == 0) {
                        cost = -1;
                    }
                    adjacencyMatrix[i][j] = cost;
                    line.erase(0, pos + 1);
                    j++;
                }
                pos = line.find('\n');
                token = line.substr(0, pos);
                if (token == "") {
                    continue;
                }
                cost = stoi(token);
                if (i != j && cost == 0) {
                    cost = -1;
                }
                adjacencyMatrix[i][j] = cost;
                i++;
            }
            numVertices = i;
        } else if (fileFormat == ".dat") {
            vector<string> lines = SplitFileByLines(file);
            int count = 0;
            for (string line : lines) {
                count++;
                if (count > 10) { // reading edges
                    vector<float> numbers = ExtractNumbers(line);
                    if (numbers.size() > 2) { // this is a edge not the last line in the file
                        adjacencyMatrix[int(numbers[0]) - 1][int(numbers[1]) - 1] = float(numbers[2]);
                        adjacencyMatrix[int(numbers[1]) - 1][int(numbers[0]) - 1] = float(numbers[2]);
                        if (int(numbers[0]) > numVertices) {
                            numVertices = int(numbers[0]);
                        }
                        if (int(numbers[1]) > numVertices) {
                            numVertices = int(numbers[1]);
                        }
                    }
                }
            }
        }
        else if (fileFormat == ".txt") {
            vector<string> lines = SplitFileByLines(file);
            int count = 0;
            for (string line : lines) {
                count++;
                if (count > 3) { // reading edges
                    vector<float> numbers = ExtractNumbers(line);
                    if (numbers.size() > 2) { // this is a edge not the last line in the file
                        adjacencyMatrix[int(numbers[0]) - 1][int(numbers[1]) - 1] = float(numbers[2]);
                        adjacencyMatrix[int(numbers[1]) - 1][int(numbers[0]) - 1] = float(numbers[2]);
                        if (int(numbers[0]) > numVertices) {
                            numVertices = int(numbers[0]);
                        }
                        if (int(numbers[1]) > numVertices) {
                            numVertices = int(numbers[1]);
                        }
                    }
                }
            }
        }
    }
    readFile.close();
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

void Graph::CalculateNumberOfEdges() {
    numEdges = 0;
    sumEdges = 0;
    for (int i = 0; i < numVertices; i++) {
        for (int j = i; j < numVertices; j++) {
            if (adjacencyMatrix[i][j] > 0) {
                numEdges ++;
                sumEdges += adjacencyMatrix[i][j];
            }
        }
    }
}

pair<int, int>* Graph::GetVerticesOnEdge(int& edge) {
    int currentEdge = 0;
    // check cache before scanning for edge vertices
    if (cachedVerticesOnEdge[edge].first == INT_MAX) { // key not found
        for (int vertexA = 0; vertexA < numVertices; vertexA++) {
            for (int vertexB = vertexA; vertexB < numVertices; vertexB++) {
                // if weight is greater than 0 then valid edge
                if (0 < adjacencyMatrix[vertexA][vertexB]) {
                    currentEdge ++;
                    if (currentEdge > edge) {
                        cachedVerticesOnEdge[edge].first = vertexA;
                        cachedVerticesOnEdge[edge].second = vertexB;
                        return &cachedVerticesOnEdge[edge];
                    }
                }
            }
        }
    }

    return &cachedVerticesOnEdge[edge];
}


Path* Graph::GetShortestPathBetweenVertices(const int& startVertex, const int& endVertex) {
    Path* path = nullptr;
    // check cache before running dijkstras
    if (cachedShortestPaths[startVertex][0].cost < 0) { // start vertex has no existing path calculations
        Dijkstras(startVertex);
    }

    path = &cachedShortestPaths[startVertex][endVertex];

    return path;
}

// TODO return a tuple containing vertex to start from
Path* Graph::GetShortestPathBetweenEdges(int& edgeA, int& edgeB) {
    Path* path = nullptr;

    // check if best path has been cached
    if (cachedShortestPathBetweenEdges[edgeA][edgeB].cost != -1) {
        path = &cachedShortestPathBetweenEdges[edgeA][edgeB];
        return path;
    }

    pair<int, int> *verticesOnEdgeA = GetVerticesOnEdge(edgeA);
    pair<int, int> *verticesOnEdgeB = GetVerticesOnEdge(edgeB);

    Path *bestPath = GetShortestPathBetweenVertices(verticesOnEdgeA->first, verticesOnEdgeB->first);
    Path *tempPath = GetShortestPathBetweenVertices(verticesOnEdgeA->first, verticesOnEdgeB->second);
    if (bestPath->cost > tempPath->cost)
        bestPath = tempPath;
    tempPath = GetShortestPathBetweenVertices(verticesOnEdgeA->second, verticesOnEdgeB->first);
    if (bestPath->cost > tempPath->cost)
        bestPath = tempPath;
    tempPath = GetShortestPathBetweenVertices(verticesOnEdgeA->second, verticesOnEdgeB->second);
    if (bestPath->cost > tempPath->cost)
        bestPath = tempPath;

    cachedShortestPathBetweenEdges[edgeA][edgeB] = *bestPath;
    path = &cachedShortestPathBetweenEdges[edgeA][edgeB];
    return path;
}

Path* Graph::GetShortestPathBetweenVertexAndEdge(int& vertex, int& edge) {
    pair<int, int> *verticesOnEdge = GetVerticesOnEdge(edge);
    // check cache before running dijkstras
    if (cachedShortestPaths[vertex][0].cost == -1) { // start vertex has no existing path calculations
        Dijkstras(vertex);
    }

    if (cachedShortestPaths[vertex][verticesOnEdge->first].cost < cachedShortestPaths[vertex][verticesOnEdge->second].cost) {
        return &cachedShortestPaths[vertex][verticesOnEdge->first];
    }

    return &cachedShortestPaths[vertex][verticesOnEdge->second];
}

float& Graph::GetEdgeCost(int& vertexA, int& vertexB) {
    return adjacencyMatrix[vertexA][vertexB];
}

int& Graph::GetEdgeId(int& va, int& vb) {
    int edgeId = 0;
    for (int vertexA = 0; vertexA < numVertices; vertexA++) {
        for (int vertexB = vertexA; vertexB < numVertices; vertexB++) {
            // if weight is greater than 0 then valid edge
            if (0 < adjacencyMatrix[vertexA][vertexB]) {
                if ((va == vertexA && vb == vertexB) || (vb == vertexA && va == vertexB)) {
                    return edgeId;
                }
                edgeId++;
            }
        }
    }
    return edgeId;
}

int& Graph::GetOppositeVertexOnEdge(int& vertex, int& edge) {
    pair<int, int> *verticesOnEdge = GetVerticesOnEdge(edge);
    int v = verticesOnEdge->first;
    if (verticesOnEdge->first == vertex) {
        v = verticesOnEdge->second;
    }
    //cerr << "Trying to associate a vertex with an edge that is not related: (vertex: " << vertex << ", edge(" << edge << "): (" << verticesOnEdge->first << ", " << verticesOnEdge.second << "))" << endl;
    return v;
}

bool Graph::IsValidEdge(int& startVertex, int& endVertex) {
    return GetEdgeCost(startVertex, endVertex) > 0;
}


int& Graph::GetEdgesConnectedToVertex(int& vertex) {
    int numEdges = 0;
    for (int v = 0; v < numVertices; v++) {
        if (adjacencyMatrix[vertex][v] > 0) {
            numEdges++;
        }
    }

    // TODO make this so it only returns a vector of vertex elements

    return numEdges;
}


// utility function for dijkstras
int Graph::MinDistance(float dist[], bool visited[]) {
    // Initialize min value
   int min = INT_MAX, min_index;

    for (int v = 0; v < numVertices; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// dijkstras in this implementation will not return anything because it will add the paths it finds to the cache
void Graph::Dijkstras(int startVertex) {

    float dist[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    vector<int> paths[MAX_VERTICES];

    for (int i = 0; i < numVertices; i++) {
        dist[i] = FLT_MAX;
        visited[i] = false;
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




