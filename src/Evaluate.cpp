/*
 * Evaluate.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */


#include <Evaluate.h>
#include <math.h>

double Eval(Individual *individual){
	double sum = 0;
	for(int i = 0; i < individual->chromLength; i++){
		sum += (individual->chromosome[i] == 1 ? 1: 0);
	}
	return sum;
}
