//
// By Bryan D.
// Created: 10/15/2020
//

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
using namespace std;

// Graph Constructor
Graph::Graph(Options options) {

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

    setAdjacencyMatrix(graph, numVerti);
    calculateNumberOfEdges();
}

// Graph Constructor
// @param adjMatrix is an existing multi dim array
// @param numVerti is the number of vertices on the graph
Graph::Graph(float **adjMatrix, int numVerti) {
    setAdjacencyMatrix(adjMatrix, numVerti);
    calculateNumberOfEdges();
}


Graph::~Graph() {
    //TODO auto generated destructor tab
}

// SetMatrix is utilized by initializer and constructor functions to set the class graph data
void Graph::setAdjacencyMatrix(float **otherMatrix, int numVerti) {
    numVertices = numVerti;

    adjacencyMatrix = new float*[numVerti];
    for (int i = 0; i < numVerti; i++) {
        adjacencyMatrix[i] = new float[numVerti];
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

int* Graph::getVerticesOnEdge(int edgeA) {
    int vertices[NUM_VERTICES_PER_EDGE];
    return vertices;
}


Path* Graph::getShortestPathBetweenVertices(int startVertexA, int endVertexB) {
    // if path from a to b is cached
        // get cache
    // if not cached
        // compute dijkstra's
    Path* path = new Path();
    return path;
}

Path* Graph::getShortestPathBetweenEdges(int edgeA, int edgeB) {
    int* verticesOnEdgeA = getVerticesOnEdge(edgeA);
    int* verticesOnEdgeB = getVerticesOnEdge(edgeB);

    Path* bestPath = nullptr;

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

void Graph::dijkstras(int startVertex) {

}




