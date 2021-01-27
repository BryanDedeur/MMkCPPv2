/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Copyright: University of Nevada, Reno
 * @Date: 10/18/20
 */

#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <string>
#include "Const.h"
#include "Graph.h"
#include <iostream>

struct Gene {
    int value;
    bool isRobot;

    Gene() : value(0), isRobot(false) {}
    Gene& operator=(Gene other) { // Assignment operator copying gene struct
        if (this != &other) {
            this->value = other.value;
            this->isRobot = other.isRobot;
        }
        return *this;
    }

    bool operator==(Gene other) {
        return value == other.value && isRobot == other.isRobot;
    }

    friend ostream& operator<<(ostream &os, const Gene& gene)
    {
        if (gene.isRobot) {
            return os << "R" << gene.value;
        }
        return os << gene.value;
    }
};



class Individual {
public:
    Individual(Options *opts, Graph *graph);
    virtual ~Individual();

	Gene chromosome[MAX_CHROMLENGTH];
	double fitness;
	int totalTravelDistance;
    Graph* graph;
    Options* options;
    Path* decoding; // one path per robot
    int* robotChromIndex; // for storing the starting index of every robot
    long int seed;

    void Init();
    void Mutate(double pm);
    void Swap(int &indexA, int &indexB);
    void Evaluate(); // Reasoning: seems like evaluation is better done from within the class for better access to data members
    bool CheckIfValidRoutes();
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
