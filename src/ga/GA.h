/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#ifndef GA_H_
#define GA_H_

#include "Population.h"
#include "Options.h"
#include "../graph/Graph.h"
#include "../cpp/CPP.h"

#include <time.h>
#include <vector>

#define MAX_NUM_ROBOTS 20

class GA {

public:
	GA(int argc, char *argv[]);

	virtual ~GA();

	//--------------------------------
	Graph *graph;
	Population *parent;
	Population *child;
	Options options;

	CPP* cpp;

	vector<Individual> bestPerSeed;
	Individual *best;
    void SetGraph(string graphfile);
    void SetupOptions(int argc, char*argv[]);

	void Init();
	void Run();
    void Report();

    int runCount;
    double timeSeconds;
};

#endif /* GA_H_ */
