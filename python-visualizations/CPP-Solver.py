# importing the helpers
from Helpers import *
import random

filePath = '../problem-instances/benchmarks/gdb/gdb'

def get_odd(graph):
    degrees = [0 for i in range(len(graph))]
    for i in range(len(graph)):
        for j in range(len(graph)):
                if(graph[i][j]!=0):
                    degrees[i]+=1
                
    #print(degrees)
    odds = [i for i in range(len(degrees)) if degrees[i]%2!=0]
    #print('odds are:',odds)
    return odds

for i in range(23):
    tempFilePath = filePath + str(i + 1) + '.dat'
    graph, graphName, sumEdges = load_graph_dat_file(tempFilePath)
    odds = get_odd(graph)
    print()
    print("# Number of odd vertices: ", len(odds))
    print_dat_graph_as_CPP_format(tempFilePath)

print()


def sum_edges(graph):
    w_sum = 0
    l = len(graph)
    for i in range(l):
        for j in range(i,l):
            w_sum += graph[i][j]
    return w_sum
            

def dijktra(graph, source, dest):
    shortest = [0 for i in range(len(graph))]
    selected = [source]
    l = len(graph)
    #Base case from source
    inf = 10000000
    min_sel = inf
    for i in range(l):
        if(i==source):
            shortest[source] = 0 #graph[source][source]
        else:
            if(graph[source][i]==0):
                shortest[i] = inf
            else:
                shortest[i] = graph[source][i]
                if(shortest[i] < min_sel):
                    min_sel = shortest[i]
                    ind = i
                
    if(source==dest):
        return 0
    # Dijktra's in Play
    selected.append(ind) 
    while(ind!=dest):
        #print('ind',ind)
        for i in range(l):
            if i not in selected:
                if(graph[ind][i]!=0):
                    #Check if distance needs to be updated
                    if((graph[ind][i] + min_sel) < shortest[i]):
                        shortest[i] = graph[ind][i] + min_sel
        temp_min = 1000000
        #print('shortest:',shortest)
        #print('selected:',selected)
        
        for j in range(l):
            if j not in selected:
                if(shortest[j] < temp_min):
                    temp_min = shortest[j]
                    ind = j
        min_sel = temp_min
        selected.append(ind)
    
    return shortest[dest]
                            
#Finding odd degree vertices in graph



#Function to generate unique pairs
def gen_pairs(odds):
    pairs = []
    for i in range(len(odds)-1):
        pairs.append([])
        for j in range(i+1,len(odds)):
            pairs[i].append([odds[i],odds[j]])
        
    #print('pairs are:',pairs)
    #print('\n')
    return pairs


#Final Compiled Function
def Chinese_Postman(graph):
    odds = get_odd(graph)
    if(len(odds)==0):
        return sum_edges(graph)
    pairs = gen_pairs(odds)
    l = (len(pairs)+1)//2

    
    pairings_sum = []
    
    def get_pairs(pairs, done = [], final = []):
        
        if(pairs[0][0][0] not in done):
            done.append(pairs[0][0][0])
            
            for i in pairs[0]:
                f = final[:]
                val = done[:]
                if(i[1] not in val):
                    f.append(i)
                else:
                    continue
                
                if(len(f)==l):
                    pairings_sum.append(f)
                    return 
                else:
                    val.append(i[1])
                    get_pairs(pairs[1:],val, f)
                    
        else:
            get_pairs(pairs[1:], done, final)
            
    get_pairs(pairs)
    min_sums = []
    
    for i in pairings_sum:
        s = 0
        for j in range(len(i)):
            s += dijktra(graph, i[j][0], i[j][1])
        min_sums.append(s)
    
    added_dis = min(min_sums)
    chinese_dis = added_dis + sum_edges(graph)
    return chinese_dis    
    
print('Chinese Postman Distance for ', graphName, ':', Chinese_Postman(graph))
print('Sum of edges ', graphName, ':', sumEdges)

def format_file(graph, graphName):
    outputStr = ""

    outputStr += "% Graph saved at Tue Jan 12 2021 14:20:49 GMT-0800 (Pacific Standard Time)\n"

    for row in graph:
        outputStr += "n " + str(random.randint(0,400)) + " " + str(random.randint(0,400)) + "\n"

    for row in range(len(graph)):
        for col in range(len(graph[row])):
            if graph[row][col] != 0:
                outputStr += "e " + str(row) + " " + str(col) + " " + str(graph[row][col]) + "\n"

    f = open(graphName + '.txt', "w")
    f.write(outputStr)
    f.close()
    print("file created")

format_file(graph, graphName)