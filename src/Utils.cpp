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

void ClearFile(std::string filename) {
    std::ofstream ofs;
    ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void WriteBufToFile(std::string buf, std::string filename){
	std::ofstream ofs(filename, std::ofstream::app);
	if(ofs.good()){
		ofs << buf;
	}
	ofs.flush();
	ofs.close();
}

bool ArrayContains(int* arr, int val)
{
    for(int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        if(arr[i] == val)
        {
            return true;
        }
    }
    return false;
}


int Flip(float prob){
	return (rand() < prob*RAND_MAX ? 1 : 0);
}

/* greater than equal to low and strictly less than high */
int IntInRange(int low, int high){
	return low + rand()%(high - low);
}

/* greater than equal to 0 and less than 1 */
float RandomFraction(){
	return ((float)(rand()%1000))/(float)1000.0;
}




