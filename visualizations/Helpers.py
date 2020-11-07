import numpy as np

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
    index = 0
    graph = ""
    numRobots = 0
    popSize = 0
    numGens = 0
    sType = ""
    xType = ""
    mType = ""
    for token in tokens[len(tokens) - 1].split('-'):
        if index == 2:
            graph = token
        elif index == 3:
            numRobots = int(token.split('R')[0])
        elif index == 4:
            popSize = int(token.split('pops')[1])
        elif index == 5:
            numGens = int(token.split('gens')[0])
        elif index == 6:
            sType = token
        elif index == 7:
            xType = token
        elif index == 8:
            mType = token

        index += 1
    return graph, numRobots, popSize, numGens, sType, xType, mType
