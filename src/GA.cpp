/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#include "GA.h"
#include <string>
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
	options.randomSeed = 121;
	options.popSize = 30;
	options.chromLength = 10;
	options.maxgens = 60;
	options.px = 0.7f;
	options.pm = 0.001f;
    options.infile = std::string ("infile");
    options.outfile = std::string("../outfile");

	// new stuff for mmkcpp
	options.numRobots = 4;
	options.datafile = std::string("../benchmarks/mmkcpp/graph-gdb1.csv");
}

void GA::Init(){
    graph = new Graph(&options);
    //cout << *graph << endl;
	parent = new Population(&options, graph);
	child  = new Population(&options, graph);
	parent->Init(); // evaluates, stats, and reports on initial population
	parent->Statistics();
	parent->Report(0);

    bestIndividual = new Individual(&options, graph);
    bestIndividual->Init();
    bestIndividual->Evaluate();
}

void GA::Run(){
	for(unsigned long int i = 1; i < options.maxgens; i++){
		parent->Generation(child);
		child->EvaluateMembers();
		child->Statistics();
		child->Report(i);

		Population *tmp = parent;
		parent = child;
		child = tmp;
		if (bestIndividual->fitness > parent->bestIndividual->fitness) {
		    *bestIndividual = *parent->bestIndividual;
		}
	}
}

