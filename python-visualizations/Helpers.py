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


def parse_dat_coordinate(line):
    v1 = None
    v2 = None
    cost = None

    tokens = line.split(' ')
    v1 = int(tokens[2].split(',')[0])
    v2 = int(tokens[3].split(')')[0])
    cost = int(tokens[6])

    return v1, v2, cost

def load_graph_dat_file(fname):
    f = open(fname, 'r')
    lines = []
    for line in f:
        lines.append(line)
    f.close()

    graphName = lines[0].split(' NOMBRE : ')[1].split('\n')[0]
    numVertices = int(lines[2].split(' VERTICES : ')[1])
    numEdges = int(lines[3].split(' ARISTAS_REQ : ')[1])

    matrix = []
    for x in range(numVertices):
        matrix.append([])
        for y in range(numVertices):
            matrix[x].append(0)

    sumEdges = 0
    for i in range(10, numEdges + 10):
        v1, v2, cost = parse_dat_coordinate(lines[i])
        sumEdges += cost
        matrix[v1 - 1][v2 - 1] = cost

    return matrix, graphName, sumEdges

def print_dat_graph_as_CPP_format(fname):
    f = open(fname, 'r')
    lines = []
    for line in f:
        lines.append(line)
    f.close()

    graphName = lines[0].split(' NOMBRE : ')[1].split('\n')[0]
    numVertices = int(lines[2].split(' VERTICES : ')[1])
    numEdges = int(lines[3].split(' ARISTAS_REQ : ')[1])

    print(graphName + " = [")

    sumEdges = 0
    outStr = ""
    for i in range(10, numEdges + 10):
        v1, v2, cost = parse_dat_coordinate(lines[i])
        outStr += "(" + str(v1) + ", " + str(v2) + ", " + str(cost) + ")"
        if i < numEdges + 10:
            outStr += ", "
        sumEdges += cost

    print(outStr)
    print("]")


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
