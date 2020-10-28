/*
 * @Project: MMkCPP
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */


#include "Evaluate.h"
#include <math.h>

double Eval(Individual *individual){
	double sum = 0;
//	for (int i = 0; i < individual->chromLength; i++) {
//	    // TODO fix for new chromosome
//		sum += individual->calculateFitness();
//	}
    // migrated this to individual.h class
	return sum;
}
