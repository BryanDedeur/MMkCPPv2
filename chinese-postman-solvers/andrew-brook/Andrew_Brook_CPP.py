import itertools
import copy
import networkx as nx
import pandas as pd
import matplotlib.pyplot as plt

import os

from helpers import *

import sys


edgeTuplesList = []

# ------------------------------------------ CREATE GRAPH ----------------------------------------------- #

def setup_args():
    graphFile = sys.argv[1]
    #graphFile = "large-instances/graph-raw.csv"
    return graphFile

def convert_adj_to_edge_format(adj_mat, graph):
    for i in range(len(adj_mat[0])):
        for j in range(i, len(adj_mat[0])):
            if 0 < adj_mat[i][j]:
                graph.add_edge(i, j, weight=float(adj_mat[i][j]), trail='original')
    return graph

graph = nx.Graph()
graph_name = setup_args()
adj = load_graph_dat_file(graph_name) #load_graph_dat_file(graph_name) # if using dat file or csv file need to specify the different method
graph = convert_adj_to_edge_format(adj[0], graph)

# ------------------------------------------ INSPECT GRAPH ----------------------------------------------- #

edges = list(graph.edges(data=True))

# ------------------------------------------ CPP ALGORITHM ----------------------------------------------- #

# ----------------------- CPP Step 1: Find Nodes of Odd Degree

def find_nodes_of_odd_degree(graph):
    nodes_odd_degree = []
    for v, d in graph.degree():
        if d % 2 == 1:
            nodes_odd_degree.append(v)
    return nodes_odd_degree

nodes_odd_degree = find_nodes_of_odd_degree(graph)

print('Number of nodes of odd degree: {}'.format(len(nodes_odd_degree)))
print('Number of total nodes: {}'.format(len(graph.nodes())))

# ----------------------- CPP Step 2: Find Min Distance Pairs

# Compute all pairs of odd nodes. in a list of tuples
odd_node_pairs = list(itertools.combinations(nodes_odd_degree, 2))

def get_shortest_paths_distances(graph, pairs, edge_weight_name):
    """Compute shortest distance between each pair of nodes in a graph.  Return a dictionary keyed on node pairs (tuples)."""
    distances = {}
    for pair in pairs:
        distances[pair] = nx.dijkstra_path_length(graph, pair[0], pair[1], weight=edge_weight_name)
    return distances

odd_node_pairs_shortest_paths = get_shortest_paths_distances(graph, odd_node_pairs, 'weight')

print('Number of pairs: {}'.format(len(odd_node_pairs)))


def create_complete_graph(pair_weights, flip_weights=True):
    """
    Create a completely connected graph using a list of vertex pairs and the shortest path distances between them
    Parameters: 
        pair_weights: list[tuple] from the output of get_shortest_paths_distances
        flip_weights: Boolean. Should we negate the edge attribute in pair_weights?
    """
    g = nx.Graph()
    for k, v in pair_weights.items():
        wt_i = - v if flip_weights else v
        g.add_edge(k[0], k[1], distance=v, weight=wt_i)  
    return g

graph_odd_complete = create_complete_graph(odd_node_pairs_shortest_paths, flip_weights=True)

# Counts
print('Number of nodes: {}'.format(len(graph_odd_complete.nodes())))
print('Number of edges: {}'.format(len(graph_odd_complete.edges())))

# Compute min weight matching.
# Note: max_weight_matching uses the 'weight' attribute by default as the attribute to maximize.
odd_matching_dupes = nx.algorithms.max_weight_matching(graph_odd_complete, True)

print('Number of edges in matching: {}'.format(len(odd_matching_dupes)))

# Convert matching to list of deduped tuples
odd_matching = list(pd.unique([tuple(sorted([k, v])) for k, v in odd_matching_dupes]))


# Counts
print('Number of edges in matching (deduped): {}'.format(len(odd_matching)))

def add_augmenting_path_to_graph(graph, min_weight_pairs):
    """
    Add the min weight matching edges to the original graph
    Parameters:
        graph: NetworkX graph (original graph from trailmap)
        min_weight_pairs: list[tuples] of node pairs from min weight matching
    Returns:
        augmented NetworkX graph
    """
    
    # We need to make the augmented graph a MultiGraph so we can add parallel edges
    graph_aug = nx.MultiGraph(graph.copy())
    for pair in min_weight_pairs:
        graph_aug.add_edge(pair[0], 
                           pair[1], 
                           **{'distance': nx.dijkstra_path_length(graph, pair[0], pair[1]), 'trail': 'augmented'}
                           # attr_dict={'distance': nx.dijkstra_path_length(graph, pair[0], pair[1]),
                           #            'trail': 'augmented'}  # deprecated after 1.11
                          )
    return graph_aug

