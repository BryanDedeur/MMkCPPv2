/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include "Options.h"
#include "../graph/Graph.h"

#include "Individual.h"

#include <algorithm> // for min and max and sort
#include <vector>

using std::sort;

class Population {
public:
	Population(Options* options, Graph *graph);
	virtual ~Population();
	//------------------------

	Options* options;
	vector<Individual*> members;

    double avgFitness, minFitness, maxFitness, sumFitness;
    double avgTravelDist, minTravelDist, maxTravelDist, sumTravelDist;
    Graph* graph;
    Individual* bestIndividual;

    void Init();

    // helpers
    bool ChromContains(Gene* arr, Gene &gene);

    void EvaluateMembers();
	void Generation(Population *child);
    void CHCGeneration(Population *child);
	void Report(unsigned long int gen);
	void Statistics();

	// Helpers
    void XoverAndMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
    int ProportionalSelector();
    void StoreIfBest(Individual* ind);

    // Generation production strategies
    //void FitnessProportional(Population *child);

    // Crossovers
    //	void TwoPoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
    //	void OnePoint(Individual *p1, Individual *p2, Individual *c1, Individual *c2);
    void PMX(Individual *p1, Individual *p2, Individual *c1, Individual *c2); // Permutation crossover
    void OX(Individual *p1, Individual *p2, Individual *c1, Individual *c2); // Ordered crossover (heterogeneous recombination)

	// Mutators
	// mutator is inside of individual class
	void SwapMutate(Individual *i); // Two point swap mutation
    void InvertMutate(Individual *ind);
};

#endif /* POPULATION_H_ */
