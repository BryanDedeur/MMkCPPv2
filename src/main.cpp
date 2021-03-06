/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Jonathan Peters
 * @Copyright: University of Nevada, Reno
 * @Date: 10/18/20
 */

#include <iostream>
#include "ga/GA.h"

using namespace std;

int main(int argc, char *argv[]) {

    GA ga = GA(argc, argv);
    //cout << *ga.graph << endl;
    for (int i = 1; i <= ga.options.numRuns; i++) {
        ga.Init();
        ga.Run();
    }
    ga.Report();

    return 0;
}
