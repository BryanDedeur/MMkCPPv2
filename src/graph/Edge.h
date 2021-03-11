//
// Created by Bryan on 11/3/2020.
//

#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

#include <ostream>
#include <vector>

class Edge {
	public:

		// Default Constructors
		Edge();
		Edge(int id, int vertexA, int vertexB, float cost);

		unsigned int id;
		unsigned int vertexA;
		unsigned int vertexB;
		float cost;

		std::pair<int, int> vpair;
		Edge& operator=(Edge other);
};


#endif //GRAPH_EDGE_H
