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
#include <string>

using namespace std;

void runCommand(string commandStr) {
    cout << " - " << commandStr << endl;
    const char* command = commandStr.c_str();
    int ret_val = system(command);

    if(!(ret_val == 0 && errno == 0)) {
        cerr << "There was an error with the command: " << ret_val << endl;
    }
}

int main(int argc, char *argv[]) {
    clock_t start, mid, end;
    start = clock();

    const int numTrials = 30;

    // Start the GA
    GA ga = GA(argc, argv);
    cout << "Starting MMkCPP genetic algorithm on graph " << ga.options.datafile << endl; // prints Simple genetic algorithm
    double aveTime = 0;
    for (int i = 1; i <= numTrials; i++) {
        mid = clock();
        ga.options.randomSeed = time(NULL);
        ga.Init();
        ga.Run();
        end = clock();
        cout << "Run " << i << " seed(" << ga.options.randomSeed << "): "<< ga.options.maxgens << " generations of population size " << ga.options.popSize << " evolved in " << double(end - mid)/1000 << "s" << endl;
        aveTime += double(end - mid);
    }
    end = clock();
    cout << "Finished " << numTrials << " runs in " << double(end - start) / 1000 << "s (" << (aveTime / numTrials) / 1000 << "s per runs)" << endl << endl;

    // Show where to find the output files
    cout << "Results: " << ga.options.outfile << endl;
    cout << "Best Individual Decoded: " << ga.options.decodedfile << endl << endl;

    // Call the visualization stuff
    cout << "Running visualization commands: " << endl;
    runCommand("python3 ../visualizations/FitnessPlot.py " + ga.options.outfile);
    runCommand("python3 ../visualizations/GraphTravelPlans.py " + ga.options.decodedfile + " " + ga.options.datafile);
    runCommand("python3 ../visualizations/GraphTravelOverlap.py " + ga.options.decodedfile + " " + ga.options.datafile);

    return 0;
}