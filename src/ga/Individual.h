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

        void AddGeneToChromosome(int value, int index);

        void GenerateRandomChromosome();

        void Swap(int& indexA, int& indexB);

        void SetGeneAtPosition(int& value, int& position);
        void ResizeChromosome(int& newSize);
        bool SanityCheckPassed();

        int& FindNextSubTourStartNode(map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges);
        int& FindVisitedNodeWithUnvisitedEdges(map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges);
        int& FindUnvisitedNodeWithUnvisitedEdges(map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges);
        void UntrackEdgeFromNode(int node, Edge& edge, map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges);
        int DetermineNextNodeForSubtour(Path& cycle, int decision, map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges);
        void AdjustEdgeTracking(int node, int previousNode, map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges);
        bool SubTourIsCircle(Path& subTour);
        void StartNewTour(map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges);
        bool NodeProgressesForward(int node);

        void ConvertChromosomeToSubTours();
        void ConvertSubToursToTours();

        void Evaluate(); 
        string TourToString();

        // new additions
        Individual& operator=(Individual other);
        // operator overrides
        friend ostream& operator<<(ostream& os, const Individual& individual);
        vector<Path> tours; // each robot contains its own edge tour

        vector<Path> subTours;


    private:
        GA* ga;


};

#endif /* INDIVIDUAL_H_ */
