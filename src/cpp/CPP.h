/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Bryan Dedeurwaerder, Johnathan Peters
 * @Copyright: University of Nevada, Reno
 * @Date: 10/18/20
 */

#ifndef CPP_H_
#define CPP_H_

#include "../graph/Path.h"
#include "../graph/Graph.h"

#include <iostream>
#include <vector>

class CPP {
public:
	CPP(Graph *graph);

	void Solve();

	Path* solution;

private:
	void CheckIfCacheExists();
	void ReadCacheFile(string filePath);
	void WriteToCacheFile(string filePath);

	void FindOddDegreeNodes();
	void FindPairsBetweenOddDegreeNodes();

	Graph* graph;
};

#endif /* INDIVIDUAL_H_ */
