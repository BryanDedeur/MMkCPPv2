/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
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
        std::swap(value, other.value);
        std::swap(isRobot, other.isRobot);
        return *this;
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
    Individual(Options &opts, Graph *graph);
    virtual ~Individual();

	int chromLength;
	Gene chromosome[MAX_CHROMLENGTH];
	double fitness;

    void Init();
    void Mutate(double pm);

    // new additions

    Graph* graph;
    Options* options;

    // operator overrides
    friend ostream& operator<<(ostream& os, const Individual& individual);

    void Swap(int &indexA, int &indexB);
    void Evaluate(); // Reasoning: seems like evaluation is better done from within the class for better access to data members
    void Decode();
    Path* decoding; // one path per robot

    int* robotChromIndex; // for storing the starting index of every robot

//    int totalTravelDistance;
//    float travelDistribution; // for each robot sum robot travel distance / totalTravelDistance

};

#endif /* INDIVIDUAL_H_ */
