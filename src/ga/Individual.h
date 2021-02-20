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

#include <iostream>
#include <string>
#include <vector>

class Individual {
    public:
        Individual(Options *opts, Graph *graph);
        virtual ~Individual();

	    double fitness;
	    double totalTravelDistance;

        vector<int> chromosome;

        vector<int> visitedEdgeCounts;
        vector<int> robotChromStartIndex;

        Graph* graph;
        Options* options;

        void GenerateRandomChromosome();
        void AddEdgeToChromosome(int edgeId);
        void AddEdgeToChromosome(int edgeId, int index);
        void AddEdgeToChromosome(int edgeId, bool randomize);

        void InjectMissingEdges();
        void ConvertChromosomeToTour();
        void DistributeTourBetweenRobots();

        //void RepairTour(int& robot, int& startChromeIndex, int& endChromeIndex);

        void Swap(int &indexA, int &indexB);
        void Replace(int& index, int& edgeId);

        void Evaluate(); 

        void Decode();

        void LogTours(string filename);


        // new additions
        Individual& operator=(Individual other);
        // operator overrides
        friend ostream& operator<<(ostream& os, const Individual& individual);

    private:
        vector<Path> tours; // each robot contains its own edge tour
};

#endif /* INDIVIDUAL_H_ */
