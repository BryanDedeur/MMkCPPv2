/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Jonathan Peters
 * @Date: 10/18/20
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include "../Utils.h"

#include <string>
#include <time.h>

using std::string;

// Definitions (if you add to this you need to update the get...str functions in options
enum SelectorType {FP, CHC}; // proportional ranking, tournament, genitor/ steady state
enum CrossoverType {NoCross, OnePoint, TwoPoint, PMX, OX, CX, EX};
enum MutationType {NoMut, Swap, Invert, Slide, Uniform};

struct Base { };

// Options
typedef struct Options : Base {
    // in files
	string infile;
    //string graphfile = "../problem-instances/bridge-generator2/B200.txt"; // directory must be relative to the executable
    //string graphfile = "../problem-instances/custom-graphs/bryans/pacman.csv"; // directory must be relative to the executable
    //string graphfile = "../problem-instances/benchmarks/gdb/gdb1.dat";
    string graphfile = "../problem-instances/stacs-graphs/graph-raw.csv";;

    string graphName;

    string outputDir = "../../results/";

    // output files
    string decodedfile;
    string fitnessfile;
    string travelfile;
    string resultsfile;

    bool minimalOutput = false;
    bool makeVisuals = false;
    int closedRouteVertex = 0;

    string seedsFile = "../seed-files/1seeds.txt";
    long int* seeds;
    long int randomSeed = time(NULL);
     
	int numRuns = 1;
	int popSize = 100;
	//int chromLength; // this is automatically set by the graph
	unsigned int maxgens = 2 * popSize;

    int numRobots = 2;

	float px = 0.99;
	float pm = 0;

	SelectorType selector = CHC;
	CrossoverType crossover = OnePoint;
	MutationType mutator = Uniform;

    // Helper functions below
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
            case OnePoint: return "onepoint";
            case TwoPoint: return "twopoint";
            default: return "";
        }
    }
    string GetMutatorStr() {
        switch(mutator) {
            case Swap: return "swap";
            case Invert: return "inv";
            case Slide: return "sld";
            case Uniform: return "uniform";
            default: return "";
        }
	}

} Options;

#endif /* OPTIONS_H_ */