# Create augmented graph: add the min weight matching edges to g
g_aug = add_augmenting_path_to_graph(graph, odd_matching)

# Counts
print('Number of edges in original graph: {}'.format(len(graph.edges())))
print('Number of edges in augmented graph: {}'.format(len(g_aug.edges())))

# ----------------------- CPP Step 3: Compute Eulerian Circuit

def create_eulerian_circuit(graph_augmented, graph_original, starting_node=None):
    """Create the eulerian path using only edges from the original graph."""
    euler_circuit = []
    naive_circuit = list(nx.eulerian_circuit(graph_augmented, source=starting_node))
    
    for edge in naive_circuit:
        edge_data = graph_augmented.get_edge_data(edge[0], edge[1])    
        
        if edge_data[0]['trail'] != 'augmented':
            # If `edge` exists in original graph, grab the edge attributes and add to eulerian circuit.
            edge_att = graph_original[edge[0]][edge[1]]
            euler_circuit.append((edge[0], edge[1], edge_att)) 
        else: 
            aug_path = nx.shortest_path(graph_original, edge[0], edge[1], weight='distance')
            aug_path_pairs = list(zip(aug_path[:-1], aug_path[1:]))
            
            print('Filling in edges for augmented edge: {}'.format(edge))
            # print('Augmenting path: {}'.format(' => '.join(aug_path)))
            print('Augmenting path pairs: {}\n'.format(aug_path_pairs))
            
            # If `edge` does not exist in original graph, find the shortest path between its nodes and 
            #  add the edge attributes for each link in the shortest path.
            for edge_aug in aug_path_pairs:
                edge_aug_att = graph_original[edge_aug[0]][edge_aug[1]]
                euler_circuit.append((edge_aug[0], edge_aug[1], edge_aug_att))
                                      
    return euler_circuit

euler_circuit = create_eulerian_circuit(g_aug, graph, 0)

# Preview first 20 directions of CPP solution
for i, edge in enumerate(euler_circuit):
    print(i, edge)

# ------------------------------------------ ROUTE PREP ----------------------------------------------- #

def CloseRouteBetweenVertices(route, start, end, graph):
    last = 0
    closedRoute = nx.dijkstra_path(graph, start, end)
    for i in range(len(closedRoute)):
        if i != 0:
            route.append(closedRoute[i])
            last = closedRoute[i]
        else:
            last = closedRoute[i]
    return route

sum = float(0)
vertexRoute = []
for item in euler_circuit:
    vertexRoute.append(item[0])
    sum += float(item[2]['weight'])
vertexRoute.append(euler_circuit[len(euler_circuit) - 1][1])

def CloseRoute(vertexRoute, graph):
    start = vertexRoute[len(vertexRoute) - 1]
    closedRoute = nx.dijkstra_path(graph, start, 1)
    for i in range(len(closedRoute)):
        if i != 0:
            vertexRoute.append(closedRoute[i])
            last = closedRoute[i]
        else:
            last = closedRoute[i]
    return vertexRoute

#vertexRoute = CloseRoute(vertexRoute, graph)

def CalculateTourCost(route, graph):
    sum = 0
    last = 0
    for i in range(len(route)):
        if i != 0:
            sum += graph[last][route[i]]["weight"]
            last = route[i]
        else:
            last = route[i]
    return sum

#sum = CalculateTourCost(vertexRoute, graph)

def MakeZeroBasedIndexing(route):
    for i in range(len(route)):
        route[i] -= 1
    return route

#vertexRoute = MakeZeroBasedIndexing(vertexRoute)

print()
print("Tour Cost: {}".format(sum))
print("Graph name: {}".format(graph_name))

num_edges_traveled = len(euler_circuit)

sum_edges = 0
for edge in edges:
    sum_edges += edge[2]['weight']

routeFormatted = ''
for i in range(len(vertexRoute)):
    if i == len(vertexRoute) - 1:
        routeFormatted += str(vertexRoute[i])
    else:
        routeFormatted += str(vertexRoute[i]) + ','

with open('andrew-brook-cpp-solutions.txt', 'a') as fo:
    fo.write(graph_name + "\t" 
             + str(len(graph.nodes())) + "\t" 
             + str(len(graph.edges())) + "\t" 
             + str(sum_edges) + "\t" 
             + str(sum) + "\t"  # tour cost
             + str(num_edges_traveled) + "\t" 
             + str(routeFormatted) + "\n")
