/*
 * Individual.h
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include "Const.h"

class Individual {
public:
	Individual(int chromLen);
	virtual ~Individual();

	int chromLength;
	int chromosome[MAX_CHROMLENGTH];
	double fitness;

	void Init();
	void Mutate(double pm);
};

#endif /* INDIVIDUAL_H_ */
