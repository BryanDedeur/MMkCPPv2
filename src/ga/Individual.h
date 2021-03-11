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

class GA;

class Individual {
    public:
        Individual(Options *opts, Graph *graph, GA* ga);
        virtual ~Individual();

	    double fitness;
	    double totalTravelDistance;
        int seed;

        vector<int> chromosome;

        vector<int> visitedEdgeCounts;
        vector<int> robotChromStartIndex;

        Graph* graph;
        Options* options;

        void GenerateChromosomeFromCPP();
        void GenerateRandomChromosome();
        void GenerateRandomWalkChromosome();

        void SetGeneAtPosition(int& value, int& position);
        void ResizeChromosome(int& newSize);
        bool SanityCheckPassed();

        void AddEdgeToChromosome(int edgeId);
        void AddEdgeToChromosome(int edgeId, int index);
        void AddEdgeToChromosome(int edgeId, bool randomize);

        void InjectMissingEdges();
        void ConvertChromosomeToTour();
        void DistributeTourBetweenRobots();
        void ConvertRobotToursToChromosome();
        float GetFurthestTravelingRobotTourLength();

        void Swap(int &indexA, int &indexB);

        void Evaluate(); 
        string TourToString();

        // new additions
        Individual& operator=(Individual other);
        // operator overrides
        friend ostream& operator<<(ostream& os, const Individual& individual);
        vector<Path> tours; // each robot contains its own edge tour

    private:
        GA* ga;
};

#endif /* INDIVIDUAL_H_ */
