/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#include "Graph.h"

using namespace std;

// Graph Constructor
Graph::Graph(Options options) : cachedShortestPaths(), adjacencyMatrix(), numEdges(0), numVertices(0) {

    adjacencyMatrix = new int*[MAX_NUM_VERTICES];
    for (int i = 0; i < MAX_NUM_VERTICES; i++) {
        adjacencyMatrix[i] = new int[MAX_NUM_VERTICES];
        for (int j = 0; j < MAX_NUM_VERTICES; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }

    SetGraphFromFile(options.datafile);

    CalculateNumberOfEdges();

    //Path* path = GetShortestPathBetweenEdges(1, 10);


}

// Graph Constructor
// @param adjMatrix is an existing multi dim array
// @param numVerti is the number of vertices on the graph
Graph::Graph(float **adjMatrix, int numVerti) : cachedShortestPaths(), numEdges(0), numVertices(0){
    CalculateNumberOfEdges();
}

Graph::~Graph() {
    //TODO auto generated destructor tab
    for (int i = 0; i < MAX_NUM_VERTICES; i++) {
        delete[] adjacencyMatrix[i];
    }
    delete[] adjacencyMatrix;
}

void Graph::Init() {
    //cacheShortestPaths();
    // TODO implement, this would be a good place to cache things ahead of time
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
            }
        }
    }
}

pair<int, int>* Graph::GetVerticesOnEdge(int edge) {
    int currentEdge = 0;
    // check cache before scanning for edge vertices
    if (cachedVerticesOnEdge.find(edge) == cachedVerticesOnEdge.end()) { // key not found
        for (int vertexA = 0; vertexA < numVertices; vertexA++) {
            for (int vertexB = vertexA; vertexB < numVertices; vertexB++) {
                // if weight is greater than 0 then valid edge
                if (0 < adjacencyMatrix[vertexA][vertexB]) {
                    currentEdge ++;

                    if (currentEdge > edge) {
                        cachedVerticesOnEdge[edge] = make_pair(vertexA, vertexB);
                        return &cachedVerticesOnEdge[edge];
                    }
                }
            }
        }
    }

    return &cachedVerticesOnEdge[edge];
}


Path* Graph::GetShortestPathBetweenVertices(int startVertex, int endVertex) {
    // check cache before running dijkstras
    if (cachedShortestPaths.find(startVertex) == cachedShortestPaths.end()) { // start vertex has no existing path calculations
        Dijkstras(startVertex);
    }

    return &cachedShortestPaths[startVertex][endVertex];
}

Path* Graph::GetShortestPathBetweenEdges(int edgeA, int edgeB) {
    // check if best path has been cached
    if (cachedShortestPathBetweenEdges.find(edgeA) != cachedShortestPathBetweenEdges.end()) {
        if (cachedShortestPathBetweenEdges[edgeA].find(edgeB) != cachedShortestPathBetweenEdges[edgeA].end()) {
            return &cachedShortestPathBetweenEdges[edgeA][edgeB];
        }
    }

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

    return bestPath;
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
    int* dist = new int[numVertices];
    bool* visited = new bool[numVertices];

    vector<int> *path = new vector<int>[numVertices];

    for (int i = 0; i < numVertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        path[i].push_back(startVertex);
    }

    dist[startVertex] = 0;
    cachedShortestPaths[startVertex][startVertex] = Path(path[startVertex], dist[startVertex]);

    // TODO this might be a little faster if every path from previous calcuations was considered

    for (int count = 0; count < numVertices - 1; count++) {
        int nearestUnvisitedVertex = MinDistance(dist, visited);

        visited[nearestUnvisitedVertex] = true;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v]     // not visited
                && -1 != adjacencyMatrix[nearestUnvisitedVertex][v] // edge exists
                && dist[nearestUnvisitedVertex] != INT_MAX          // explored
                && dist[nearestUnvisitedVertex] + adjacencyMatrix[nearestUnvisitedVertex][v] < dist[v]) {

                dist[v] = dist[nearestUnvisitedVertex] + adjacencyMatrix[nearestUnvisitedVertex][v];

                path[v] = path[nearestUnvisitedVertex];
                path[v].push_back(v);

                cachedShortestPaths[startVertex][v] = Path(path[v], dist[v]);
            }
        }
    }
}




