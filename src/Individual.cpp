/*
 * @Project: MMkCPP
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#include "Individual.h"
#include "Utils.h"

Individual::Individual(Options &opts, Graph *gph) : chromLength(gph->numEdges + opts.numRobots) {
    fitness = -1;
    graph = gph;
    options = &opts;
    robotChromIndex = new int[opts.numRobots];
}

Individual::~Individual() {
	// TODO Auto-generated destructor stub
}

void Individual::Init(){
    // Initialize the chromosome with every possible edge and every possible robot
	for(int i = 0; i < chromLength; i++) {
        chromosome[i].value = i;
        if (i >= graph->numEdges) {
            chromosome[i].value = i - graph->numEdges;
            chromosome[i].isRobot = true;
        }
	}
	// Randomize chromosome by swapping every element with another element
	for (int i = 0; i < chromLength; i++) {
	    int otherIndex = rand() % chromLength;
        Swap(i, otherIndex);
	}
}

ostream& operator<<(ostream& os, const Individual& individual)
{
    os << "chromosome: [";
    for (int i = 0; i < individual.chromLength; i++) {
        os << individual.chromosome[i];
        if (i < individual.chromLength - 1) {
            os << ",";
        }
    }
    os << "]" << endl;
    os << "decoding: " << endl;
    for (int r = 0; r < individual.options->numRobots; r++) {
        os << "R" << r << " path(cost: "<< individual.decoding[r].cost << "): ";
        for (int &itr : individual.decoding[r].path) {
            os << itr << " ";
        }
        os << endl;
    }
    return os;
}

void Individual::Swap(int &indexA, int &indexB) {
    Gene temp = chromosome[indexA];
    chromosome[indexA] = chromosome[indexB];
    chromosome[indexB] = temp;

    // adjust the robot start index if robot
    if (chromosome[indexA].isRobot) {
        robotChromIndex[chromosome[indexA].value] = indexA;
    }
    if (chromosome[indexB].isRobot) {
        robotChromIndex[chromosome[indexB].value] = indexB;
    }
}

void Individual::Mutate(double pm){
	for(int i = 0; i < chromLength; i++){
		if(Flip(pm)) {

		}
	}
}

void Individual::Evaluate() {
    // calculate the total travel distance
    for (int i = 0; i < chromLength; i++) {
        //sum += individual->calculateFitness();
    }

    // calculate the distribution of travel among all robots

}

void Individual::Decode() {
    // make sure array is valid
    decoding = new Path[options->numRobots];
    for (int r = 0; r < options->numRobots; r++) {
        decoding[r] = Path(vector<int>(), 0);
    }
    for (int r = 0; r < options->numRobots; r++) {
        for (int i = 0; i < chromLength; i++) {
            // to account for cyclic encoding
            int firstEdgeIndex = (robotChromIndex[r] + i + 1) % chromLength; // [R0, 0, 1
            int secondEdgeIndex = (robotChromIndex[r] + i + 2) % chromLength;
            // no more edges to account for, this could happen with random encoding
            if (chromosome[firstEdgeIndex].isRobot) {
                break;
            }

            // if two edges exist
            if (!chromosome[secondEdgeIndex].isRobot) {
                Path bestPath = graph->GetShortestPathBetweenEdges(chromosome[firstEdgeIndex].value, chromosome[secondEdgeIndex].value);
                // TODO make sure best path starts with vertices on first edge and ends with vertices on second edge
                // Travel current edge
                // if first travel
                if (decoding[r].path.empty()) {
                    // start travel from opposite vertex on from best path starting edge
                    int oppositeVertex = graph->GetOppositeVertexOnEdge(bestPath.path.front(), chromosome[firstEdgeIndex].value);
                    decoding[r].cost += graph->GetEdgeCost(oppositeVertex, bestPath.path.front());
                    decoding[r].path.push_back(oppositeVertex);
                } else { // traveled somewhere before
                    int oppositeVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
                    decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), oppositeVertex);
                    decoding[r].path.push_back(oppositeVertex);
                }

                // Travel to next edge (but dont travel the edge)
                // edges are connected
                if (bestPath.path.size() == 1) {
                    // if we are not at the connecting vertex go there
                    if (bestPath.path.back() != decoding[r].path.back()) {
                        decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), bestPath.path.back());
                        decoding[r].path.push_back(bestPath.path.back());
                    } // else do nothing
                } else { // edges are not connected
                    // if already at bestpath start vertex
                    if (decoding[r].path.back() == bestPath.path.front()) {
                        bestPath.path.erase(bestPath.path.begin());
                    } else { // travel to best starting vertex
                        decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), bestPath.path.front());
                        decoding[r].path.push_back(bestPath.path.front());
                    }
                    decoding[r] += bestPath;
                }
            } else { // one edge exists
                // if already traveled somewhere
                if (!decoding[r].path.empty()) {
                    // travel edge (should have arrived at the edge at this point)
                    int oppositeVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
                    decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), oppositeVertex);
                    decoding[r].path.push_back(oppositeVertex);
                } else { // randomly start somewhere and end on opposite vertex on edge
                    pair<int, int>* vertices = graph->GetVerticesOnEdge(chromosome[firstEdgeIndex].value);
                    if (rand() % 2 == 0) {
                        decoding[r].path.push_back(vertices->first);
                    } else {
                        decoding[r].path.push_back(vertices->second);
                    }
                    int oppositeVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
                    decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), oppositeVertex);
                }
            }

//
//            // find the best path in-between edges
//            Path shortestPath = Path(vector<int>(), 0);
//            if (chromosome[secondEdgeIndex].isRobot) {
//                // only one remaining edge to account for
//                if (!decoding[r].path.empty()) {
//                    shortestPath = graph->GetShortestPathBetweenVertexAndEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
//                    decoding[r] += shortestPath;
//
//                    int otherVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
//                    decoding[r].path.push_back(otherVertex); // this is really the start of the path
//                    decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), shortestPath.path.front());
//                } else if (i == 0) {
//                    pair<int, int>* vertices = graph->GetVerticesOnEdge(chromosome[firstEdgeIndex].value);
//                    if (rand() % 2 == 0) {
//                        decoding[r].path.push_back(vertices->first);
//                        decoding[r].path.push_back(vertices->second);
//                        decoding[r].cost += graph->GetEdgeCost(vertices->first, vertices->second);
//
//                    } else {
//                        decoding[r].path.push_back(vertices->second);
//                        decoding[r].path.push_back(vertices->first);
//                        decoding[r].cost += graph->GetEdgeCost(vertices->second, vertices->first);
//                    }
//                }
//            } else {
//                // two edges to account for
//                shortestPath = graph->GetShortestPathBetweenEdges(chromosome[firstEdgeIndex].value, chromosome[secondEdgeIndex].value);
//                if (i == 0) {
//                    int otherVertex = graph->GetOppositeVertexOnEdge(shortestPath.path.back(), chromosome[firstEdgeIndex].value);
//                    decoding[r].path.push_back(otherVertex); // this is really the start of the path
//                    decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), shortestPath.path.back());
//                }
//
//                decoding[r] += shortestPath;
//
//                // dont need this because the final edge will be accounted for on the next itteration
////                // let the robot travel the second edge
////                int otherVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[secondEdgeIndex].value);
////                //cout << "Vertex1: " << decoding[r].path.back() << " Opposite Vertex2: " << otherVertex << endl;
////                decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), otherVertex);
////                decoding[r].path.push_back(otherVertex);
//            }
//
//
//            // append the shortest path to the existing path
//
//            cout << chromosome[firstEdgeIndex].value << " " << chromosome[secondEdgeIndex].value << endl;


        }
    }
}
