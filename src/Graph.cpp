//
// By Bryan D.
// Created: 10/15/2020
//

#include "Graph.h"


// Graph Constructor
Graph::Graph(Options options) : cachedShortestPaths() {
    // TODO load graph from file options.datafile

    // Below is just a test
    const int numVerti = 10;
    // created with https://graphonline.ru/en/
    int** testGraph = (int **) malloc(numVerti * sizeof(int*));
    for (int i = 0; i < numVerti; i++) {
        testGraph[i] = (int *) malloc(numVerti * sizeof(int));
    }

    int exampleGraph[numVerti][numVerti] =
            {{0, 5, 7, -1, -1, -1, -1, -1, -1, -1},
             {5, 0, -1, 7, -1, -1, -1, 11, -1, -1},
             {7, -1, 0, 3, -1, -1, -1, -1, 11, -1},
             {-1, 7, 3, 0, 5, 5, -1, -1, -1, 1},
             {-1, -1, -1, 5, 0, -1, 11, 3, -1, -1},
             {-1, -1, -1, 5, -1, 0, 3, -1, 1, -1},
             {-1, -1, -1, -1, 11, 3, 0, -1, -1, -1},
             {-1, 11, -1, -1, 3, -1, -1, 0, -1, -1},
             {-1, -1, 11, -1, -1, 1, -1, -1, 0, -1},
             {-1, -1, -1, 1, -1, -1, -1, -1, -1, 0}};

    for (int i = 0; i < numVerti; i++) {
        for (int j = 0; j < numVerti; j++) {
            testGraph[i][j] = exampleGraph[i][j];
        }
    }

    setAdjacencyMatrix(testGraph, numVerti);
    calculateNumberOfEdges();

    Path* path = getShortestPathBetweenEdges(2, 4);
}

// Graph Constructor
// @param adjMatrix is an existing multi dim array
// @param numVerti is the number of vertices on the graph
Graph::Graph(int **adjMatrix, int numVerti) : cachedShortestPaths() {
    setAdjacencyMatrix(adjMatrix, numVerti);
    calculateNumberOfEdges();
}

//Graph::Graph(int adjMatrix[], int numVerti) {
//    setAdjacencyMatrix(adjMatrix[], numVerti);
//    calculateNumberOfEdges();
//}


Graph::~Graph() {
    //TODO auto generated destructor tab
}

// SetMatrix is utilized by initializer and constructor functions to set the class graph data
void Graph::setAdjacencyMatrix(int **otherMatrix, int numVerti) {
    numVertices = numVerti;

    adjacencyMatrix = new int*[numVerti];
    for (int i = 0; i < numVerti; i++) {
        adjacencyMatrix[i] = new int[numVerti];
        for (int j = 0; j < numVerti; j++) {
            adjacencyMatrix[i][j] = otherMatrix[i][j];
        }
    }
}

void Graph::calculateNumberOfEdges() {
    numEdges = 0;
    for (int i = 0; i < numVertices; i++) {
        for (int j = i; j < numVertices; j++) {
            // if weight is greater than 0 then valid edge
            if (adjacencyMatrix[i][j] > 0) {
                numEdges ++;
            }
        }
    }
}

void Graph::Init() {
    //cacheShortestPaths();
    // TODO implement, this would be a good place to cache things ahead of time
}

const int Graph::getNumVertices() {
    return numVertices;
}

const int Graph::getNumEdges() {
    return numEdges;
}

// TODO Test
int* Graph::getVerticesOnEdge(int edge) {
    int *vertices = (int *) malloc(2 * sizeof(int));
    int currentEdge = 0;
    if (!(edge > numEdges - 1)) {
        // Check cache if this has been solved before
        if (cachedVerticesOnEdge.find(edge) == cachedVerticesOnEdge.end()) {
            for (int vertexA = 0; vertexA < numVertices; vertexA++) {
                for (int vertexB = vertexA; vertexB < numVertices; vertexB++) {
                    // if weight is greater than 0 then valid edge
                    if (adjacencyMatrix[vertexB][vertexB] > 0) {
                        currentEdge ++;
                        if (currentEdge > edge) {
                            vertices[0] = vertexA;
                            vertices[1] = vertexB;
                            cachedVerticesOnEdge[edge] = vertices;
                            return cachedVerticesOnEdge[edge];
                        }
                    }
                }
            }
        }
    }

    return cachedVerticesOnEdge[edge];
}


Path* Graph::getShortestPathBetweenVertices(int startVertex, int endVertex) {
    // check cache before running dijkstras
    if (cachedShortestPaths.find(startVertex) == cachedShortestPaths.end()) { // start vertex has no existing path calculations
        dijkstras(startVertex);
    }

    return &cachedShortestPaths[startVertex][endVertex];
}

Path* Graph::getShortestPathBetweenEdges(int edgeA, int edgeB) {
    int* verticesOnEdgeA = getVerticesOnEdge(edgeA);
    int* verticesOnEdgeB = getVerticesOnEdge(edgeB);

    Path* bestPath = nullptr;
    // TODO check if best path has been cached

    for (int i = 0; i < NUM_VERTICES_PER_EDGE; i++) {
        for (int j = 0; j < NUM_VERTICES_PER_EDGE; j++) {
            Path* tempPath = getShortestPathBetweenVertices(verticesOnEdgeA[i], verticesOnEdgeB[j]);
            if (bestPath == nullptr || bestPath->cost > tempPath->cost) {
                bestPath = tempPath;
            }
        }
    }
    return bestPath;
}

// utility function for dijkstras
int Graph::minDistance(int dist[], bool visited[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < numVertices; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// dijkstras does not return anything because it will add the paths it finds to the cache
void Graph::dijkstras(int startVertex) {
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


    // TODO this could be a little faster if every path from previous calcuations was considered

    for (int count = 0; count < numVertices - 1; count++) {
        int nearestUnvisitedVertex = minDistance(dist, visited);

        visited[nearestUnvisitedVertex] = true;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v]     // not visited
                && adjacencyMatrix[nearestUnvisitedVertex][v] != -1 // edge exists
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




