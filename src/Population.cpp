/*
 * @Project: MMkCPP v2
 * @Description: Genetic algorithm to evaluate efficient routes for a robotic bridge inspection team
 * @Collaborators: Sushil Louis, Bryan Dedeurwaerder, Johnathan Peters
 * @Date: 10/18/20
 */

#include "Population.h"
#include "Evaluate.h"
#include "Utils.h"

#include <iostream>

Population::Population(Options* opts, Graph *gph) {
    options = opts;
    avgFitness = minFitness = maxFitness = sumFitness = -1;
    avgTravelDist = minTravelDist = maxTravelDist = sumTravelDist = -1;
    AssertWithErrorMessage("The constant MAXPOP is too small for CHC, increase MAXPOP to at least " + to_string(options->popSize * 2), (options->popSize * 2) <= MAXPOP);

    for (int i = 0; i < options->popSize * 2; i++){
        members[i] = new Individual(options, gph);
        members[i]->Init();
    }
    bestIndividual = members[0];
    graph = gph;
}

Population::~Population() {
    for (int i = 0; i < options->popSize; i++){
        delete members[i];
    }
}

void Population::Init(){
	EvaluateMembers();
}

void Population::EvaluateMembers(){
	for (int i = 0; i < options->popSize; i++) {
		members[i]->Evaluate();
        StoreIfBest(members[i]);
	}
}

void Population::Statistics(){
	sumFitness = 0;
	minFitness = members[0]->fitness;
	maxFitness = members[0]->fitness;
    sumTravelDist = 0;
    minTravelDist = members[0]->totalTravelDistance;
    maxTravelDist = members[0]->totalTravelDistance;
	for (int i = 0; i < options->popSize; i++){
		sumFitness += members[i]->fitness;
		if (minFitness > members[i]->fitness)
			minFitness = members[i]->fitness;
		if (maxFitness < members[i]->fitness)
			maxFitness = members[i]->fitness;

        sumTravelDist += members[i]->totalTravelDistance;
        if (minTravelDist > members[i]->totalTravelDistance)
            minTravelDist = members[i]->totalTravelDistance;
        if (maxTravelDist < members[i]->totalTravelDistance)
            maxTravelDist = members[i]->totalTravelDistance;
	}
	avgFitness = sumFitness/options->popSize;
    avgTravelDist = sumTravelDist/options->popSize;
}

void Population::Report(unsigned long int gen){
	char printbuf[1024];
	sprintf(printbuf, "%4i \t %f \t %f \t %f \t %i \n ", (int)gen, 1/minFitness, 1/avgFitness, 1/maxFitness, options->randomSeed);
	WriteBufToFile(std::string(printbuf), options->fitnessfile);
    char printbuf2[1024];
    sprintf(printbuf2, "%4i \t %i \t %i \t %i \t %i  \n ", (int)gen, minTravelDist, avgTravelDist, maxTravelDist, options->randomSeed);
    WriteBufToFile(std::string(printbuf2), options->travelfile);
}

void Population::StoreIfBest(Individual* ind) {
    if (ind->fitness > bestIndividual->fitness) {
        bestIndividual = ind;
    }
}

void Population::Generation(Population *child) {
    int pi1, pi2, ci1, ci2;
    Individual *p1, *p2, *c1, *c2;

    for(int i = 0; i < options->popSize; i += 2) {
        pi1 = ProportionalSelector();
        pi2 = ProportionalSelector();

        p1 = members[pi1];
        p2 = members[pi2];

        ci1 = i;
        ci2 = i + 1;

        c1 = child->members[ci1];
        c2 = child->members[ci2];

        XoverAndMutate(p1, p2, c1, c2);
    }
}

bool CompareFitness(Individual *a, Individual *b) {
    return (a->fitness > b->fitness);
}

void Population::CHCGeneration(Population *child) {
    int pi1, pi2, ci1, ci2;
    Individual *p1, *p2, *c1, *c2;

    // Create the large population
    int doublePopSize = 2 * options->popSize;
    for (int i = 0; i < options->popSize; i += 2) {
        pi1 = ProportionalSelector();
        pi2 = ProportionalSelector();

        ci1 = options->popSize + i;
        ci2 = options->popSize + i + 1;

        p1 = members[pi1]; p2 = members[pi2];
        c1 = members[ci1]; c2 = members[ci2];

        XoverAndMutate(p1, p2, c1, c2);
    }

    // Halve the population
    for (int i = options->popSize; i < doublePopSize; i++) {
        members[i]->Evaluate();
        StoreIfBest(members[i]);
    }

    sort(members, members + doublePopSize, CompareFitness);

    for (int i = 0; i < options->popSize; i++) {
        child->members[i] = members[i];
    }
}

