/*
 * GA.h
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#ifndef GA_H_
#define GA_H_

#include "Population.h"
#include "Options.h"
#include "Graph.h"

class GA {

private:
	void Construct();

public:
	GA(int argc, char *argv[]);

	virtual ~GA();

	//--------------------------------
	Graph *graph;
	Population *parent;
	Population *child;
	Options options;


	void SetupOptions(int argc, char*argv[]);

	void Init();
	void Run();

};

#endif /* GA_H_ */
