/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include "Const.h"
#include "Utils.h"
#include <string>

using std::string;

// Definitions (if you add to this you need to update the get...str functions in options
enum SelectorType {FP, CHC}; // proportional ranking, tournament, genitor/ steady state
enum CrossoverType {NoCross, PMX, OX, CX, EX};
enum MutationType {NoMut, Swap, Invert, Slide};

// Options
typedef struct {
    // in files
	string infile;
    string graphfile;

    // output files
    string decodedfile;
    string fitnessfile;
    string travelfile;
    string resultsfile;

    bool minimalOutput;
    bool makeVisuals;
    bool openRoutes; // start and end vertex does not matter
    int startVertex;

    string graphName;

	long int randomSeed;
	int numRuns;
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
            case FP: return "fp";
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
            case Invert: return "inv";
            case Slide: return "sld";
            default: return "";
        }
	}

        // Unique for arc-routing
    int numRobots;
} Options;

#endif /* OPTIONS_H_ */
