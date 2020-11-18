/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Copyright: University of Nevada, Reno
 * @Date: 10/18/20
 */

#include <iostream>
#include "GA.h"

using namespace std;

int main(int argc, char *argv[]) {

    GA ga = GA(argc, argv);
    cout << endl << "Starting GA on graph " << ga.options.graphName << " with " << ga.options.numRobots << " robots for " << ga.options.numRuns << " runs of " << ga.options.maxgens << " generations with population size " << ga.options.popSize << ": " << endl;
    for (int i = 1; i <= ga.options.numRuns; i++) {
        ga.Init();
        ga.Run();
    }
    ga.Report();

    return 0;
}
