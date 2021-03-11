/*
 * @Project: MMkCPP
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#include "GA.h"
#include "Individual.h"
#include "../Utils.h"
#include <map>

Individual::Individual(Options* opts, Graph* gph, GA* theGA) {
    fitness = -1;
    graph = gph;
    options = opts;
    ga = theGA;
    seed = opts->randomSeed;

    totalTravelDistance = 0;

    // create a empty tour for each robot
    for (int r = 0; r < options->numRobots; r++) {
        tours.push_back(Path(gph));
    }

    // create counter for every edge
    for (int e = 0; e < graph->numEdges; e++) {
        visitedEdgeCounts.push_back(0);
    }
}

Individual::~Individual() {

}

void Individual::GenerateChromosomeFromCPP() {
    for (int e = 0; e < ga->cpp->solution->edgePath.size(); e++) {
        AddEdgeToChromosome(ga->cpp->solution->edgePath[e].id);
    }

    //// scramble ga a little bit
    //int index = rand() % chromosome.size();
    //int otherIndex = rand() % chromosome.size();
    //Swap(index, otherIndex);
}

// generates a random chromosome containing all edges in the graph
void Individual::GenerateRandomChromosome() {
    // add all the edges in the graph to a random robot tour
    for (int e = 0; e < graph->numEdges; e++) {
        AddEdgeToChromosome(e);
    }

	// swap every edge with a random edge
	for (int geneIndex = 0; geneIndex < chromosome.size(); geneIndex++) {
	    int otherIndex = rand() % chromosome.size();
        Swap(geneIndex, otherIndex);
	}
}

// generates a random chromosome containing all edges in the graph
void Individual::GenerateRandomWalkChromosome() {
    for (; chromosome.size() < graph->numEdges;) {
        int start = rand() % graph->numEdges;
        int end = rand() % graph->numEdges;
        Path* path = graph->GetShortestPathBetweenEdges(graph->GetEdge(start), graph->GetEdge(end));
        for (int i = 0; i < path->edgePath.size(); i++) {
            chromosome.push_back(path->edgePath[i].id);
        }
    }
}

// sets the gene 
void Individual::SetGeneAtPosition(int& value, int& position) {
    chromosome[position] = value;
}

void Individual::ResizeChromosome(int& newSize) {
    if (chromosome.size() < newSize) {
        for (int i = (newSize - chromosome.size()) - 1; i > -1; i--) {
            chromosome.push_back(0);
        }
    }
    else if (chromosome.size() > newSize) {
        for (int i = (chromosome.size() - newSize) - 1; i > -1; i--) {
            chromosome.pop_back();
        }
    }
}

// checks to make sure every edge is traveled at least once
bool Individual::SanityCheckPassed() {
    vector<int> edgeCounter;
    for (int i = 0; i < graph->numEdges; i++) {
        edgeCounter.push_back(0);
    }

    for (int i = 0; i < chromosome.size(); i++) {
        edgeCounter[chromosome[i]]++;
    }

    for (int i = 0; i < graph->numEdges; i++) {
        if (edgeCounter[i] == 0) {
            return false;
        }
    }
    return true;
}

// adds a new edge to the chromosome
void Individual::AddEdgeToChromosome(int edgeId) {
    chromosome.push_back(edgeId);
    totalTravelDistance += graph->GetEdge(edgeId).cost;
}

// adds a new edge to the chromosome
void Individual::AddEdgeToChromosome(int edgeId, int index) {
    // this is really slow, consider speeding this up somehow
    if (index >= chromosome.size()) {
        AddEdgeToChromosome(edgeId);
    }
    else {
        chromosome.insert(chromosome.begin() + index, edgeId);
    }
}

// adds a new edge to the chromosome
void Individual::AddEdgeToChromosome(int edgeId, bool randomize) {
    AddEdgeToChromosome(edgeId, int(rand() % chromosome.size()));
}

void Individual::InjectMissingEdges() {
    int i = 0;
    // reset counters
    for (i = 0; i < visitedEdgeCounts.size(); i++) {
        visitedEdgeCounts[i] = 0;
    }

    // count occurances
    for (i = 0; i < chromosome.size(); i++) {
        visitedEdgeCounts[chromosome[i]]++;
    }

    // inject missing
    for (i = 0; i < visitedEdgeCounts.size(); i++) {
        if (visitedEdgeCounts[i] == 0) {
            AddEdgeToChromosome(i, true);
        }
    }
}

// adds edges to chromosome so the tour is fully connected. Every edge leads to a connected edge (decoding in a way)
void Individual::ConvertChromosomeToTour() {
    // Make path using dijkstras
    Path tempPath = Path(graph);    
    for (int geneIndex = 0; geneIndex < chromosome.size(); geneIndex++) {
        tempPath.AddEdge(graph->GetEdge(chromosome[geneIndex]));
    }

    // Shove path back into chromosome
    int chromSize = 0;
    totalTravelDistance = 0;
    for (int i = 0; i < tempPath.edgePath.size(); i++) {
        if (i < chromosome.size()) {
            chromosome[i] = tempPath.edgePath[i].id;
        }
        else {
            chromosome.push_back(tempPath.edgePath[i].id);
        }
        chromSize++;
        totalTravelDistance += tempPath.edgePath[i].cost;
    }

    // remove left over stuff from previous chromosome
    for (int i = chromSize; i < chromosome.size(); i++) {
        chromosome.pop_back();
    }
}

void Individual::DistributeTourBetweenRobots() {
    float splitTourLength = totalTravelDistance / options->numRobots;

    int i = 0; // index is outside the for loop so we can start at the last visited gene in the chromosome
    for (int r = 0; r < options->numRobots; r++) {
        tours[r].Reset();

        // add starting vertex
        tours[r].AddVertex(options->closedRouteVertex);

        // add edges from chromosome until cost exceeds the split between robots
        float tempEdgeCost = 0;
        for (; i < chromosome.size(); i++) {
            if (tempEdgeCost > splitTourLength && r < options->numRobots - 1) {
                break;
            } else {
                tours[r].AddEdge(graph->GetEdge(chromosome[i]));
                tempEdgeCost += graph->GetEdge(chromosome[i]).cost;
            }
        }

        // add ending vertex
        tours[r].AddVertex(options->closedRouteVertex);
    }
}

void Individual::ConvertRobotToursToChromosome() {
    totalTravelDistance = 0;
    int chromSize = 0;
    for (int r = 0; r < options->numRobots; r++) {
        for (int i = 0; i < tours[r].edgePath.size(); i++) {
            if (i < chromosome.size()) {
                chromosome[i] = tours[r].edgePath[i].id;
            }
            else {
                chromosome.push_back(tours[r].edgePath[i].id);
            }
            chromSize++;
            totalTravelDistance += tours[r].edgePath[i].cost;
        }
    }
    // remove left over stuff from previous chromosome
    for (int i = chromSize; i < chromosome.size(); i++) {
        chromosome.pop_back();
    }
}

float Individual::GetFurthestTravelingRobotTourLength() {
    Path* best = &tours[0];
    for (int r = 0; r < options->numRobots; r++) {
        if (best->GetCost() < tours[r].GetCost()) {
            best = &tours[r];
        }
        //tours[r].SanityCheckPass();
    }
    return best->GetCost();
}


// swaps two chromosome indexes, preserves edges
void Individual::Swap(int& indexA, int& indexB) {
    int temp = chromosome[indexA];
    chromosome[indexA] = chromosome[indexB];
    chromosome[indexB] = temp;
}

void Individual::Evaluate() {
    InjectMissingEdges();
    ConvertChromosomeToTour();
    DistributeTourBetweenRobots();
    ConvertRobotToursToChromosome();

    fitness = GetFurthestTravelingRobotTourLength();
    //fitness = totalTravelDistance;
}

string Individual::TourToString() {
    string route = "{";
    for (int r = 0; r < options->numRobots; r++) {
        route += "{";
        for (int i = 0; i < tours[r].edgePath.size(); i++) {
            if (i == tours[r].edgePath.size() - 1) {
                route += to_string(tours[r].edgePath[i].id);
            }
            else {
                route += to_string(tours[r].edgePath[i].id) + ", ";
            }
        }
        if (r == options->numRobots - 1) {
            route += "}";
        }
        else {
            route += "}, ";
        }
    }
    route += "}";
    return route;
}

ostream& operator<<(ostream& os, const Individual& individual)
{
    os << "chromosome: [";
    //for (int i = 0; i < individual.options->chromLength; i++) {
    //    os << individual.chromosome[i];
    //    if (i < individual.options->chromLength - 1) {
    //        os << ",";
    //    }
    //}
    //os << "]" << endl;


    //for (int i = 0; i < individual.options->numRobots; i++) {
    //    os << individual.decoding[i] << endl;
    //}
    return os;
}

Individual& Individual::operator=(Individual other){
    if (this != &other) {
        this->graph = other.graph;
        this->chromosome = other.chromosome;
        this->visitedEdgeCounts = other.visitedEdgeCounts;
        this->robotChromStartIndex = other.robotChromStartIndex;
        for (int i = 0; i < other.tours.size(); i++) {
            this->tours[i] = other.tours[i];
        }
        this->fitness = other.fitness;
        this->totalTravelDistance = other.totalTravelDistance;
        this->seed = other.seed;
    }
    return *this;
}
