# Riley Ruckman, Travis Shields, Jot Virdee
# TCSS343, Wi21
# Assigmment 4 - Brute Force

import random
import math
import time
import json

import matplotlib.pyplot as plt
import matplotlib
from datetime import datetime
from tkinter import Tk     # from tkinter import Tk for Python 3.x
from tkinter.filedialog import askopenfilename
##############################################################################################################################################
def SSBruteForce(S, t):
    for counter in range(2**len(S)):
        sublist = []
        sum = 0
        for j in range(len(S)): 
            if((counter & (1 << j)) > 0): 
                sublist.append(j)
                sum += S[j]
        if sum == t:
            return True, sublist, len(sublist)+len(S)
    return False, [], 2*len(S)
##############################################################################################################################################
def SSDynamic(S, t):
    length = len(S)
    originalT = t
    A = [[False for i in range(t+1)] for j in range(length)]
    for i in range(length):
        A[i][0] = True

    for j in range(1,t+1):
        A[0][j] = (S[0] == j)

    for i in range(1,length):
        for j in range(1,t+1):
            if j >= S[i]:
                A[i][j] = A[i-1][j] or A[i-1][j-S[i]]
            else:
                A[i][j] = A[i-1][j]
    if A[(length-1)][t] == True:
        subset = []
        for i in range(length-1, -1, -1):
            if t >= S[i]:
                if A[i-1][t-S[i]] == True:
                    t = t - S[i]
                    subset.append(i)
        subset.reverse()
        return True, subset, ((originalT+1)*length) + length
    return False, [], ((originalT+1)*length) + length
