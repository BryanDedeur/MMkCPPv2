/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include "Const.h"
#include "Options.h"
#include "Individual.h"
#include "Graph.h"
#include <algorithm> // for min and max

class Population {
public:
	Population(Options options, Graph *graph);
	virtual ~Population();
	//------------------------

	Options options;
	Individual *members[MAXPOP];
	double avg, min, max, sumFitness;
    Graph* graph;

	void Init();
	void EvaluateMembers();
	void Generation(Population *child);
	void Report(unsigned long int gen);
	void Statistics();

    void XoverAndMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2);

    // Selectors
	int ProportionalSelector();
	// TODO implement CHC selection (Cross generation elitist seletion)


	// Crossovers
    // TODO implement order crossover (Heterogenous recombination)


	// Mutators
	void TwoPoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
	void OnePoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
	// TODO implement Cataclysmic mutation

};

#endif /* POPULATION_H_ */
