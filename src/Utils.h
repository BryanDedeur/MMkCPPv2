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
#include <sstream>
#include <vector>

using namespace std;

bool FileExists(string& filename);
void ClearFile(string filename);
void WriteToFile(stringstream &ss, string filename);
string ExtractNameOfFile(string filePath);
string ExtractFileFormat(string filePath);
vector<float> ExtractNumbers(string str);
vector<string> SplitFileByLines(string filePath);
float RandomFraction();
int Flip(float prob);
int IntInRange(int low, int high);
void AssertWithErrorMessage(string message, bool didPass);

#endif /* UTILS_H_ */
