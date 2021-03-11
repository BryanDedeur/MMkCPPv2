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

    cout << "Checking if best results are valid: " << endl;

    for (int i = 0; i < ga.best->tours.size(); i++) {
        cout << "Best tour " << i << ": ";
        if (ga.best->tours[i].SanityCheckPass()) {
            cout << "Valid! ";
            cout << "cost: " << ga.best->tours[i].GetCost();
        }
        else {
            cout << "Invalid :(" << endl;
        }
    }

    return 0;
}
