/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <string>

enum SelectorType {FitnessProportional, CHC};
enum CrossoverType {PMX, OX};
enum MutationType {Swap, Cataclysmic};

typedef struct {
	std::string infile;
	std::string outfile;

	std::string datafile;
	std::string decodedfile;

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
