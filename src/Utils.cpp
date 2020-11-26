/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Copyright: University of Nevada, Reno
 * @Date: 10/18/20
 */

#include "Utils.h"



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

string ExtractNameOfFile(string filePath) {
    size_t pos = 0;
    std::string token;
    string delimiter = "/";
    string delimeter2 = ".";
    while ((pos = filePath.find(delimiter)) != std::string::npos) {
        token = filePath.substr(0, pos);
        filePath.erase(0, pos + delimiter.length());
        if ((pos = filePath.find(delimeter2)) != std::string::npos)
            filePath.erase(pos, token.length() - pos);
    }
    return filePath;
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

void AssertWithErrorMessage(string message, bool didPass) {
    std::cerr << message << std::endl;
    assert(didPass);
}





