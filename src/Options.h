/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include "Utils.h"
#include <string>

using std::string;

// Definitions
enum SelectorType {FitnessProportional, CHC};
enum CrossoverType {PMX, OX};
enum MutationType {Swap, Cataclysmic};

// Options
typedef struct {
	string infile;
	string outfile;

	string datafile;
	string decodedfile;

	long int randomSeed;
	int popSize;
	int chromLength;
	unsigned int maxgens;

	float px;
	float pm;

	SelectorType selector;
	CrossoverType crossover;
	MutationType mutator;

	// Unique for mmkcpp
    int numRobots;
} Options;

#endif /* OPTIONS_H_ */
