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

// adds a new edge to the chromosome
void Individual::AddGeneToChromosome(int value, int index) {
    if (!(index < chromosome.size())) {
        while (index >= chromosome.size()) {
            chromosome.push_back(0);
        }
    }

    chromosome[index] = value;
}

// generates a random chromosome containing all edges in the graph
void Individual::GenerateRandomChromosome() {
    for (int e = 0; e < graph->numEdges; e++) {
        AddGeneToChromosome(rand() % graph->largestNumEdgesConnectedToAnyVertex, e);
    }
}

// swaps two chromosome indexes, preserves edges
void Individual::Swap(int& indexA, int& indexB) {
    int temp = chromosome[indexA];
    chromosome[indexA] = chromosome[indexB];
    chromosome[indexB] = temp;
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

    for (int r = 0; r < options->numRobots; r++) {
        for (int i = 0; i < tours[r].edgePath.size(); i++) {
            edgeCounter[tours[r].edgePath[i].id]++;
        }
    }

    for (int i = 0; i < graph->numEdges; i++) {
        if (edgeCounter[i] == 0) {
            return false;
        }
    }
    return true;
}

int Individual::DetermineNextNodeForSubtour(Path& cycle, int decision, map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges){
    if (visitedVerticesWithUnvistedEdges[cycle.vertexPath.back()].size() == 0) {
        return -1;
    }
    int localDecision = decision - ((decision / visitedVerticesWithUnvistedEdges[cycle.vertexPath.back()].size()) * visitedVerticesWithUnvistedEdges[cycle.vertexPath.back()].size());
    Edge* currentEdge = visitedVerticesWithUnvistedEdges[cycle.vertexPath.back()][localDecision];
    int nextVertex = graph->GetOppositeVertexOnEdge(cycle.vertexPath.back(), *currentEdge);
    return nextVertex; 
}

int& Individual::FindVisitedNodeWithUnvisitedEdges(map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges) {
    int value = -1;
    for (int i = 0; i < visitedVerticesWithUnvistedEdges.size(); i++) {
        if (visitedVerticesWithUnvistedEdges[i].size() > 0) {
            return i;
        }
    }
    return value;
}

int& Individual::FindUnvisitedNodeWithUnvisitedEdges(map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges) {
    int value = -1;
    for (int i = 0; i < graph->numVertices; i++) {
        if (visitedVerticesWithUnvistedEdges.find(i) != visitedVerticesWithUnvistedEdges.end()) {
            return i;
        }
    }
    return value;
}

int& Individual::FindNextSubTourStartNode(map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges) {
    int nextNode = FindVisitedNodeWithUnvisitedEdges(visitedVerticesWithUnvistedEdges);
    if (nextNode == -1) {
        nextNode = FindUnvisitedNodeWithUnvisitedEdges(visitedVerticesWithUnvistedEdges);
    }
    return nextNode;
}

void Individual::UntrackEdgeFromNode(int node, Edge& edge, map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges) {
    for (int j = 0; j < visitedVerticesWithUnvistedEdges[node].size(); j++) {
        if (visitedVerticesWithUnvistedEdges[node][j]->id == edge.id) {
            visitedVerticesWithUnvistedEdges[node].erase(visitedVerticesWithUnvistedEdges[node].begin() + j);
            break;
        }
    }
}

void Individual::AdjustEdgeTracking(int node, int previousNode, map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges) {
    // if node has been visited already
    if (visitedVerticesWithUnvistedEdges.find(node) != visitedVerticesWithUnvistedEdges.end()) {
        if (previousNode != -1) {
            Edge edge = graph->GetEdge(node, previousNode);
            UntrackEdgeFromNode(node, edge, visitedVerticesWithUnvistedEdges);
            UntrackEdgeFromNode(previousNode, edge, visitedVerticesWithUnvistedEdges);
        }
    }
    else {
        // if node has not been visited already
        visitedVerticesWithUnvistedEdges[node] = graph->GetEdgesConnectedToVertex(node);
        if (previousNode != -1) {
            Edge edge = graph->GetEdge(node, previousNode);
            UntrackEdgeFromNode(node, edge, visitedVerticesWithUnvistedEdges);
            UntrackEdgeFromNode(previousNode, edge, visitedVerticesWithUnvistedEdges);
        }
    }
}

void Individual::StartNewTour(map<int, vector<Edge*>>& visitedVerticesWithUnvistedEdges) {
    // start new tour
    circles.push_back(Path(graph));
    int nextVertex = FindNextSubTourStartNode(visitedVerticesWithUnvistedEdges);
    circles.back().AddVertex(nextVertex);
    AdjustEdgeTracking(circles.back().vertexPath.back(), -1, visitedVerticesWithUnvistedEdges);
}

bool Individual::NodeProgressesForward(int node) {
    return node != -1;
}

bool Individual::SubTourIsCircle(Path& subTour) {
    return subTour.vertexPath.front() == subTour.vertexPath.back();
}

