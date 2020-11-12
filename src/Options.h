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

// Definitions (if you add to this you need to update the get...str functions in options
enum SelectorType {Proportionate, CHC}; // proportionate ranking, tournament, genitor/ steady state
enum CrossoverType {NoCross, PMX, OX};
enum MutationType {NoMut, Swap, Cataclysmic};

// Options
typedef struct {
    // in files
	string infile;
    string datafile;

    // output files
    string decodedfile;
    string fitnessfile;
    string travelfile;

	long int randomSeed;
	int popSize;
	int chromLength;
	unsigned int maxgens;

	float px;
	float pm;

	SelectorType selector;
	CrossoverType crossover;
	MutationType mutator;
	string GetSelectorStr() {
        switch(selector) {
            case CHC: return "chc";
            case Proportionate: return "fp";
            default: return "";
        }
	}
    string GetCrossoverStr() {
        switch(crossover) {
            case OX: return "ox";
            case PMX: return "pmx";
            default: return "";
        }
    }
    string GetMutatorStr() {
        switch(mutator) {
            case Swap: return "swap";
            default: return "";
        }
	}

        // Unique for mmkcpp
    int numRobots;
} Options;

#endif /* OPTIONS_H_ */