void Population::XoverAndMutate(Individual *p1, Individual *p2, Individual *c1, Individual *c2){
    // Crossover
    if(Flip(options->px)){ // if prob, then cross/exchange bits
        switch(options->crossover) {
            case CrossoverType::OX:
                OX(p1, p2, c1, c2); break;
            case CrossoverType::PMX: PMX(p1, p2, c1, c2); break;
            case CrossoverType::NoCross: break;
            default: break;
        }
    }

    // Mutate
    switch(options->mutator) {
        case MutationType::Invert:
            InvertMutate(c1);
            InvertMutate(c2); break;
        case MutationType::Swap:
            SwapMutate(c1);
            SwapMutate(c2); break;
        case MutationType::NoMut: break;
        default: break;
    }
}

int Population::ProportionalSelector(){
	int i = -1;
	float sum = 0;
	float limit = RandomFraction() * sumFitness;
	do {
		i = i + 1;
		sum += members[i]->fitness;
	} while (sum < limit && i < options->popSize-1 );

	return i;
}

void Population::PMX(Individual *p1, Individual *p2, Individual *c1, Individual *c2) {
    // TODO make sure PMX boundary is correct or is it fixed
    int lowerBound = rand() % (options->chromLength - 1) + 1;
    int upperBound = (rand() % (options->chromLength - lowerBound + 1)) + (lowerBound); // TODO double check this
    
    if (lowerBound >= upperBound || lowerBound < 0 || upperBound >= options->chromLength) {
       // cerr << "NO" << endl;
    }
    // TODO implement
}

bool Population::ChromContains(Gene* arr, Gene &gene) {
    for(int i = 0; i < options->chromLength; i++)
    {
        if(arr[i] == gene)
        {
            return true;
        }
    }
    return false;
}

void Population::OX(Individual *p1, Individual *p2, Individual *c1, Individual *c2) {
    //Get random index points
//    cout << "ORDER CROSSOVER" << endl;
//    cout << "p1: " << *p1;
//    cout << "p2: " << *p2;
    int t1 = IntInRange(0, options->chromLength);
    int t2 = IntInRange(0, options->chromLength);
    do
    {
        t2 = IntInRange(0, options->chromLength);
    }while(t2 == t1);

    if(t1 > t2)
    {
        int temp = t1;
        t1 = t2;
        t2 = temp;
    }
//

    //Directly copy genes between index points, track copied values with arrays
    int len = options->chromLength;
    Gene* arr1 = new Gene[options->chromLength];
    Gene* arr2 = new Gene[options->chromLength];
    for (int i = 0; i < options->chromLength; i++) {
        arr1[i].value = -1;
        arr2[i].value = -1;
    }

    for(int i = t1; i <= t2; i++)
    {
        c1->chromosome[i] = p1->chromosome[i];
        arr1[i] = p1->chromosome[i];
        c2->chromosome[i] = p2->chromosome[i];
        arr2[i] = p2->chromosome[i];
    }
    //Copy remaining values from opposite parent
    int i1 = 0;	//<--To access spaces outside of index points
    int i2 = 0;
    for(int i = 0; i < options->chromLength; i++)
    {
        //Skip spaces already copied to
        if(i1 == t1)
        {
            i1 = t2 + 1;
        }
        if(i2 == t1)
        {
            i2 = t2 + 1;
        }
        if(!ChromContains(arr1, p2->chromosome[i]))
        {
            c1->chromosome[i1] = p2->chromosome[i];
            i1++;
        }
        if(!ChromContains(arr2, p1->chromosome[i]))
        {
            c2->chromosome[i2] = p1->chromosome[i];
            i2++;
        }
    }
    delete arr1;
    delete arr2;

    c1->UpdateRobotChromIndex();
    c2->UpdateRobotChromIndex();

//    cout << "t1: " << t1 << endl;	//<--TEMP for debugging
//    cout << "t2: " << t2 << endl;	//<--TEMP for debugging
//    cout << "c1: " << *c1;
//    cout << "c2: " << *c2;
}

// --------------------------- Mutators ---------------------------

void Population::SwapMutate(Individual *ind) {
    for(int i = 0; i < options->chromLength; i++){
        if(Flip(options->pm)) {
            int pos2 = rand() % options->chromLength;
            ind->Swap(i, pos2);
        }
    }
}

void Population::InvertMutate(Individual *ind) {

    if(Flip(options->pm)) {
        // pick two locations
        int lowerBound = rand() % options->chromLength;
        int upperBound = rand() % options->chromLength;
        int l = min(upperBound, lowerBound), r = max(upperBound, lowerBound);
        int diff = r - l;

        // swap everything inbetween
        //cout << "before mutation: " << *ind << " left/right: " << l << "/" << r << endl;
        for (; l < r; l++, r--) {
            ind->Swap(l, r);
        }
        //cout << "after mutation: " << *ind << endl << endl;
    }

}


