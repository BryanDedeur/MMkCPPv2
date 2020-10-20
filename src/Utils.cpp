/*
 * Utils.cpp
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>

void WriteBufToFile(std::string buf, std::string filename){
	std::ofstream ofs(filename, std::ofstream::app);
	if(ofs.good()){
		ofs << buf;
	}
	ofs.flush();
	ofs.close();
}

int Flip(float prob){
	return (random() < prob*RAND_MAX ? 1 : 0);
}

/* greater than equal to low and strictly less than high */
int IntInRange(int low, int high){
	return low + random()%(high - low);
}



/* greater than equal to 0 and less than 1 */
float RandomFraction(){
	return ((float)(random()%1000))/(float)1000.0;
}

