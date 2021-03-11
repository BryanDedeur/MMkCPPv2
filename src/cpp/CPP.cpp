/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Bryan Dedeurwaerder, Johnathan Peters
 * @Copyright: University of Nevada, Reno
 * @Date: 10/18/20
 */

#include "CPP.h"

CPP::CPP(Graph* gph) {
	graph = gph;
    solution = new Path(graph);
    CheckIfCacheExists();
}

void CPP::Solve() {

}

void CPP::FindOddDegreeNodes() {

}

void CPP::FindPairsBetweenOddDegreeNodes() {

}

void CPP::ReadCacheFile(string filePath) {
    vector<string> lines = SplitFileByLines(filePath);
    vector<float> numbers = ExtractNumbers(lines[0]);
    for (int i = 0; i < numbers.size(); i++) {
        int v = int(numbers[i]);
        solution->AddVertex(v);
    }
}

void CPP::WriteToCacheFile(string filePath) {

}

void CPP::CheckIfCacheExists() {

    string cacheFile = "../src/cpp/cached/" + graph->graphName + ".cache";
    if (FileExists(cacheFile)) {
        ReadCacheFile(cacheFile);
    }
    else {
        Solve();
        WriteToCacheFile(cacheFile);
    }
}
