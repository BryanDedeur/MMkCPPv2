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
#include "Graph.h"

class GA {

private:
	void Construct();

public:
	GA(int argc, char *argv[]);

	virtual ~GA();

	//--------------------------------
	Graph *graph;
	Population *parent;
	Population *child;
	Options options;

	Individual* bestIndividual;
	void SetupOptions(int argc, char*argv[]);

	void Init();
	void Run();

};

#endif /* GA_H_ */