void Individual::IntegrateSubTourIntoTour(list<int>& tempTour, Path& subTour, bool lastTour) {
    if (tempTour.size() == 0) {
        for (int i = 0; i < subTour.vertexPath.size(); i++) {
            tempTour.push_back(subTour.vertexPath[i]);
        }
        return;
    }
    else {
        // find start vertex in tempTour
        list<int>::reverse_iterator rit;
        for (rit = tempTour.rbegin(); rit != tempTour.rend(); ++rit) {
            if (*rit == subTour.vertexPath.front()) {
                for (int i = 0; i < subTour.vertexPath.size(); ++i) {
                    list<int>::reverse_iterator rit2 = rit;
                    rit2++;
                    tempTour.insert(rit2.base(), subTour.vertexPath[i]);
                }
                // if incomplete sub tour return to start vertex to continue previous sub tour
                if ((subTour.vertexPath.back() != subTour.vertexPath.front()) && lastTour) {
                    tempTour.insert(rit.base(), subTour.vertexPath.front());
                }
                return;
            }
        }
    }
}

void Individual::ConvertChromosomeToCircles() {
    numNonOverlappingCircles = 0;
    circles.clear();

    map<int, vector<Edge*>> visitedVerticesWithUnvistedEdges;

    circles.push_back(Path(graph));
    circles.back().AddVertex(options->closedRouteVertex); // usually just zero
    AdjustEdgeTracking(circles.back().vertexPath.back(), -1, visitedVerticesWithUnvistedEdges);

    for (int i = 0; i < chromosome.size(); i++) {
        int nextNode = DetermineNextNodeForSubtour(circles.back(), chromosome[i], visitedVerticesWithUnvistedEdges);
        if (NodeProgressesForward(nextNode)) { // next node != -1
            // add node to sub tour
            AdjustEdgeTracking(nextNode, circles.back().vertexPath.back(), visitedVerticesWithUnvistedEdges);
            circles.back().AddVertex(nextNode);
            if (SubTourIsCircle(circles.back())) {
                numNonOverlappingCircles++;
                StartNewTour(visitedVerticesWithUnvistedEdges);
            }
        }
        else { // we hit a dead end
            StartNewTour(visitedVerticesWithUnvistedEdges);
            nextNode = DetermineNextNodeForSubtour(circles.back(), chromosome[i], visitedVerticesWithUnvistedEdges);
            AdjustEdgeTracking(nextNode, circles.back().vertexPath.back(), visitedVerticesWithUnvistedEdges);
            circles.back().AddVertex(nextNode);
        }
    }
}

void Individual::RecursivelyCombineSubTours(int subTourId, vector<bool> &toursTraveled) {
    toursTraveled[subTourId] = true;
    for (int i = 0; i < circles[subTourId].vertexPath.size(); ++i) {
        for (int j = 0; j < circles.size(); ++j) {
            if (!toursTraveled[j]) {
                if ((circles[subTourId].vertexPath[i] == circles[j].vertexPath.front())) {
                    RecursivelyCombineSubTours(j, toursTraveled);
                }
            }
        }
        tours[0].AddVertex(circles[subTourId].vertexPath[i]);
    }

    if (circles[subTourId].vertexPath.back() != circles[subTourId].vertexPath.front()) {
        tours[0].AddVertex(circles[subTourId].vertexPath.front());
    }
}



void Individual::Evaluate() {
    ConvertChromosomeToCircles();

    // reset robot tours
    for (int r = 0; r < options->numRobots; ++r) {
        tours[r] = Path(graph);
        tours[r].AddVertex(options->closedRouteVertex);
    }

    if (circles.size() < options->numRobots || circles.size() == options->numRobots) {
        // assign circles until we run out of robots
        for (int i = 0; i < circles.size(); i++) {
            for (int v = 0; v < circles[i].vertexPath.size(); v++) {
                tours[i].AddVertex(circles[i].vertexPath[v]);
            }
        }
    }
    else if (circles.size() > options->numRobots) {
        // combine circles to the same number of robots
        int numCirclesPerRobot = circles.size() / options->numRobots;
        for (int i = 0; i < circles.size(); i++) {
            int r = i % options->numRobots;
            for (int v = 0; v < circles[i].vertexPath.size(); v++) {
                tours[r].AddVertex(circles[i].vertexPath[v]);
            }
        }
    }

    // add home vertex to tours
    for (int r = 0; r < options->numRobots; ++r) {
        tours[r].AddVertex(options->closedRouteVertex);
    }

    fitness = tours[0].GetCost();
    totalTravelDistance = 0;
    for (int r = 0; r < options->numRobots; ++r) {
        if (tours[r].GetCost() > fitness) {
            fitness = tours[r].GetCost();
        }
        totalTravelDistance += tours[r].GetCost();
    }
}

string Individual::TourToString() {
    string route = "{";
    for (int r = 0; r < options->numRobots; r++) {
        route += "{";
        for (int i = 0; i < tours[r].vertexPath.size(); i++) {
            if (i == tours[r].vertexPath.size() - 1) {
                route += to_string(tours[r].vertexPath[i]);
            }
            else {
                route += to_string(tours[r].vertexPath[i]) + ", ";
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
    for (int i = 0; i < individual.chromosome.size(); i++) {
        os << individual.chromosome[i];
        if (i < individual.chromosome.size() - 1) {
            os << ",";
        }
    }
    os << "]" << endl;


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
        this->numNonOverlappingCircles = other.numNonOverlappingCircles;
    }
    return *this;
}
