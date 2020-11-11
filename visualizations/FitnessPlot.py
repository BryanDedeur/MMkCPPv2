# importing the helpers
from Helpers import *

# importing the required modules
import matplotlib.pyplot as plt
import sys

args = sys.argv
if len(args) > 1:
    inputDir = args[1] #file path pass as command line arguement
else:
    inputDir = '../results/fitness-graph-gdb19-4R-pops30-50gens-fp-ox-swap.tsv'

graph, numRobots, popSize, numGens, sType, xType, mType = get_params_from_string(inputDir)
data = load_fitness_file(inputDir)

outputDir = '../img/fitness-plot-' +\
            graph + '-' +\
            str(numRobots) + 'R-' +\
            'pops' + str(popSize) + '-' +\
            str(numGens) + 'gens-' +\
            sType + '-' + xType + '-' + mType +\
            '.png'

def plotMatrix(matrix):
    # TODO add horizontal line and make label on best resutl
    fig = plt.figure()
    ax = fig.add_subplot()
    ax.set_ylabel('Robot travel distance')
    ax.set_xlabel('Generation')

    averages = []
    for i in range(numGens):
        baw = [] # best average worst
        for j in range(len(matrix[0])):
            baw.append(0)
        averages.append(baw)

    runs = 0
    for row in matrix:
        gen = int(row[0])
        for j in range(len(matrix[0])):
            if j != 0:
                averages[gen][j - 1] += row[j]
        if gen == 0:
            runs += 1

    for g in range(numGens):
        #ax.scatter(g, averages[g][0] / runs, color='red', s=2)
        ax.scatter(g, averages[g][1] / runs, color='blue', s=2)
        ax.scatter(g, averages[g][2] / runs, color='green', s=2)
        #ax.scatter(g, averages[g][3] / runs, color='green', s=2)

    ax.set_title('Average of Best and Average\nLongest Traveling Robot Per Generation (' +
                 str(runs) + ' Runs)')
    plt.show(block=True)
    fig.savefig(outputDir)
    return

plotMatrix(data)