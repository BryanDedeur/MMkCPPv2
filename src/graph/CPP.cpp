//
// Created by Bryan 
//

#include "CPP.h"


CPP::CPP() {

} 

bool sortPath(Path a, Path b) { return (a.cost < b.cost); }

void recursivelyMakeCombinations(vector<int> oddVertices, vector<Path> tempCombinations, vector<vector<Path>> &allCombinations, Graph& graph) {
	int first = oddVertices.front();
	oddVertices.erase(oddVertices.begin());
	
	if (oddVertices.size() == 1) {
		tempCombinations.push_back(*graph.GetShortestPathBetweenVertices(first, oddVertices.front()));
		allCombinations.push_back(tempCombinations);
	} else {
		tempCombinations = vector<Path>();
		for (int v = 0; v < oddVertices.size(); v++) {
			vector<int> temp = oddVertices;
			tempCombinations.push_back(*graph.GetShortestPathBetweenVertices(first, oddVertices[v]));
			temp.erase(temp.begin() + v);
			recursivelyMakeCombinations(temp, tempCombinations, allCombinations, graph);
		}
	}
}

void CPP::Solve(Graph& graph) {
	// Find all the vertices with odd number of edges
	//oddVertices = vector<int>();
	//for (int v = 0; v < graph.numVertices; v++) {
	//	if (!(graph.GetEdgesConnectedToVertex(v) % 2 == 0)) {
	//		oddVertices.push_back(v);
	//	}
	//}
	//numOddVertices = oddVertices.size();


	//// Find the shortest paths between all the odd edged vertices using dijkstras
	//vector<Path> paths = vector<Path>();
	//for (int v1 = 0; v1 < oddVertices.size(); v1++) {
	//	for (int v2 = 0; v2 < oddVertices.size(); v2++) {
	//		if (v1 != v2) {
	//			paths.push_back(*graph.GetShortestPathBetweenVertices(v1, v2));
	//		}
	//	}
	//}

	//// Find the pairs of vertices that all sum to the lowest travel cost 
	//// std::sort(paths.begin(), paths.end(), sortPath);

	//vector<vector<Path>> allCombinations = vector<vector<Path>>();

	//recursivelyMakeCombinations(oddVertices, vector<Path>(), allCombinations, graph);

	//// Find the lowest cost of pairs
	//vector<Path> cheapestPathCombinations = vector<Path>();
	//double sumOfPaths = DBL_MAX;
	//for (int i = 0; i < allCombinations.size(); i++) {
	//	double temp = 0;
	//	for (int p = 0; p < allCombinations[i].size(); p++) {
	//		temp += allCombinations[i][p].cost;
	//	}
	//	if (temp < sumOfPaths) {
	//		sumOfPaths = temp;
	//		cheapestPathCombinations = allCombinations[i];
	//	}
	//}

	////cout << "The CPP minimal cost is " << graph.sumEdges + sumOfPaths << " where the sum of edges is " << graph.sumEdges << endl;
	//shortestPathDistance = graph.sumEdges + sumOfPaths;
}