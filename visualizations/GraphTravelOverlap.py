# importing the helpers
from Helpers import *

# importing the required modules
import matplotlib.pyplot as plt
import random
import numpy as np
import sys

args = sys.argv
if len(args) > 1:
    routeDir = args[1] #file path passed as command line arguement
    graphDir = args[2]
else:
    routeDir = '../results/route-graph-gdb3-4R-pops80-200gens-fp-ox-swap.tsv'
    graphDir = '../benchmarks/mmkcpp/graph-gdb3.csv'

graph, numRobots, popSize, numGens, sType, xType, mType = get_params_from_string(routeDir)
outputDir = '../img/overlap-plot-' +\
            graph + '-' +\
            str(numRobots) + 'R-' +\
            'pops' + str(popSize) + '-' +\
            str(numGens) + 'gens-' +\
            sType + '-' + xType + '-' + mType +\
            '.png'

routes = load_route_file(routeDir)
adj = load_graph_file(graphDir)

def createNewAdjMatrixWithNoEdgeCost(adj):
    adj_with_overlap = []
    for row in adj:
        new_row = []
        for item in row:
            if item == -1:
                new_row.append(item)
            else:
                new_row.append(0)
        adj_with_overlap.append(new_row)
    return adj_with_overlap

counterAdj = createNewAdjMatrixWithNoEdgeCost(adj)

def sumEdgeTravelCount(routes):
    count = 0
    for route in routes:
        for v in range(len(route)):
            if v < len(route) - 1:
                counterAdj[route[v]][route[v+1]] += 1
                counterAdj[route[v+1]][route[v]] += 1
                if counterAdj[route[v]][route[v+1]] > count:
                    count = counterAdj[route[v]][route[v+1]]
    return count

highestNum = sumEdgeTravelCount(routes)
print()
# show a graph with the overlap of travel show a graph with the color indicating the lowest cost edges

for i in range(len(counterAdj)):
    for j in range(len(counterAdj[i])):
        if counterAdj[i][j] != counterAdj[j][i]:
            print("SHIT")


def plotTravelPlans(routes, countAdj, max):
    axis = np.linspace(0, 2*np.pi, len(countAdj), endpoint=False)
    x, y = np.cos(axis), np.sin(axis) # convert the number of vertices to a circle plot
    # TODO fix plot to show sum of backwards travel on edge
    fig, ax = plt.subplots(figsize=(5, 5))
    #TODO fix this from not saving to file
    ax.set_title(graph + ' Robot Overlap from Best Result')
    ax.axes.xaxis.set_ticks([])
    ax.axes.yaxis.set_ticks([])
    # plt.aspect('equal', adjustable='box')

    for i in range(len(countAdj)):
        ax.annotate(i, (x[i], y[i]),
                    textcoords="offset points",
                    xytext=(0, 5),
                    ha='center',
                    color='black')
        for j in range(len(countAdj[i])):
            if countAdj[i][j] != -1 and countAdj[i][j] != 0:
                if countAdj[i][j] == 1:
                    line_up, = ax.plot((x[i], x[j]), (y[i], y[j]), linewidth= countAdj[i][j] * 2, c=(countAdj[i][j]/max, 1 - countAdj[i][j]/max, 1, 1), label='1 Pass')
                elif countAdj[i][j] == max:
                    line_down, = ax.plot((x[i], x[j]), (y[i], y[j]), linewidth=countAdj[i][j] * 2,
                        c=(countAdj[i][j] / max, 1 - countAdj[i][j] / max, 1, 1), label= str(max) + ' Pass')
                else:
                    ax.plot((x[i], x[j]), (y[i], y[j]), linewidth= countAdj[i][j] * 2, c=(countAdj[i][j]/max, 1 - countAdj[i][j]/max, 1, 1))

    ax.plot(x, y, 'bo', color='black', label='POINT', markersize=2)

    ax.legend([line_up, line_down], ['1 Pass', str(max) + ' Pass'])

    # plt.show()
    fig.savefig(outputDir)
    return

plotTravelPlans(routes, counterAdj, highestNum)