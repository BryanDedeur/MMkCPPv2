/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
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

    SetGraphFromFile(options->datafile);

    CalculateNumberOfEdges();

    options->chromLength = numEdges + options->numRobots;

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
            if (j == 0)
                os << "(" << i << "," << j << ")" << graph.cachedShortestPaths[i][j].cost;
            else
                os << "\t" << "(" << i << "," << j << ")"<< graph.cachedShortestPaths[i][j].cost;
        }
        os << endl;
    }
    return os;
}


void Graph::SetGraphFromFile(string file) {
    fstream readFile;
    readFile.open(file, ios::in );

    if (!readFile.is_open()) {
        cerr << "Cannot locate file: " << file << endl;
        return;
    } else {
        string line, token, temp = "";

        // Read data, line by line
        int i = 0;
        while(getline(readFile, line, '\n')) {
            size_t pos = 0;
            int j = 0;
            while((pos = line.find(',')) != std::string::npos) {
                token = line.substr(0, pos);
                adjacencyMatrix[i][j] = stoi(token);
                line.erase(0, pos + 1);
                j++;
            }
            pos = line.find('\n');
            token = line.substr(0, pos);
            adjacencyMatrix[i][j] = stoi(token);
            //line.erase(0, pos + 1);
            i++;
        }
        numVertices = i;
    }
    readFile.close();
}
void Graph::CalculateNumberOfEdges() {
    numEdges = 0;
    for (int i = 0; i < numVertices; i++) {
        for (int j = i; j < numVertices; j++) {
            // if weight is greater than 0 then valid edge
            if (0 < adjacencyMatrix[i][j]) {
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


Path* Graph::GetShortestPathBetweenVertices(int& startVertex, int& endVertex) {
    Path* path = nullptr;
    // check cache before running dijkstras
    if (cachedShortestPaths[startVertex][0].cost == -1) { // start vertex has no existing path calculations
        Dijkstras(startVertex);
    }

    path = &cachedShortestPaths[startVertex][endVertex];

    return path;
}

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

int& Graph::GetEdgeCost(int& vertexA, int& vertexB) {
    return adjacencyMatrix[vertexA][vertexB];
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

// utility function for dijkstras
int Graph::MinDistance(int dist[], bool visited[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < numVertices; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// dijkstras in this implementation will not return anything because it will add the paths it finds to the cache
void Graph::Dijkstras(int startVertex) {

    int dist[MAX_VERTICES];
    bool visited[MAX_VERTICES];
    vector<int> paths[MAX_VERTICES];

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
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
                && -1 != adjacencyMatrix[nearestUnvisitedVertex][v] // edge exists
                && dist[nearestUnvisitedVertex] != INT_MAX          // explored
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




