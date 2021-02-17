/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Bryan Dedeurwaerder, Johnathan Peters
 * @Copyright: University of Nevada, Reno
 * @Date: 10/18/20
 */

#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include "Options.h"
#include "../graph/Graph.h"
#include "Gene.h"

#include <iostream>
#include <string>
#include <vector>

class Individual {
public:
    Individual(Options *opts, Graph *graph);
    virtual ~Individual();

	vector<Gene> chromosome;
	double fitness;
	double totalTravelDistance;
    Graph* graph;
    Options* options;
    Path* decoding; // one path per robot
    int* robotChromIndex; // for storing the starting index of every robot
    long int seed;

    Path unassignedPath;


    void Init();
    void Mutate(double pm);
    void Swap(int &indexA, int &indexB);
    void Evaluate(); // Reasoning: seems like evaluation is better done from within the class for better access to data members
    bool CheckIfValidRoutes();
    void FindTravelCosts();

    void Decode();
    void LogRoutes(string filename); // There might be a better way of doing this
    void UpdateRobotChromIndex();
    bool ChromContains(Gene* arr, Gene &val);


    // new additions
    Individual& operator=(Individual other);
    // operator overrides
    friend ostream& operator<<(ostream& os, const Individual& individual);

};

#endif /* INDIVIDUAL_H_ */
