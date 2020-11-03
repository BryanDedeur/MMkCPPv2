/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <string>

typedef struct {
	std::string infile;
	std::string outfile;

	std::string datafile;

	long int randomSeed;
	int popSize;
	int chromLength;
	unsigned int maxgens;

	float px;
	float pm;

	// TODO create an option for which mutator
	// TODO create an option for which crossover
	// TODO create an option for which selector

	// Unique for mmkcpp
    int numRobots;


} Options;

#endif /* OPTIONS_H_ */
