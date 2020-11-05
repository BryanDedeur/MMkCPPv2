/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Copyright: University of Nevada, Reno
 * @Date: 10/18/20
 */

#include <time.h>
#include <iostream>
#include <fstream>
#include "GA.h"
using namespace std;

int main(int argc, char *argv[]) {
    clock_t start, mid, end;
    start = clock();

    cout << "Start MMkCPP genetic algorithm" << endl; // prints Simple genetic algorithm

    int numTrials = 30;

    GA ga = GA(argc, argv);
    double aveTime = 0;
    for (int i = 1; i <= numTrials; i++) {
        mid = clock();
        ga.options.randomSeed = time(NULL);
        ga.Init();
        ga.Run();
        cout << "Trial " << i << " seed(" << ga.options.randomSeed << "): GA "<< ga.options.maxgens << " generations complete" << endl;
        end = clock();
        aveTime += double(end - mid);
    }
    end = clock();
    cout << "Finished " << numTrials << " trials in " << double(end - start) / 1000 << "s (" << (aveTime / numTrials) / 1000 << "s per trial)" << endl << endl;

    cout << "Results: " << ga.options.outfile << endl;
    cout << "Best Individual Decoded: " << ga.options.decodedfile << endl;

    return 0;
}