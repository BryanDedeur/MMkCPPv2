/*
 * Utils.h
 *
 *  Created on: Sep 20, 2020
 *      Author: sushil
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <string>

void WriteBufToFile(std::string buf, std::string filename);

float RandomFraction();
int Flip(float prob);
int IntInRange(int low, int high);

#endif /* UTILS_H_ */
