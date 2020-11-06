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
	options.popSize = 30;
	options.chromLength = 10;
	options.maxgens = 50;
	options.px = 0.7f;
	options.pm = 0.001f;

	// strings below helpful for naming the files
    options.selector = FitnessProportional;
    options.crossover = OX;
    options.mutator = Swap;


	// new stuff for mmkcpp
    options.numRobots = 4;

    string filename = "graph-gdb1";
	options.datafile = "../benchmarks/mmkcpp/" + filename + ".csv";
	options.decodedfile = "../routes";

    options.infile = "../infile";
    options.outfile = "../ga-results-" + filename; // +
//            "-" + selectors[options.selector] +
//            "-" + crossovers[options.crossover] +
//            "-" + mutators[options.mutator];
}

void GA::Init(){
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
		child->EvaluateMembers();
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

