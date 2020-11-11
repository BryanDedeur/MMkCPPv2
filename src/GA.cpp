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
    ClearFile(options.outfile);
}

GA::~GA() {
	// TODO Auto-generated destructor stub
}


void GA::SetupOptions(int argc, char *argv[]){
	options.randomSeed = time(NULL);
	options.popSize = 1000; // if this is an odd number this will break
	//options.chromLength = 10;
	options.maxgens = 1000;
	options.px = 0.7f;
	// options.pm = 0.001f; // This is set by the graph

    options.selector = Proportionate;
    options.crossover = OX;
    options.mutator = Swap;

	// new stuff for mmkcpp
    options.numRobots = 1;

    string graphName = "graph-gdb1";

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
    options.outfile = "../results/fitness-" + GAParamsStr + ".tsv";

}

void GA::Init(){
    // Initalize GA
    graph = new Graph(&options);
    //cout << *graph << endl;
	parent = new Population(&options, graph);
	child  = new Population(&options, graph);
	parent->Init(); // evaluates, stats, and reports on initial population
	parent->Statistics();
	parent->Report(0);
}

void GA::Run(){
	for(unsigned long int i = 1; i < options.maxgens; i++){
		parent->Generation(child);
		if (options.selector != SelectorType::CHC) {
            child->EvaluateMembers();
        }
		if (child->bestIndividual->fitness > bestFitness) {
            bestFitness = child->bestIndividual->fitness;
            child->bestIndividual->WriteToFile(options.decodedfile);
		}
        child->Statistics();
		child->Report(i);

		Population *tmp = parent;
		parent = child;
		child = tmp;
	}
}

