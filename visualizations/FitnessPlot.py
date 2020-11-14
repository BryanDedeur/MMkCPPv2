# importing the helpers
from Helpers import *

# importing the required modules
import matplotlib.pyplot as plt
import sys

args = sys.argv
if len(args) > 1:
    inputDir = args[1] #file path pass as command line arguement
    graphDir = args[2]
else:
    inputDir = '../results/fitness-graph-gdb1-1R-pops20-80gens-chc-ox-swap.tsv'
    graphDir = '../benchmarks/arc-routing/graph-gdb1.csv'


graph, numRobots, popSize, numGens, sType, xType, mType = get_params_from_string(inputDir)
data = load_fitness_file(inputDir)

outputDir = '../img/fitness-plot-' +\
            graph + '-' +\
            str(numRobots) + 'R-' +\
            'pops' + str(popSize) + '-' +\
            str(numGens) + 'gens-' +\
            sType + '-' + xType + '-' + mType +\
            '.png'

adj = load_graph_file(graphDir)
vertices = adj.shape[0]

# def getLowerBound(graph):
#     totalCost = 0
#     for i in range(vertices):
#         for j in range(i + 1, vertices):
#             if adj[i, j] != -1:
#                 totalCost += adj[i, j]
#     return totalCost

def plotMatrix(matrix):
    # TODO add horizontal line and make label on best resutl
    fig = plt.figure()
    ax = fig.add_subplot()
    ax.set_ylabel('Robot travel distance')
    ax.set_xlabel('Generation')

    # ax.axhline(y=getLowerBound(adj), color='r', linestyle='-')

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
        ax.scatter(g, averages[g][1] / runs, color='green', s=2)
        ax.scatter(g, averages[g][2] / runs, color='blue', s=2)
        #ax.scatter(g, averages[g][3] / runs, color='green', s=2)

    ax.set_title('Average Longest Traveling Robot Per Generation with ' +
                 str(runs) + ' Runs')
    # plt.show(block=True)
    fig.savefig(outputDir)
    return

plotMatrix(data)