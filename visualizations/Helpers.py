import numpy as np
from pathlib import Path

def load_fitness_file(fname):
  f = open(fname, 'r')
  matrix = []
  for line in f:
    arr = []
    count = 0
    for token in line.split('\t'):
        if token != ' ':
            arr.append(float(token))
        count += 1;
    if len(arr) != 0:
        matrix.append(arr)
  f.close()
  return matrix

def load_graph_file(fname):
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

def load_coordinate_file(fname):
    fname = fname.split('.csv')[0] + '.cord'
    f = Path(fname)
    if f.is_file():
        file = open(fname, 'r')
        matrix = []
        for line in file:
            arr = []
            for token in line.split(','):
                arr.append(int(token))
            matrix.append(arr)
        file.close()
        adj = np.array(matrix)
        return adj
    return []

def load_route_file(fname):
    f = open(fname, 'r')
    robots = []
    for line in f:
        arr = []
        count = 0
        for token in line.split(' '):
            if count != 0 and token != '\n':
                arr.append(int(token))
            count += 1
        robots.append(arr)
    f.close()
    return robots

def get_params_from_string(str):
    tokens = str.split('/')
    ga_info = tokens[len(tokens) - 1].split('.')[0].split('-')

    for i in range(len(ga_info) - 6):
        if i == len(ga_info) - 7:
            graph = ga_info[i]
        else:
            graph = ga_info[i] + '-'

    #graph = ga_info[len(ga_info) - 1]
    numRobots = int(ga_info[len(ga_info) - 6].split('R')[0])
    popSize = int(ga_info[len(ga_info) - 5].split('pops')[1])
    numGens = int(ga_info[len(ga_info) - 4].split('gens')[0])
    sType = ga_info[len(ga_info) - 3]
    xType = ga_info[len(ga_info) - 2]
    mType = ga_info[len(ga_info) - 1]

    return graph, numRobots, popSize, numGens, sType, xType, mType
