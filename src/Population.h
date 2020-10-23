/*
 * Population.h
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
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
	void Evaluate();
	void Generation(Population *child);
	void Report(unsigned long int gen);
	void Statistics();

    void XoverAndMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2);

    // Selectors
	int ProportionalSelector();

	// Crossovers

	// Mutators
	void TwoPoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
	void OnePoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);

};

#endif /* POPULATION_H_ */
