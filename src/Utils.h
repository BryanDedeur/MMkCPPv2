/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Copyright: University of Nevada, Reno
 * @Date: 10/18/20
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

using std::string;

void ClearFile(std::string filename);
void WriteBufToFile(std::string buf, std::string filename);
std::string ExtractNameOfFile(std::string);
float RandomFraction();
int Flip(float prob);
int IntInRange(int low, int high);
void AssertWithErrorMessage(string message, bool didPass);

#endif /* UTILS_H_ */
