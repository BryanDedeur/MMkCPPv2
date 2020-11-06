# importing the required modules
import matplotlib.pyplot as plt
import numpy as np

def load_graph_data(fname, inDir):
  f = open(fname, 'r')
  matrix = []
  for line in f:
    arr = []
    count = 0
    for token in line.split('\t'):
        if (count == 0 or count == 2):
            if token != ' ':
                arr.append(float(token))
        count += 1;
    matrix.append(arr)
  f.close()
  data = np.array(matrix)
  return data

def plotMatrix(matrix, outDir):
    averages = []
    count = 0
    for coordpairA in matrix:
        if len(coordpairA) > 0:
            aveOfGen = []
            aveOfGen.append(coordpairA[0])
            sum = 0
            count = 0
            for coordpairB in matrix:
                if len(coordpairB) > 0:
                    if coordpairA[0] == coordpairB[0]:
                        sum += coordpairB[1]
                        count += 1
            aveOfGen.append(sum / count)
            averages.append(aveOfGen)
    averages = np.array(averages)

    fig = plt.figure()
    ax = fig.add_subplot()
    for coordpair in averages:
        ax.scatter(coordpair[0],coordpair[-1], color='blue')


    ax.set_title('Average Total Travel Distance Per Generation (' + str(count) + ' Trials)')
    ax.set_ylabel('Ave sum of robot travel distance in population')
    ax.set_xlabel('Generation')
    fig.show()

    fig.savefig(outputDir + 'ave-fitness-' + str(count) + '-trials-canonical-ga.png')
    return

inputDir = '../ga-results-graph-gdb1'
outputDir = '../img/'

data = load_graph_data(inputDir, "outfile")
plotMatrix(data, outputDir)
