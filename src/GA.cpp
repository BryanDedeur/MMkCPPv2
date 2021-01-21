/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Jonathan Peters
 * @Date: 10/18/20
 */

#include "GA.h"
#include <iostream>
namespace fs = experimental::filesystem;


GA::GA(int argc, char *argv[]) : runCount(0), timeSeconds(0) {
	SetupOptions(argc, argv);

	// if the file already exists clear it (EXCEPT the results file)
    ClearFile(options.fitnessfile);
    ClearFile(options.travelfile);
    ClearFile(options.decodedfile);

    best = new Individual(&options, graph);
    best->totalTravelDistance = 0;
    best->fitness = 0;

    if (options.minimalOutput) {
        cout.clear();
        cout << "Starting GA on graph " << options.graphName << " with " << options.numRobots << " robots for " << options.numRuns << " runs of " << options.maxgens << " generations with population size " << options.popSize << endl;
    }
    else {
        cout << endl << "Starting GA on graph " << options.graphName << " with " << options.numRobots << " robots for " << options.numRuns << " runs of " << options.maxgens << " generations with population size " << options.popSize << ": " << endl;
    }

    if (options.minimalOutput)
        cout.setstate(ios_base::failbit);
}

GA::~GA() {
	// release memory
	delete graph;
	delete best;
}


void GA::SetupOptions(int argc, char *argv[]){
    for (int i = 0; i < argc; ++i) {
        switch(i) {
            case 1: options.graphfile = argv[i]; break;
            case 2: options.seedsFile = argv[i]; break;
            case 3: options.numRobots = strtol(argv[i], NULL, 10); break;
            case 4: options.popSize = strtol(argv[i], NULL, 10); break;
            case 5: options.maxgens = strtol(argv[i], NULL, 10); break;
            case 6: options.closedRouteVertex = strtol(argv[i], NULL, 10); break;
            case 7: options.minimalOutput = string(argv[i]) == "1"; break;
            case 8: options.makeVisuals = string(argv[i]) == "1"; break;
            default: break;
        }
    }

    vector<string> lines = SplitFileByLines(options.seedsFile);
    options.seeds = new long int[lines.size()];

    int i = 0;
    for (string seedStr : lines) {
        options.seeds[i] = stol(seedStr, NULL, 10);
        i++;
    }

    options.numRuns = lines.size();

    SetGraph(options.graphfile);

}

void GA::SetGraph(string graphf) {
    options.graphfile = graphf;

    options.graphName = ExtractNameOfFile(graphf);
    graph = new Graph(&options);
    cout << *graph << endl;

    options.chromLength = graph->numEdges + options.numRobots;

    // output file name
    string GAParamsStr =
            to_string(options.numRobots) + "R-" +
            "pops" + to_string(options.popSize) + "-" +
            to_string(options.maxgens) + "gens-" +
            options.GetSelectorStr() + "-" +
            options.GetCrossoverStr() + "-" +
            options.GetMutatorStr();

    options.decodedfile = options.outputDir + "route-" + options.graphName + "-" + GAParamsStr + ".tsv";
    options.fitnessfile = options.outputDir + options.graphName + "-" + GAParamsStr + ".tsv";
    options.travelfile = options.outputDir + options.graphName + "-" + GAParamsStr + ".tsv";
    options.resultsfile = options.outputDir + GAParamsStr + ".tsv";
}

void GA::Init(){
    AssertWithErrorMessage("Population size is not even", options.popSize % 2 == 0);
    AssertWithErrorMessage("Number of runs should be at least 1", options.numRuns > 0);
    AssertWithErrorMessage("Number of robots should be at least 1", options.numRobots > 0);
    AssertWithErrorMessage("Closed route start vertex is out of bounds", options.closedRouteVertex < options.chromLength);

    if (graph == nullptr) {
        graph = new Graph(&options);
    }

    options.randomSeed = options.seeds[runCount];
    srand(options.randomSeed);
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
        //cerr << "There was an error with the command: " << ret_val << endl;
    }
}

void GA::Report() {

    CPP chinesePostmanProblem = CPP();
    chinesePostmanProblem.Solve(*graph);
    
    std::stringstream ss;
    ss << options.graphName.c_str() << "\t"
        << graph->numEdges << "\t" 
        << graph->numVertices << "\t"
        << chinesePostmanProblem.numOddVertices << "\t"
        << chinesePostmanProblem.shortestPathDistance << "\t"
        << graph->sumEdges << "\t"
        << best->totalTravelDistance << "\t"
        << timeSeconds << "\t"
        << best->seed << endl;
    WriteToFile(ss, options.resultsfile);

    best->LogRoutes(options.decodedfile);

    cout << "Finished " << runCount << " runs in " << timeSeconds << "s (" << (timeSeconds / runCount) << "s per run)" << endl << endl;

    cout << "Best result written to: " << options.decodedfile << endl;

    if (options.makeVisuals) {
        cout << "Creating visuals... ";
        runCommand("python3 ../visualizations/TravelPlot.py " + options.travelfile + " " + options.graphfile);
        runCommand("python3 ../visualizations/FitnessPlot.py " + options.fitnessfile + " " + options.graphfile);
        runCommand("python3 ../visualizations/GraphTravelPlans.py " + options.decodedfile + " " + options.graphfile);
        runCommand("python3 ../visualizations/GraphTravelOverlap.py " + options.decodedfile + " " + options.graphfile);
    }

    cout << "Done!" << endl;
    if (options.minimalOutput) {
        cout.clear();
        cout << "Finished " << options.graphName << " with " << options.numRobots << " robots for " << options.numRuns << " runs of " << options.maxgens << " generations with population size " << options.popSize << ": in " << timeSeconds << "s (" << (timeSeconds / runCount) << "s per run)" << endl;
    }
}

