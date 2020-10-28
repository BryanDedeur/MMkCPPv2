/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#include "Graph.h"
#include <iostream>
#include <fstream>

#ifdef _WIN32
    #include <json.h>
#else
    #include <jsoncpp/json/json.h>
#endif

using namespace std;

// Graph Constructor
Graph::Graph(Options options) : cachedShortestPaths() {

	//Create ifstream to read from option.dataFile
	ifstream graph_file(options.datafile, ifstream::binary);
	if(graph_file.fail())
	{
		cerr << "ERROR: JSON file not found" << endl;
		return;
	}
	
	//jsonGraph will hold the object in the json file
	Json::Value jsonGraph;
	graph_file >> jsonGraph;
	
	//Create float** to hold data read from json file
	int numVerti = jsonGraph["graph"].size();
	float** graph = (float **) malloc(numVerti * sizeof(float*));
	for(int i = 0; i < numVerti; i++)
	{
		graph[i] = (float *) malloc(numVerti * sizeof(float));
	}

	//Read data from json to float**
	for(int i = 0; i < numVerti; i++)
	{
		for(int j = 0; j < numVerti; j++)
		{
			graph[i][j] = jsonGraph["graph"][i]["list"][j].asFloat();
		}
	}

    calculateNumberOfEdges();

    Path* path = getShortestPathBetweenEdges(1, 10);


}

// Graph Constructor
// @param adjMatrix is an existing multi dim array
// @param numVerti is the number of vertices on the graph
Graph::Graph(float **adjMatrix, int numVerti) : cachedShortestPaths(){
    calculateNumberOfEdges();
}

//Graph::Graph(int adjMatrix[], int numVerti) {
//    setAdjacencyMatrix(adjMatrix[], numVerti);
//    calculateNumberOfEdges();
//}


Graph::~Graph() {
    //TODO auto generated destructor tab
}

void Graph::calculateNumberOfEdges() {
    numEdges = 0;
    for (int i = 0; i < numVertices; i++) {
        for (int j = i; j < numVertices; j++) {
            // if weight is greater than 0 then valid edge
            if (0 < adjacencyMatrix.at(i).at(j)) {
                numEdges ++;
            }
        }
    }
}

void Graph::Init() {
    //cacheShortestPaths();
    // TODO implement, this would be a good place to cache things ahead of time
}

pair<int, int>* Graph::getVerticesOnEdge(int edge) {
    int currentEdge = 0;
    // check cache before scanning for edge vertices
    if (cachedVerticesOnEdge.find(edge) == cachedVerticesOnEdge.end()) { // key not found
        for (int vertexA = 0; vertexA < numVertices; vertexA++) {
            for (int vertexB = vertexA; vertexB < numVertices; vertexB++) {
                // if weight is greater than 0 then valid edge
                if (0 < adjacencyMatrix.at(vertexA).at(vertexB)) {
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


Path* Graph::getShortestPathBetweenVertices(int startVertex, int endVertex) {
    // check cache before running dijkstras
    if (cachedShortestPaths.find(startVertex) == cachedShortestPaths.end()) { // start vertex has no existing path calculations
        dijkstras(startVertex);
    }

    return &cachedShortestPaths[startVertex][endVertex];
}

Path* Graph::getShortestPathBetweenEdges(int edgeA, int edgeB) {
    // check if best path has been cached
    if (cachedShortestPathBetweenEdges.find(edgeA) != cachedShortestPathBetweenEdges.end()) {
        if (cachedShortestPathBetweenEdges[edgeA].find(edgeB) != cachedShortestPathBetweenEdges[edgeA].end()) {
            return &cachedShortestPathBetweenEdges[edgeA][edgeB];
        }
    }

    pair<int, int>* verticesOnEdgeA = getVerticesOnEdge(edgeA);
    pair<int, int>* verticesOnEdgeB = getVerticesOnEdge(edgeB);

    Path* bestPath = getShortestPathBetweenVertices(verticesOnEdgeA->first, verticesOnEdgeB->first);
    Path* tempPath = getShortestPathBetweenVertices(verticesOnEdgeA->first, verticesOnEdgeB->second);
    if (bestPath->cost > tempPath->cost)
        bestPath = tempPath;
    tempPath = getShortestPathBetweenVertices(verticesOnEdgeA->second, verticesOnEdgeB->first);
    if (bestPath->cost > tempPath->cost)
        bestPath = tempPath;
    tempPath = getShortestPathBetweenVertices(verticesOnEdgeA->second, verticesOnEdgeB->second);
    if (bestPath->cost > tempPath->cost)
        bestPath = tempPath;

    cachedShortestPathBetweenEdges[edgeA][edgeB] = *bestPath;

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

// dijkstras in this implementation will not return anything because it will add the paths it finds to the cache
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

    // TODO this might be a little faster if every path from previous calcuations was considered

    for (int count = 0; count < numVertices - 1; count++) {
        int nearestUnvisitedVertex = minDistance(dist, visited);

        visited[nearestUnvisitedVertex] = true;

        for (int v = 0; v < numVertices; v++) {
            if (!visited[v]     // not visited
                && -1 != adjacencyMatrix.at(nearestUnvisitedVertex).at(v) // edge exists
                && dist[nearestUnvisitedVertex] != INT_MAX          // explored
                && dist[nearestUnvisitedVertex] + adjacencyMatrix.at(nearestUnvisitedVertex).at(v) < dist[v]) {

                dist[v] = dist[nearestUnvisitedVertex] + adjacencyMatrix.at(nearestUnvisitedVertex).at(v);

                path[v] = path[nearestUnvisitedVertex];
                path[v].push_back(v);

                cachedShortestPaths[startVertex][v] = Path(path[v], dist[v]);
            }
        }
    }
}




