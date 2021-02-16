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

void WriteToFile(stringstream &ss, std::string filename){
    std::ofstream outFile;
    outFile.open(filename, ios::app);
    outFile << ss.rdbuf();
    outFile.close();
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

string ExtractFileFormat(string filePath) {
    size_t pos = 0;
    std::string token;
    string delimiter = "/";
    string delimeter2 = ".";
    while ((pos = filePath.find(delimiter)) != std::string::npos) {
        token = filePath.substr(0, pos);
        filePath.erase(0, pos + delimiter.length());
        if ((pos = filePath.find(delimeter2)) != std::string::npos)
            filePath.erase(0, pos);
    }
    return filePath;
}

vector<float> ExtractNumbers(string str)
{
    stringstream ss;

    vector<float> numbers = vector<float>();

    /* Storing the whole string into string stream */
    ss << str;

    /* Running loop till the end of the stream */
    string temp;
    float found;
    while (!ss.eof()) {

        /* extracting word by word from stream */
        ss >> temp;

        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found)
            numbers.push_back(float(found));

    }
    return numbers;
}

vector<string> SplitFileByLines(string filePath) {
    fstream readFile;
    readFile.open(filePath, ios::in);

    vector<string> lines = vector<string>();

    if (!readFile.is_open()) {
        AssertWithErrorMessage("Cannot locate file: " + filePath, readFile.is_open());
    }
    else {
        string line = "";
        while (getline(readFile, line, '\n')) {
            lines.push_back(line);
        }
    }
    readFile.close();

    return lines;
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
    if (!didPass)
        std::cerr << message << std::endl;
    assert(didPass);
}





