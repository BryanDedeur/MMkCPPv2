# importing the required modules 
import matplotlib.pyplot as plt 
import numpy as np

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

def plotAdjacencyMatrix(adj):
    n = adj.shape[0]
    axis = np.linspace(0, 2*np.pi, n, endpoint=False)
    x, y = np.cos(axis), np.sin(axis)
    # hide the axis
    ax = plt.gca()
    ax.axes.xaxis.set_ticks([])
    ax.axes.yaxis.set_ticks([])
    # plot the graph
    plt.plot(x, y, 'bo', color='red', label='POINT')
    for i in range(n):
        plt.annotate(i,  # this is the text
                     (x[i], y[i]),  # this is the point to label
                     textcoords="offset points",  # how to position the text
                     xytext=(0, 10),  # distance from text to points (x,y)
                     ha='center',
                     color='red')  # horizontal alignment can be left, right or center
        for j in range(i + 1, n):
            if adj[i, j] != -1:
                plt.plot((x[i], x[j]), (y[i], y[j]), color='blue')
                plt.annotate(adj[i, j],  # this is the text
                             ((x[i] + x[j]) / 2, (y[i] + y[j]) / 2),  # this is the point to label
                             textcoords="offset points",  # how to position the text
                             xytext=(0, 5),  # distance from text to points (x,y)
                             ha='center',
                             color='blue')  # horizontal alignment can be left, right or center
    plt.show()
    return

adjacency_matrix = load_graph_data("../benchmarks/mmkcpp/graph-gdb19.csv")
plotAdjacencyMatrix(adjacency_matrix)