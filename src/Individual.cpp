/*
 * @Project: MMkCPP
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#include "Individual.h"
#include "Utils.h"

Individual::Individual(Options &opts, Graph *gph) : chromLength(gph->numEdges + opts.numRobots) {
    fitness = -1;
    graph = gph;
    options = &opts;
}

Individual::~Individual() {
	// TODO Auto-generated destructor stub
}

void Individual::Init(){
    // Initialize the chromosome with every possible edge and every possible robot
	for(int i = 0; i < chromLength; i++) {
        if (i >= graph->numEdges) {
            chromosome[i].value = i - graph->numEdges;
            chromosome[i].isRobot = true;
        } else {
            chromosome[i].value = i;
        }
	}
	// TODO randomize chromosome
}

void Individual::Mutate(double pm){
	for(int i = 0; i < chromLength; i++){
		if(Flip(pm)) {

		}
	}
}

void Individual::Evaluate() {
    // calculate the total travel distance
    for (int i = 0; i < chromLength; i++) {
        //sum += individual->calculateFitness();
    }

    // calculate the distribution of travel among all robots

}
