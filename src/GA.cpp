/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#include "GA.h"
#include <iostream>

GA::GA(int argc, char *argv[]) {
	SetupOptions(argc, argv);
	srand(options.randomSeed);
    ClearFile(options.fitnessfile);
    ClearFile(options.travelfile);
    graph = new Graph(&options);
    best = new Individual(&options, graph);
    best->totalTravelDistance = 0;
    best->fitness = 0;
}

GA::~GA() {
	// TODO Auto-generated destructor stub
}


void GA::SetupOptions(int argc, char *argv[]){
	options.randomSeed = time(NULL);
	options.popSize = 1000; // if this is an odd number this will break
	//options.chromLength = 10;
	options.maxgens = 1000;
	options.px = 0.99;
	options.pm = 0.4; // This is set by the graph

    options.selector = CHC;
    options.crossover = OX;
    options.mutator = Invert;

	// new stuff for mmkcpp
    options.numRobots = 1;

    string graphName = "graph-gdb3";

    options.infile = "../infile";
    options.datafile = "../benchmarks/mmkcpp/" + graphName + ".csv";

    // output file name
    string GAParamsStr = graphName + "-" +
            to_string(options.numRobots) + "R-" +
            "pops" + to_string(options.popSize) + "-" +
            to_string(options.maxgens) + "gens-" +
            options.GetSelectorStr() + "-" +
            options.GetCrossoverStr() + "-" +
            options.GetMutatorStr();

    options.decodedfile = "../results/route-" + GAParamsStr + ".tsv";
    options.fitnessfile = "../results/fitness-" + GAParamsStr + ".tsv";
    options.travelfile = "../results/travel-" + GAParamsStr + ".tsv";
}

void GA::Init(){
    //cout << *graph << endl;
	parent = new Population(&options, graph);
	child  = new Population(&options, graph);
	parent->Init(); // evaluates, stats, and reports on initial population
	parent->Statistics();
	parent->Report(0);
}

void GA::Run(){
	for(unsigned long int i = 1; i < options.maxgens; i++){
        if (options.selector == SelectorType::CHC) {
            parent->CHCGeneration(child);
        } else {
            parent->Generation(child);
            child->EvaluateMembers();
        }
		if (child->bestIndividual->fitness > best->fitness) {
            *best = *child->bestIndividual;
		}
        child->Statistics();
		child->Report(i);

		Population *tmp = parent;
		parent = child;
		child = tmp;
	}
}

