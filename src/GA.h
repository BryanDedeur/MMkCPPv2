/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#ifndef GA_H_
#define GA_H_

#include <time.h>
#include "Population.h"
#include "Options.h"
#include "Graph.h"
#include "CPP.h"
#include <time.h>
#include <vector>

class GA {

public:
	GA(int argc, char *argv[]);

	virtual ~GA();

	//--------------------------------
	Graph *graph;
	Population *parent;
	Population *child;
	Options options;

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