##############################################################################################################################################
def SSClever(S, t):
    length = len(S)

    L = list(range(0, length//2))
    H = list(range(length//2, length))

    T = {}  # table of subsets that yield a weight less than t
    l = len(L)
    for counter in range(2**l): 
            sublist = []
            sum = 0
            for j in range(l): 
                if((counter & (1 << j)) > 0): 
                    sublist.append(L[j])
                    sum += S[L[j]]
            if sum == t:
                return True, sublist, 2*len(S) + len(sublist) + 2*len(T)
            elif sum < t:
                T.update({sum: sublist})

    W = {}  # table of subsets that yield a weight less than t
    h = len(H)
    for counter in range(2**h): 
            sublist = []
            sum = 0
            for j in range(h):
                if((counter & (1 << j)) > 0):
                    sublist.append(H[j])
                    sum += S[H[j]]
            if sum == t:
                return True, sublist, 2*len(S) + len(sublist) + 2*len(T) + 2*len(W)
            elif sum < t:
                W.update({sum: sublist})

    for x in T.keys(): #for each entry in table T
        for n in sorted(W.keys()):
            if x + n > t: #skip all combinations that are too large
                break
            if x + n == t: #return if the equality is true
                return True, T.get(x) + W.get(n), 2*len(S) + 2*len(T) + 2*len(W)
    return False, [], 2*len(S) + 2*len(T) + 2*len(W)
##############################################################################################################################################
# Based off user input, different testing scenarios can be created for the three
# Subset Sum algorithms
# Input: number of elements in input list, range of values for list elements, boolean for guranteeing solution, binary value for allowing execution of respective algorithm
# Output: Nested array of output and exection time of each algorithm
def Driver(n, r, v, ableToRun):
    #S = random.sample(range(1, r+1), n) # S is a list of length n with element values ranging from 1 to r
    S = []
    for i in range(n):
        S.append(random.randint(1, r+1))
    if v:
        # The desired sum is calculated from a random subset of S to gurantee a valid solution.
        t = sum(random.sample(S, random.sample(range(1, n+1), 1)[0]))
    else:
        # Assuming that all elements of S are of maximum value r, it is impossible for the sum of S to be greater than n*r. Therefore, n*r+1 is never a valid solution.
        #t = n*r + 1
        t = sum(S) + 1

    # Initializes result of each algorithm to empty
    BruteForceResults = DPResults = CleverResults = ('Null',[], 0)

    # For each algorithm, the execution time is calculated and the results are stored.
    BruteForceStartTime = time.time()
    if (ableToRun & 0b001): # If the respective bit is set in ableToRun, the algorithm is allowed to execute.
        BruteForceResults = SSBruteForce(S, t)
    BruteForceFinalTime = int((time.time() - BruteForceStartTime)*1000)

    DPStartTime = time.time()
    if (ableToRun & 0b010):
        DPResults = SSDynamic(S, t)
    DPFinalTime = int((time.time() - DPStartTime)*1000)

    CleverStartTime = time.time()
    if (ableToRun & 0b100):
        CleverResults = SSClever(S, t)
    CleverFinalTime = int((time.time() - CleverStartTime)*1000)

    print('n = {}, r = {}, v = {}'.format(n, r, v))
    print('t = {}, S = {}'.format(t, S))
    print('BF: Solution = {}, Time = {}, Space = {}'.format(BruteForceResults[1], BruteForceFinalTime, BruteForceResults[2]))
    print('DP: Solution = {}, Time = {}, Space = {}'.format(DPResults[1], DPFinalTime, DPResults[2]))
    print('CL: Solution = {}, Time = {}, Space = {}\n'.format(CleverResults[1], CleverFinalTime, CleverResults[2]))

    # Returns nested array of algorithm results and execution times. Execution times are in seconds (s)
    return [[BruteForceResults, BruteForceFinalTime], [DPResults, DPFinalTime], [CleverResults, CleverFinalTime]]
##############################################################################################################################################
# Automated testing of 3 Subset Sum algorithms
# Stores results of algorithm testing into nested array
# Writes nested array to text file for later use
# Input: Upper limit of algorithm execution time in minutes
# Output: Nested array of testing results
def TestAlgorithms(minuteLimit, upperN, saveStats=True):
    # Initializes 3x2x2 array
    # The order is: Algorithm Type, r-value, v-value
    stats = [[[[[],[],[]] for x in range(2)] for y in range(2)] for z in range(3)]
    nLimit = [0 for x in range(3)]
    for r in [1000, 1000000]:
        for v in [False, True]:
            n = 5 # Algorithm testing is done with at least 5 elements
            ableToRun = 0b111   # Setting bit values here determines which algorithms will be tested
            while(ableToRun > 0b000 and n <= upperN):
                results = Driver(n, r, v, ableToRun)
                for i in range(len(results)):       # Runs through each algorithm's stats
                    if results[i][0][0] != 'Null':  # Checks if currently-selected data is valid
                        if results[i][0][0] != v:
                            return i
                        timeRan = results[i][1]     # Grabs execution time
                        tableSpace = results[i][0][2]
                        # Based off the unique values of 1,000 amd 1,000,000, using the log of r using base 1,000
                        # will give 1 or 2 for 1,000 and 1,000,000, respectively. This can be used to
                        # select the appropriate index.
                        stats[i][int(math.log(r, 1000))-1][v][0].append(n)
                        stats[i][int(math.log(r, 1000))-1][v][1].append(timeRan)
                        stats[i][int(math.log(r, 1000))-1][v][2].append(tableSpace)
                        # If the currently-selected algorithm runs for more than the specified MinuteLimit, then
                        # the bit for that algorithm is switched to 0. This is done using a XOR operation on the specified bit with 1.
                        if timeRan > minuteLimit*60*1000 or (v and n >= nLimit[i]):
                            ableToRun = ableToRun^(2**i)
                            if (not v):
                                nLimit[i] = n
                n += 1  # Increments n for further tests
            for i in range(len(nLimit)):
                if nLimit[i] == 0:
                    nLimit[i] = n

    if saveStats:
        # Opens/overrides text file for storing stats.
        now = datetime.now() # current date and time
        date_time = now.strftime("%m%d%Y_%H%M%S")
        with open('{}.stats'.format(date_time), 'w', encoding='utf8') as file:
            json.dump(stats, file)
    
    # Returns stats array
    return stats
##############################################################################################################################################
# Reads stats.txt file and return file contents as array
def readStatsFile():
    
    Tk().withdraw() # we don't want a full GUI, so keep the root window from appearing
    #cwd = os.getcwd()
    filename = askopenfilename() # show an "Open" dialog box and return the path to the selected file

    with open(filename, 'r', encoding='utf8') as file:
            return json.load(file)
##############################################################################################################################################
# Plots the data from the algorithm results using matplotlib.pyplot
# Each testing scenario gets its own plot
# Input: nested array of results
# Output: none
def plot(stats, showPlots = True, savePlots = True):
    # Strings for the title of each plot, based off each scenario
    algorithmTitles = ('Brute Force', 'Dynamic Programming', 'Clever Algorithm', 'All Algorithms')
    rValueTitles = (', r = 1,000', ', r = 1,000,000')
    vValueTitles = (', v = False', ', v = True')
    complexityTitles = (', Time', ', Space')
    algorithmFigureNames = ('BF', 'DP', 'CL', 'ALL')
    rFigureNames = ('thou', 'mill')
    vFigureNames = ('F', 'T')
    complexityNames = ('Time', 'Space')
    yAxisLabels = ('Time (ms)', 'Table Space (Number of Entries)')
    for i in range(len(stats)):                         # Type of Algorithm
        for j in range(len(stats[i])):                  # r value
            for k in range(len(stats[i][j])):           # v value
                for l in range(1, len(complexityNames)+1):
                    if len(stats[i][j][k][0]) > 0:
                        plt.scatter(stats[i][j][k][0], stats[i][j][k][l])
                        plt.plot(stats[i][j][k][0], stats[i][j][k][l])
                        plt.xlabel('n')
                        plt.ylabel(yAxisLabels[l-1])
                        # Grabs the correct string based off the location in for loop
                        plt.title(algorithmTitles[i] + rValueTitles[j] + vValueTitles[k] + complexityTitles[l-1])
                        if savePlots:
                            plt.savefig(algorithmFigureNames[i] + rFigureNames[j] + vFigureNames[k] + complexityNames[l-1] + '.png')
                        if showPlots:
                            plt.show()
                        plt.close()
    for x in range(1, len(complexityNames)+1):
        for i in range(len(stats[0])):
            for j in range(len(stats[0][i])):
                for k in range(len(stats)):
                    if stats[k][i][j] != []:
                        plt.scatter(stats[k][i][j][0], stats[k][i][j][x])
                        plt.plot(stats[k][i][j][0], stats[k][i][j][x], label=algorithmTitles[k])
                plt.xlabel('n')
                plt.ylabel(yAxisLabels[x-1])
                # Grabs the correct string based off the location in for loop
                plt.title(algorithmTitles[3] + rValueTitles[i] + vValueTitles[j] + complexityTitles[x-1])
                plt.legend()
                if x == 2:
                    plt.yscale('log')
                if savePlots:
                    plt.savefig(algorithmFigureNames[3] + rFigureNames[i] + vFigureNames[j] + complexityNames[x-1] + '.png')
                if showPlots:
                    plt.show()
                plt.close()                                                           
##############################################################################################################################################
minuteLimit = 5
upperN = 100
saveStats = True

#stats = TestAlgorithms(minuteLimit, upperN, saveStats)
#if stats == int:
    #print("Algorithm {} doesn't work".format(stats))
stats = readStatsFile()
plot(stats, True, True)
