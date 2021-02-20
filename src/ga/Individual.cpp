/*
 * @Project: MMkCPP
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#include "Individual.h"
#include "../Utils.h"
#include <map>

Individual::Individual(Options* opts, Graph* gph) {
    fitness = -1;
    graph = gph;
    options = opts;

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

// generates a random chromosome containing all edges in the graph
void Individual::GenerateRandomChromosome() {
    // add all the edges in the graph to a random robot tour
    int robot = rand() % options->numRobots;
    for (int e = 0; e < graph->numEdges; e++) {
        AddEdgeToChromosome(e);
        robot = rand() % options->numRobots;
    }

	// swap every edge with a random edge
	for (int geneIndex = 0; geneIndex < chromosome.size(); geneIndex++) {
	    int otherIndex = rand() % chromosome.size();
        Swap(geneIndex, otherIndex);
	}
}

// adds a new edge to the chromosome
void Individual::AddEdgeToChromosome(int edgeId) {
    chromosome.push_back(edgeId);
    visitedEdgeCounts[edgeId]++;
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
    visitedEdgeCounts[edgeId]++;
}

// adds a new edge to the chromosome
void Individual::AddEdgeToChromosome(int edgeId, bool randomize) {
    AddEdgeToChromosome(edgeId, int(rand() % chromosome.size()));
}

// adds edges to chromosome so the tour is fully connected. Every edge leads to a connected edge (decoding in a way)
void Individual::ConvertChromosomeToTour() {
    // Make path using dijkstras
    Path tempPath = Path(graph);    
    for (int geneIndex = 0; geneIndex < chromosome.size() - 1; geneIndex++) {
        tempPath.AddEdge(graph->GetEdge(chromosome[geneIndex]));
    }

    totalTravelDistance = 0;
    // Shove path back into chromosome
    for (int i = 0; i < tempPath.edgePath.size(); i++) {
        if (i < chromosome.size()) {
            chromosome[i] = tempPath.edgePath[i].id;
        }
        else {
            chromosome.push_back(tempPath.edgePath[i].id);
        }
        totalTravelDistance += tempPath.edgePath[i].cost;
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


// swaps two chromosome indexes, preserves edges
void Individual::Swap(int& indexA, int& indexB) {
    int temp = chromosome[indexA];
    chromosome[indexA] = chromosome[indexB];
    chromosome[indexB] = temp;
}

void Individual::InjectMissingEdges() {
    for (int i = 0; i < visitedEdgeCounts.size(); i++) {
        if (visitedEdgeCounts[i] == 0) {
            AddEdgeToChromosome(i, true);
        }
    }
}

void Individual::Evaluate() {
    InjectMissingEdges();
    ConvertChromosomeToTour();
    DistributeTourBetweenRobots();

    //Decode();
    ////cout << *this << endl;
    //fitness = 0;
    //double largestPathCost = 0;
    //// calculate the distribution of travel among all robots
    //totalTravelDistance = 0;
    //for (int r = 0; r < options->numRobots; r++) {
    //    totalTravelDistance += decoding[r].cost;
    //    if (largestPathCost < decoding[r].cost) {
    //        largestPathCost = decoding[r].cost;
    //    }
    //}
    //fitness = 1/largestPathCost; // Larger numbers get smaller
}

void Individual::LogTours(string filename) {
    //ClearFile(filename);
    //std::stringstream ss;
    //for (int r = 0; r < options->numRobots; r++) {
    //    ss << "R" + to_string(r) + " ";
    //    int count = 0;
    //    for (int &itr : decoding[r].path) {
    //        if (count == 0) {
    //            ss << to_string(itr);
    //        } else {
    //            ss << " " + to_string(itr);
    //        }
    //        count++;
    //    }
    //    ss << endl;
    //}
    //WriteToFile(ss, filename);
}

//void Individual::UpdateRobotChromIndex() {
//    for (int i = 0; i < options->chromLength; i++) {
//        if (chromosome[i].isRobot) {
//            robotChromIndex[chromosome[i].value] = i;
//        }
//    }
//}

//bool Individual::CheckIfValidRoutes() {
//    map<int, bool> allEdgesAccountedFor = map<int, bool>();
//    for (int r = 0; r < options->numRobots; r++) {
//        int sumTravel = 0;
//        for (int i = 0; i < this->decoding[r].path.size() - 1; i++) {
//            if (this->decoding[r].path.size() <= 1) {
//                break;
//            }
//            // all vertices must be connected by an edge
//            if (!graph->IsValidEdge(this->decoding[r].path[i], this->decoding[r].path[i + 1])) {
//                cout << "invalid edge in route, no edge exists between these two vertices" << endl;
//                return false;
//            }
//            sumTravel += graph->GetEdgeCost(this->decoding[r].path[i], this->decoding[r].path[i + 1]);
//            int id = graph->GetEdgeId(this->decoding[r].path[i], this->decoding[r].path[i + 1]);
//            allEdgesAccountedFor.insert(std::pair<int, bool>(id, true));
//        }
//        if (sumTravel != this->decoding[r].cost) {
//            //cout << "route has the wrong cost but was fixed here" << endl;
//            this->decoding[r].cost = sumTravel;
//            //return false;
//        }
//    }
//
//    for (int i = 0; i < graph->numEdges; i++) {
//        if (allEdgesAccountedFor.find(i) == allEdgesAccountedFor.end()) {
//            cout << "edge " << i << " is missing" << endl;
//        }
//    }
//    return true;
//}

//void Individual::FindTravelCosts() {
//    for (int r = 0; r < options->numRobots; r++) {
//        int sumTravel = 0;
//        for (int i = 0; i < this->decoding[r].path.size() - 1; i++) {
//            if (this->decoding[r].path.size() <= 1) {
//                break;
//            }
//            sumTravel += graph->GetEdgeCost(this->decoding[r].path[i], this->decoding[r].path[i + 1]);
//        }
//        this->decoding[r].cost = sumTravel;
//    }
//}


void Individual::Decode() {
//    // make sure array is valid
//    for (int r = 0; r < options->numRobots; r++) {
//        decoding[r] = Path(0);
//        for (int i = 0; i < options->chromLength; i++) {
//            // to account for cyclic encoding
//            int firstEdgeIndex = (i + 1 + robotChromIndex[r]) % options->chromLength; // [R0, 0, 1
//            int secondEdgeIndex = (i + 2 + robotChromIndex[r]) % options->chromLength;
//            // no more edges to account for, this could happen with random encoding
//            if (chromosome[firstEdgeIndex].isRobot) {
//                break;
//            }
//            pair<int, int> *vertices = graph->GetVerticesOnEdge(chromosome[firstEdgeIndex].value);
//            // if two edges exist
//            if (!chromosome[secondEdgeIndex].isRobot) {
//                pair<int, int> firstEdgeVertices = *graph->GetVerticesOnEdge(chromosome[firstEdgeIndex].value);
//                pair<int, int> secondEdgeVertices = *graph->GetVerticesOnEdge(chromosome[secondEdgeIndex].value);
//                Path *bestPath = graph->GetShortestPathBetweenEdges(chromosome[firstEdgeIndex].value, chromosome[secondEdgeIndex].value);
//                // Travel current edge
//                // if first travel
//                if (decoding[r].path.empty()) {
//                    // start travel from opposite vertex on from best path starting edge
//                    int oppositeVertex = graph->GetOppositeVertexOnEdge(bestPath->path.front(), chromosome[firstEdgeIndex].value);
//                    decoding[r].cost += graph->GetEdgeCost(oppositeVertex, bestPath->path.front());
//                    decoding[r].path.push_back(oppositeVertex);
//                    decoding[r].path.push_back(bestPath->path.front());
//                } else { // traveled somewhere before
//                    int oppositeVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
//                    decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), oppositeVertex);
//                    decoding[r].path.push_back(oppositeVertex);
//                }
//
//                // Travel to next edge (but dont travel the edge)
//                // edges are connected
//                if (bestPath->path.size() == 1) {
//                    // if not at the best connecting vertex, travel to that vertex
//                    if (bestPath->path.back() != decoding[r].path.back()) {
//                        int oppositeVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
//                        decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), oppositeVertex);
//                        decoding[r].path.push_back(oppositeVertex);
//                    } else { // at the best connecting edge
//                        // do nothing
//                    }
//                } else { // edges are not connected
//                    // if already at bestpath start vertex
//                    if (decoding[r].path.back() == bestPath->path.front()) {
//                        decoding[r].path.pop_back();
//                    } else { // travel to best starting vertex
//                        //decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), bestPath.path.front());
//                        //decoding[r].path.push_back(bestPath.path.front());
////                        cout << decoding[r].path.back() << "->";
//                    }
//                    decoding[r] += *bestPath;
//                }
//
//            } else { // one edge exists
//
//                // if already traveled somewhere
//                if (!decoding[r].path.empty()) {
//                    // travel edge (should have arrived at the edge at this point)
//                    int oppositeVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
//                    decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), oppositeVertex);
//                    decoding[r].path.push_back(oppositeVertex);
//                } else { // randomly start somewhere and end on opposite vertex on edge
//                    pair<int, int> *vertices = graph->GetVerticesOnEdge(chromosome[firstEdgeIndex].value);
//                    if (rand() % 2 == 0) {
//                        decoding[r].path.push_back(vertices->first);
//                    } else {
//                        decoding[r].path.push_back(vertices->second);
//                    }
//                    int oppositeVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
//                    decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), oppositeVertex);
//                    decoding[r].path.push_back(oppositeVertex);
//                }
//            }
//        }
//    }
//
//    // complete routes to some vertex
//    if (options->closedRouteVertex != -1) {
//        for (int r = 0; r < options->numRobots; r++) {
//            if (!decoding[r].path.empty()) {
//                int vstart = options->closedRouteVertex;
//                int vstart2 = decoding[r].path.front();
//                int vend = decoding[r].path.back();
//
//                Path* startVertexToStartRoute = graph->GetShortestPathBetweenVertices(vstart, vstart2);
//                Path* endRouteToEndVertex = graph->GetShortestPathBetweenVertices(vend, vstart);
//                //cout << "Before: " << decoding[r] << endl;
//
//                Path temp = decoding[r];
//                decoding[r] = Path(0);
//
//                decoding[r] += *startVertexToStartRoute;
//                decoding[r] += temp;
//                decoding[r] += *endRouteToEndVertex;
//                //cout << "After: " << decoding[r] << endl;
//            }
//        }
//    }
//
//    //CheckIfValidRoutes(); // for debugging
//    FindTravelCosts();
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
    //if (this != &other) {
    //    for (int i = 0; i < options->chromLength; i++) {
    //        if (i < options->numRobots) {
    //            this->decoding[i] = other.decoding[i];
    //        }
    //        this->chromosome[i] = other.chromosome[i];
    //    }
    //    this->fitness = other.fitness;
    //    this->totalTravelDistance = other.totalTravelDistance;
    //    this->seed = other.seed;
    //}
    return *this;
}
