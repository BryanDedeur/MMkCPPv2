# importing the required modules 
import matplotlib.pyplot as plt 
import numpy as np
import random as random

graphName = 'graph-gdb1'

graphfile = '../benchmarks/mmkcpp/' + graphName + '.csv'
infile = '../routes'
outfile = '../img/route-visualization-' + graphName + '.png'

adjacency_matrix = np.matrix([[1, 2], [3, 4]])

def load_graph_data(fname):
  f = open(fname, 'r')
  matrix = []
  for line in f:
    arr = []
    for token in line.split(','):
        arr.append(int(token))
    matrix.append(arr)
  f.close()
  adj = np.array(matrix)
  return adj

def plotRoutes(fname, route):
    f = open(fname, 'r')
    for line in f:
        arr = []
        count = 0
        start = ()
        for token in line.split(' '):
            if count != 0:
                arr.append(int(token))
            count += 1


    f.close()
    return 0

def plotAdjacencyMatrix(adj):
    n = adj.shape[0]
    axis = np.linspace(0, 2*np.pi, n, endpoint=False)
    x, y = np.cos(axis), np.sin(axis)

    f = open(infile, 'r')
    robots = []
    for line in f:
        arr = []
        count = 0
        for token in line.split(' '):
            if count != 0:
                arr.append(int(token))
            count += 1
        robots.append(arr)
    f.close()

    fig, axs = plt.subplots(len(robots) + 1, figsize=(5, 5 * len(robots)))

    count = 0
    for ax in axs:
        if count == len(robots):
            ax.set_title(graphName)
        else:
            ax.set_title('R' + str(count) + " travel path")
        # hide the axis
        ax.axes.xaxis.set_ticks([])
        ax.axes.yaxis.set_ticks([])
        # make plots square
        ax.set_aspect('equal', adjustable='box')
        # plot the graph
        ax.plot(x, y, 'bo', color='black', label='POINT', markersize=2)
        for i in range(n):
            ax.annotate(i, (x[i], y[i]),
                         textcoords="offset points",
                         xytext=(0, 5),
                         ha='center',
                         color='black')
            for j in range(i + 1, n):
                if adj[i, j] != -1:
                    if count == len(robots):
                        ax.plot((x[i], x[j]), (y[i], y[j]), color='blue', linewidth=1)
                    else:
                        ax.plot((x[i], x[j]), (y[i], y[j]), 'b--', color='grey', linewidth=.25)

        count += 1


    for r in range(len(robots)):
        ax = axs[r]
        color = (random.random(), random.random(), random.random())
        count = 0
        for k in range(len(robots[r])):
            arr = robots[int(r)]
            if count < len(robots[r]) - 1:
                ax.plot((x[arr[k]], x[arr[k + 1]]), (y[arr[k]], y[arr[k + 1]]), c=color)
                ax.annotate(adj[arr[k], arr[k + 1]],  # this is the text
                             ((x[arr[k]] + x[arr[k + 1]]) / 2, (y[arr[k]] + y[arr[k + 1]]) / 2),  # this is the point to label
                             textcoords="offset points",  # how to position the text
                             xytext=(0, 5),  # distance from text to points (x,y)
                             ha='center',
                             c=color)  # horizontal alignment can be left, right or center
            count += 1

    plt.show()
    fig.savefig(outfile)
    return

adjacency_matrix = load_graph_data(graphfile)
plotAdjacencyMatrix(adjacency_matrix)