/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#include "GA.h"
#include <iostream>
#include <assert.h>

GA::GA(int argc, char *argv[]) : runCount(0), timeSeconds(0) {
	SetupOptions(argc, argv);

	// if the file already exists clear it (EXCEPT the results file)
    ClearFile(options.fitnessfile);
    ClearFile(options.travelfile);
    ClearFile(options.decodedfile);

    best = new Individual(&options, graph);
    best->totalTravelDistance = 0;
    best->fitness = 0;
}

GA::~GA() {
	// release memory
	delete graph;
	delete best;
}


void GA::SetupOptions(int argc, char *argv[]){
	options.randomSeed = time(NULL);
	options.popSize = 1000;
	options.maxgens = 1000;
	options.px = 0.99;
	options.pm = 0.4; // This is set by the graph

    options.selector = CHC;
    options.crossover = OX;
    options.mutator = Invert;

    options.numRobots = 1;
    options.numRuns = 1;

    options.graphfile = "../benchmarks/arc-routing/graph-gdb1.csv";

    // Read arguments if they are coming in [graphName], [runs], [robots].. etc
    for (int i = 0; i < argc; ++i) {
        switch(i) {
            case 1: options.graphfile = argv[i]; break;
            case 2: options.numRuns = std::strtol(argv[i], NULL, 10); break;
            case 3: options.numRobots = std::strtol(argv[i], NULL, 10); break;
            case 4: options.popSize = std::strtol(argv[i], NULL, 10); break;
            case 5: options.maxgens = std::strtol(argv[i], NULL, 10); break;
            default: break;
        }
    }

    SetGraph(options.graphfile);
}

void GA::SetGraph(string graphf) {
    options.graphfile = graphf;

    options.graphName = ExtractNameOfFile(graphf);
    graph = new Graph(&options);

    // output file name
    string GAParamsStr =
            to_string(options.numRobots) + "R-" +
            "pops" + to_string(options.popSize) + "-" +
            to_string(options.maxgens) + "gens-" +
            options.GetSelectorStr() + "-" +
            options.GetCrossoverStr() + "-" +
            options.GetMutatorStr();

    options.decodedfile = "../results/route-" + options.graphName + "-" + GAParamsStr + ".tsv";
    options.fitnessfile = "../results/fitness-" + options.graphName + "-" + GAParamsStr + ".tsv";
    options.travelfile = "../results/travel-" + options.graphName + "-" + GAParamsStr + ".tsv";
    options.resultsfile = "../results/results-" + GAParamsStr + ".tsv";
}

void GA::Init(){
    assert(("Population size is not even" ,options.popSize % 2 == 0));
    assert(("Number of runs should be at least 1" ,options.numRuns > 0));
    assert(("Number of robots should be at least 1" ,options.numRobots > 0));

    if (graph == nullptr) {
        graph = new Graph(&options);
    }

    options.randomSeed = time(NULL);
    parent = new Population(&options, graph);
	child  = new Population(&options, graph);
	parent->Init(); // evaluates, stats, and reports on initial population
	parent->Statistics();
	parent->Report(0);
}

void GA::Run(){
    clock_t clockin = clock();
    cout << runCount << ". Running GA on seed(" << options.randomSeed << "): [";
    for(unsigned long int i = 1; i < options.maxgens; i++){
        if (options.selector == SelectorType::CHC) {
            parent->CHCGeneration(child);
        } else {
            parent->Generation(child);
            child->EvaluateMembers();
        }
		if (child->bestIndividual->fitness > best->fitness) {
            *best = *child->bestIndividual;
		}
        child->Statistics();
		child->Report(i);

		Population *tmp = parent;
		parent = child;
		child = tmp;

		if ( i % 20 == 0) {
		    cout << ".";
		}
	}
    double duration = double(clock() - clockin) / 1000;
    cout << "] in " << duration << "s" << endl;
    runCount += 1;
    timeSeconds += duration;
}

void runCommand(string commandStr) {
    //cout << " - " << commandStr << endl;
    const char* command = commandStr.c_str();
    int ret_val = system(command);

    if(!(ret_val == 0 && errno == 0)) {
        cerr << "There was an error with the command: " << ret_val << endl;
    }
}

void GA::Report() {
    char printbuf[1024];
    float percentAboveLowerBound = (float(best->totalTravelDistance)/float(graph->sumEdges) - 1) * 100;

    sprintf(printbuf, "%s \t %i \t %i \t %f \t %f \n ", options.graphName.c_str(), graph->sumEdges, best->totalTravelDistance, percentAboveLowerBound, timeSeconds);
    WriteBufToFile(std::string(printbuf), options.resultsfile);

    best->WriteToFile(options.decodedfile);

    cout << "Finished " << runCount << " runs in " << timeSeconds << "s (" << (timeSeconds / runCount) << "s per run)" << endl << endl;

    cout << "Best result written to: " << options.decodedfile << endl;

    cout << "Creating visuals... ";
    runCommand("python3 ../visualizations/TravelPlot.py " + options.travelfile + " " + options.graphfile);
    runCommand("python3 ../visualizations/FitnessPlot.py " + options.fitnessfile + " " + options.graphfile);
    runCommand("python3 ../visualizations/GraphTravelPlans.py " + options.decodedfile + " " + options.graphfile);
    runCommand("python3 ../visualizations/GraphTravelOverlap.py " + options.decodedfile + " " + options.graphfile);
    cout << "Done!" << endl;

}

