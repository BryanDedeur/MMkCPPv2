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
    decoding = new Path[opts.numRobots];
}

Individual::~Individual() {
	// TODO Auto-generated destructor stub
	delete [] robotChromIndex;
	delete [] decoding;
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
    Decode();
    fitness = 0;
    // calculate the distribution of travel among all robots
    for (int r = 0; r < options->numRobots; r++) {
        fitness += decoding[r].cost;
    }

}

void Individual::Decode() {
    // make sure array is valid
    ostringstream out;
    out.str("");
    out << "Individual Decoding: " << endl;
    for (int r = 0; r < options->numRobots; r++) {
        decoding[r] = Path(0);
        out << "R" << r << ": " << endl;
        for (int i = 0; i < chromLength; i++) {
            // to account for cyclic encoding
            int firstEdgeIndex = (robotChromIndex[r] + i + 1) % chromLength; // [R0, 0, 1
            int secondEdgeIndex = (robotChromIndex[r] + i + 2) % chromLength;
            // no more edges to account for, this could happen with random encoding
            if (chromosome[firstEdgeIndex].isRobot) {
                break;
            }
            pair<int, int> *vertices = graph->GetVerticesOnEdge(chromosome[firstEdgeIndex].value);
            out << " - itr: " << i << " {edge" << chromosome[firstEdgeIndex].value << "(" << vertices->first << "," << vertices->second << ") ";
            if (!chromosome[secondEdgeIndex].isRobot) {
                vertices = graph->GetVerticesOnEdge(chromosome[secondEdgeIndex].value);
                out << "edge" << chromosome[secondEdgeIndex].value << "(" << vertices->first << "," << vertices->second << ")";
            }
            out << "}:\t";

            // if two edges exist
            if (!chromosome[secondEdgeIndex].isRobot) {
                pair<int, int> firstEdgeVertices = *graph->GetVerticesOnEdge(chromosome[firstEdgeIndex].value);
                pair<int, int> secondEdgeVertices = *graph->GetVerticesOnEdge(chromosome[secondEdgeIndex].value);
                Path *bestPath = graph->GetShortestPathBetweenEdges(chromosome[firstEdgeIndex].value, chromosome[secondEdgeIndex].value);
                // TODO make sure best path starts with vertices on first edge and ends with vertices on second edge
                out << "path(";
                for (int& itr : bestPath->path) {
                    if (itr == bestPath->path.back()) {
                        out << itr;
                    } else {
                        out << itr << "->";
                    }
                }
                out << ")robot";

                // Travel current edge
                // if first travel
                if (decoding[r].path.empty()) {
                    out << "(C1)";
                    // start travel from opposite vertex on from best path starting edge
                    int oppositeVertex = graph->GetOppositeVertexOnEdge(bestPath->path.front(), chromosome[firstEdgeIndex].value);
                    decoding[r].cost += graph->GetEdgeCost(oppositeVertex, bestPath->path.front());
                    decoding[r].path.push_back(oppositeVertex);
                    out << decoding[r].path.back() << "->";
                    decoding[r].path.push_back(bestPath->path.front());
                } else { // traveled somewhere before
                    out << "(C2)";
                    int oppositeVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
                    decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), oppositeVertex);
                    out << decoding[r].path.back() << "->";
                    decoding[r].path.push_back(oppositeVertex);
                    out << decoding[r].path.back() << "->";
                }

                // Travel to next edge (but dont travel the edge)
                // edges are connected
                if (bestPath->path.size() == 1) {
                    out << "(C3)";
                    // if not at the best connecting vertex, travel to that vertex
                    if (bestPath->path.back() != decoding[r].path.back()) {
                        int oppositeVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
                        decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), oppositeVertex);
                        decoding[r].path.push_back(oppositeVertex);
                        out << decoding[r].path.back() << "->";
                    } else { // at the best connecting edge
                        // do nothing
                    }
                } else { // edges are not connected
                    out << "(C4)";
                    // if already at bestpath start vertex
                    for (int& itr : bestPath->path) {
                        out << itr << "->";
                    }
                    if (decoding[r].path.back() == bestPath->path.front()) {
                        decoding[r].path.pop_back();
                    } else { // travel to best starting vertex
//                        decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), bestPath.path.front());
//                        decoding[r].path.push_back(bestPath.path.front());
//                        cout << decoding[r].path.back() << "->";
                    }
                    decoding[r] += *bestPath;
                }

            } else { // one edge exists

                // if already traveled somewhere
                if (!decoding[r].path.empty()) {
                    out << "robot(" << decoding[r].path.back() << "->";
                    // travel edge (should have arrived at the edge at this point)
                    int oppositeVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
                    decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), oppositeVertex);
                    decoding[r].path.push_back(oppositeVertex);
                } else { // randomly start somewhere and end on opposite vertex on edge
                    pair<int, int> *vertices = graph->GetVerticesOnEdge(chromosome[firstEdgeIndex].value);
                    if (rand() % 2 == 0) {
                        decoding[r].path.push_back(vertices->first);
                    } else {
                        decoding[r].path.push_back(vertices->second);
                    }
                    out << "robot(" << decoding[r].path.back() << "->";
                    int oppositeVertex = graph->GetOppositeVertexOnEdge(decoding[r].path.back(), chromosome[firstEdgeIndex].value);
                    decoding[r].cost += graph->GetEdgeCost(decoding[r].path.back(), oppositeVertex);
                    decoding[r].path.push_back(oppositeVertex);
                }
                out << decoding[r].path.back() << ")} ";

            }
            out << endl;
        }
    }
    //cout << out.str();

}
