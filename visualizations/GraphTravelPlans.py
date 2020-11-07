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
    routeDir = '../results/route-graph-gdb19-4R-pops30-50gens-fp-ox-swap.tsv'
    graphDir = '../benchmarks/mmkcpp/graph-gdb19.csv'

graph, numRobots, popSize, numGens, sType, xType, mType = get_params_from_string(routeDir)
outputDir = '../img/route-plot-' +\
            graph + '-' +\
            str(numRobots) + 'R-' +\
            'pops' + str(popSize) + '-' +\
            str(numGens) + 'gens-' +\
            sType + '-' + xType + '-' + mType +\
            '.png'

routes = load_route_file(routeDir)
adj = load_graph_file(graphDir)

vertices = adj.shape[0]

colors = ['orange', 'green', 'pink', 'purple', 'red', 'brown']

def plotGraph(ax, x, y, count):
    ax.plot(x, y, 'bo', color='black', label='POINT', markersize=2)
    for i in range(vertices):
        ax.annotate(i, (x[i], y[i]),
                    textcoords="offset points",
                    xytext=(0, 5),
                    ha='center',
                    color='black')
        for j in range(i + 1, vertices):
            if adj[i, j] != -1:
                if count == numRobots:
                    ax.plot((x[i], x[j]), (y[i], y[j]), color='blue', linewidth=1)
                else:
                    ax.plot((x[i], x[j]), (y[i], y[j]), 'b--', color='grey', linewidth=.25)


def plotTravelPlans(routes, adj):
    axis = np.linspace(0, 2*np.pi, vertices, endpoint=False)
    x, y = np.cos(axis), np.sin(axis) # convert the number of vertices to a circle plot

    fig, axs = plt.subplots(numRobots + 1, figsize=(5, 5 * numRobots))
    # TODO adjust the layout of the graphs so they form two columns
    totalCost = 0
    for i in range(vertices):
        for j in range(i + 1, vertices):
            if adj[i, j] != -1:
                totalCost += adj[i, j]

    travelCost = 0
    count = 0
    for ax in axs:
        if count == numRobots:
            ax.set_title(graph)
        else:
            ax.set_title('R' + str(count) + " travel path")
        # hide the axis
        ax.axes.xaxis.set_ticks([])
        ax.axes.yaxis.set_ticks([])
        # make plots square
        ax.set_aspect('equal', adjustable='box')
        # plot the graph
        plotGraph(ax, x, y, count)
        count += 1

    r = 0
    for route in routes:
        ax = axs[r]
        count = 0
        for v in range(len(route)):
            if v < len(route) - 1:
                travelCost += adj[route[v], route[v + 1]]
                ax.plot((x[route[v]], x[route[v + 1]]), (y[route[v]], y[route[v + 1]]), c=colors[r])
                ax.annotate(adj[route[v], route[v + 1]],  # this is the text
                             ((x[route[v]] + x[route[v + 1]]) / 2, (y[route[v]] + y[route[v + 1]]) / 2),  # this is the point to label
                             textcoords="offset points",  # how to position the text
                             xytext=(0, 5),  # distance from text to points (x,y)
                             ha='center',
                             c=colors[r])  # horizontal alignment can be left, right or center
            count += 1
        r += 1


    plt.show()
    fig.savefig(outputDir)
    print("Sum of Edge Weights: " + str(totalCost))
    print("Sum of All Robot Travel Costs: " + str(travelCost))
    return

plotTravelPlans(routes, adj)

