/*
 * Individual.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include <Individual.h>
#include <Utils.h>

Individual::Individual(int len) {
	// TODO Auto-generated constructor stub
	chromLength = len;
	fitness = -1;
}

Individual::~Individual() {
	// TODO Auto-generated destructor stub
}

void Individual::Init(){
	for(int i = 0; i < chromLength; i++){
		chromosome[i] = Flip(0.5f);
	}
}

void Individual::Mutate(double pm){
	for(int i = 0; i < chromLength; i++){
		if(Flip(pm))
			chromosome[i] = 1 - chromosome[i];
	}

}
