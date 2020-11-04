//============================================================================
// Name        : gacplus.cpp
// Author      : Sushil J Louis
// Version     :
// Copyright   : Copyright University of Nevada, Reno
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "GA.h"
using namespace std;

int main(int argc, char *argv[]) {
    cout << "Start MMkCPP genetic algorithm" << endl; // prints Simple genetic algorithm

    GA ga = GA(argc, argv);
    for (int i = 0; i < 30; i++) {
        ga.Init();
        ga.Run();
        cout << "Trial " << i << ": GA "<< ga.options.maxgens << " generations complete" << endl;
    }

    // TODO fix finding the best individual
    cout << endl << "Best Individual: " << endl;
    //cout << *ga.parent->members[0] << endl;
    //cout << *ga.child->members[59] << endl;


    return 0;
}