//============================================================================
// Name        : gacplus.cpp
// Author      : Sushil J Louis
// Version     :
// Copyright   : Copyright University of Nevada, Reno
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <GA.h>
using namespace std;

int main(int argc, char *argv[]) {
	cout << "Simple genetic algorithm" << endl; // prints Simple genetic algorithm

	GA ga = GA(argc, argv);

	ga.Init();
	ga.Run();

	return 0;
}
