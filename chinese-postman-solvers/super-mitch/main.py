#!/usr/bin/env python
"""
Solve the Chinese-Postman problem.

For a given graph, determine the minimum amount of backtracking
required to complete an Eularian circuit.

"""
import argparse
import sys

import data.data
from Helpers import *
from operator import itemgetter 

from chinesepostman import eularian, network


def setup_args():
    """ Setup argparse to take graph name argument. """
    #graphFile = sys.argv[1]
    #graphFile = "problem-instances/benchmarks/bbcm/10A.dat"
    graphFile = "problem-instances/bridge-generator2/B100.txt"

    return graphFile

def convert_adj_to_edge_format(adj_mat):
    edges = []
    sum = 0
    for i in range(len(adj_mat)):
        for j in range(i, len(adj_mat)):
            if 0 < adj_mat[i][j]:
                edgeTuple = (i + 1, j + 1, adj_mat[i][j])
                edges.append(edgeTuple)
                sum += adj_mat[i][j]
    print("Sum Edges:" + str(sum))
    return edges

def main():
    """ Make it so. """
    edges = None
    graph_name = setup_args() #"gdb8"#"instances/gdb1.dat" 
    print('Loading graph: {}'.format(graph_name))
    adj = load_graph_txt_file(graph_name) #load_graph_dat_file(graph_name) # if using dat file or csv file need to specify the different method
    edges = convert_adj_to_edge_format(adj[0])
    #edges = getattr(data.data, graph_name)


    original_graph = network.Graph(edges)

    print('<{}> edges'.format(len(original_graph)))
    if not original_graph.is_eularian:
        print('Converting to Eularian path...')
        graph, num_dead_ends = eularian.make_eularian(original_graph)
        print('Conversion complete')
        print('\tAdded {} edges'.format(len(graph) - len(original_graph) + num_dead_ends))
        print('\tTotal cost is {}'.format(graph.total_cost))
    else:
        graph = original_graph

    print('\tTotal cost is {}'.format(graph.total_cost))


    print('Attempting to solve Eularian Circuit...')
    route, attempts = eularian.eularian_path(graph, start=1)
    f = open("super-mitch-cpp-results.txt", "a")
    if not route:
        print('\tGave up after <{}> attempts.'.format(attempts))
        f.write(graph_name + "\t" + str(graph.total_cost) + "\tNA\t{}".format(attempts) + "\tNA\tNA\n")
    else:
        print('\tSolved in <{}> attempts'.format(attempts, route))
        print('Solution: (<{}> edges)'.format(len(route) - 1))
        print('\t{}'.format(route))
        sum = 0
        edgesTraveled = 0

        sum_edges = 0
        for edge in edges:
            sum_edges += edge[2]

        for i in range(len(route) - 1):
            for j in range(len(edges)):
                if (edges[j][0] == route[i] and edges[j][1] == route[i + 1]) or (edges[j][0] == route[i + 1] and edges[j][1] == route[i]):
                    sum += edges[j][2]
                    edgesTraveled += 1
        for i in range(len(route)):
            route[i] = route[i] - 1
        print('Solution Travel Cost: ' + str(sum))
        f.write(graph_name + "\t" +
                str(len(graph.nodes)) + "\t" + 
                str(len(edges)) + "\t" +
                str(sum_edges) + "\t" +
                str(sum) + "\t" +
                str(edgesTraveled)  + "\t" +
                "{}".format(route) + "\n")
    f.close()




if __name__ == '__main__':
    main()
