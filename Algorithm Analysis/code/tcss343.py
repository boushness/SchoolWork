# Riley Ruckman, Travis Shields, Jot Virdee
# TCSS343, Wi21
# Assigmment 4

import random
import time
##############################################################################################################################################
def SSBruteForce(S, t):
    for counter in range(2**len(S)): #Loop to length of powerset
        sublist = []
        sum = 0
        for j in range(len(S)):     #Loop to number of bits needed to represent powerset (n)
            if((counter & (1 << j)) > 0): #If element j should be present in current powerset element
                sublist.append(j)         #Add that index to subset
                sum += S[j]
        if sum == t:
            return True, sublist, len(sublist)+len(S) #if solution found, return
    return False, [], 2*len(S)
##############################################################################################################################################
def SSDynamic(S, t):
    length = len(S) 
    originalT = t   #Store t because recovering the subset changes t
    A = [[False for i in range(t+1)] for j in range(length)] #initialize every element of n*t array to false
    for i in range(length):
        A[i][0] = True  #Set all positions where sum = 0 to True

    for j in range(1,t+1):
        A[0][j] = (S[0] == j)   #If first element is < t set corresponding j to True

    for i in range(1,length): #Loop through n
        for j in range(1,t+1): #Loop through t
            if j >= S[i]:
                A[i][j] = A[i-1][j] or A[i-1][j-S[i]] #If the value of n cannot be used in this potential subset
            else:
                A[i][j] = A[i-1][j] #If the value of n cannot be used in this potential subset
    if A[(length-1)][t] == True: #Recovering the subset
        subset = []
        for i in range(length-1, -1, -1):
            if t >= S[i]:       
                if A[i-1][t-S[i]] == True: #work backwards though a path that is always true
                    t = t - S[i]
                    subset.append(i)
        subset.reverse()           #indexes are recovered in reverse order
        return True, subset, ((originalT+1)*length) + length
    return False, [], ((originalT+1)*length) + length
##############################################################################################################################################
def SSClever(S, t):
    length = len(S)

    L = list(range(0, length//2))
    H = list(range(length//2, length))

    T = {}  # table of subsets that yield a weight less than t
    l = len(L)
    for counter in range(2**l): #Use brute force method to find powerset of lower half
            sublist = []
            sum = 0
            for j in range(l): 
                if((counter & (1 << j)) > 0): 
                    sublist.append(L[j])
                    sum += S[L[j]]
            if sum == t:
                return True, sublist, 2*len(S) + len(sublist) + 2*len(T) #if lower half contains valid subset, return
            elif sum < t:
                T.update({sum: sublist})

    W = {}  # table of subsets that yield a weight less than t
    h = len(H)
    for counter in range(2**h): #Use brute force method to find powerset of upper half
            sublist = []
            sum = 0
            for j in range(h):
                if((counter & (1 << j)) > 0):
                    sublist.append(H[j])
                    sum += S[H[j]]
            if sum == t:
                return True, sublist, 2*len(S) + len(sublist) + 2*len(T) + 2*len(W) #if upper half contains valid subset, return
            elif sum < t:
                W.update({sum: sublist})

    for x in T.keys(): #Look for solution by combining subsets of lower and upper half
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

    # Prints out all necessary information in a clean output
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
def TestAlgorithms(minuteLimit=5, upperN=100):
    nLimit = [0 for x in range(3)]
    for r in [1000, 1000000]:
        for v in [False, True]:
            n = 5 # Algorithm testing is done with at least 5 elements
            ableToRun = 0b111   # Setting bit values here determines which algorithms will be tested
            while(ableToRun > 0b000 and n <= upperN):
                results = Driver(n, r, v, ableToRun)
                for i in range(len(results)):       # Runs through each algorithm's stats
                    if results[i][0][0] != 'Null':  # Checks if currently-selected data is valid
                        if results[i][0][0] != v:   # Checks if any of the algorithm's boolean output doesn't match the expected output
                            return i
                        timeRan = results[i][1]     # Grabs execution time
                        # If the execution time of any of the algorithms are past the time limit,
                        # or if the v is currently True and n is past the nLimit value from the last False run for any of the algorithms
                        # a bit in ableToRun is switched to 0 to stop that given algorithm from running in the next iteration
                        if timeRan > minuteLimit*60*1000 or (v and n >= nLimit[i]):
                            ableToRun = ableToRun^(2**i)
                            if (not v):
                                nLimit[i] = n
                n += 1  # Increments n for further tests
            # Sets nLimit value after every scenario
            for i in range(len(nLimit)):
                if nLimit[i] == 0:
                    nLimit[i] = n                                                       
##############################################################################################################################################

# Command Line interface for running manual and automatic testing

print('This program tests the time and space complexity of three different Subset Sum algorithm solutions.')
print('The testing can either be done manually or automatically.')
print('\nThe manual test conducts one test with an user-provided:'
    + '\n\tn: number of elements in the input list. (at least 5)'
    + '\n\tr: limits the elements of the input list to the range of 1 to r. (at least 1)'
    + '\n\tv: guarantees an impossible sum or a real sum. (False/True)')

print('\nThe automatic test conducts iterative tests with 4 different scenarios:'
    + '\n\tr = 1000, v = False' 
    + '\n\tr = 1000, v = True'
    + '\n\tr = 1,000,000, v = False'
    + '\n\tr = 1,000,000, v = True'
    + '\nThis testing will run with the optional, user-provided:'
    + '\n\tTime limit: limits the amount of time for any algorithm to run. (default is 5 minutes).' 
    + '\n\tnUpper: limits the highest n value any algorithm can run. (default is 40)'
    + '\n\nn is incremented by 1 when the current round is over, and the algorithms will be stopped from the next round if their execution times exceeds the'
    + '\nuser-provided time limit, or n reaches the user-provided nUpper value.')

print("\nBoth testing choices have limits: n and nUpper are at least 5, r cannot be smaller than 1, and the time limit cannot be smaller than 0.")

# Asks user if they want to do manual or automatic testing, and checks the input
user = input('\nWould you like to do manual testing, automatic testing, or end the program? (M/A/E): ')
while user != 'A' and user != 'M' and user != 'E':
    print('\nInvalid input.')
    user = input('Would you like to do manual testing, automatic testing, or end the program? (M/A/E): ')

# Continuously runs until user wants to leave
while user != 'E':
    if user == 'M': # Manual testing
        print('\nYou chose manual testing.')

        # Grabs n value from user
        n = input('\nPlease enter a value for n (n must be an integer and greater than 5.): ')
        go = False
        while(not go):  # Since input() is a string, the input variable will try to typecast it into an acceptable type
            try:        # and proceed with input checking
                n = float(n)
                if n >=5 and n.is_integer():
                    n = int(n)
                    go = True
            except:
                continue
            if (not go):
                print('\nInvalid input. n must be an integer and greater than 5.')
                n = input('Please enter a value for n (n must be an integer): ')

        # Grabs r value from user
        r = input('\nPlease enter a value for r (r must be an integer.): ')
        go = False
        while(not go):
            try:
                r = float(r)
                if r >=1 and r.is_integer():
                    r = int(r)
                    go = True
            except:
                continue
            if (not go):
                print('\nInvalid input. r must be an integer and at least 1.')
                r = input('Please enter a value for r (r must be an integer.): ')

        # Grabs v value from user
        v = input('\nPlease enter a value for v (v must be a boolean i.e. True/False.): ')
        while v != 'False' and v != 'True' and v != 'F' and v != 'T':
            print('\nInvalid input. (v must be a boolean i.e. True/False.')
            v = input('Please enter a value for v (v must be a boolean i.e. True/False.): ')
        v = (v == 'True')
        
        # Conducts testing with user-provided values
        print('\nConducting test.')
        Driver(n, r, v, 0b111)
        print('\nTesting Complete.')

        # Asks user if they want to continue manual testing
        user = input('\nWould you like to manually test again? (Y/N): ')
        while user != 'Y' and user != 'N':
            print('\nInvalid input.')
            user = ('Would you like to manually test again?: (Y/N)')
        
        # User can continue manual testing, go to automatic testing, or end the program
        if user == 'Y':
            user = 'M'
        else:
            user = input('\nWould you like to do automatic testing, or end the program? (A/E): ')
            while user != 'A' and user != 'E':      
                print('\nInvalid input.')
                user = input('Would you like to do automatic testing, or end the program? (A/E): ')
    
    if user == 'A': # Automatic testing
        print('\nYou chose automatic testing.')

        # Grabs timeLimit from user
        timeLimit = input('\nPlease enter a value for the time limit (In minutes, and can be a decimal/float.): ')
        go = False
        while(not go):
            if timeLimit == '': # Allows default values, as per the instructions
                timeLimit = 5
                go = True
            else:
                try:
                    timeLimit = float(timeLimit)
                    if timeLimit > 0:
                        go = True
                except:
                    continue
            if (not go):
                print('\nInvalid input. The time limit must be a positive, real number, and preferrably larger than 0.')
                timeLimit = input('Please enter a value for the time limit (In minutes, and can be a decimal/float.): ')

        # Grabs nUpper from user
        nUpper = input('\nPlease enter a value for nUpper (nUpper must be an integer, and at least 5.): ')
        go = False
        while(not go):
            if nUpper == '':
                nUpper = 40
                go = True
            else:
                try:
                    nUpper = float(nUpper)
                    if nUpper >= 5 and nUpper.is_integer():
                        go = True
                except:
                    continue
            if (not go):
                print('\nInvalid input. nUpper must be an integer, and at least 5.')
                nUpper = input('Please enter a value for nUpper (nUpper must be an integer, and at least 5.): ')
        
        # Conducts automatic testing
        print('\nConducting tests.')
        TestAlgorithms(timeLimit, nUpper)
        print('\nTesting Complete.')

        # Asks user if they want to continue automatic testing
        user = input('\nWould you like to automatically test again? (Y/N): ')
        while user != 'Y' and user != 'N':
            print('\nInvalid input.')
            user = ('Would you like to automatically test again?: (Y/N)')
        
        # User can continue automatic testing, go to manual testing, or end the program
        if user == 'Y':
            user = 'A'
        else:
            user = input('\nWould you like to do manual testing, or end the program? (M/E): ')
            while user != 'M' and user != 'E':
                print('\nInvalid input.')
                user = input('Would you like to do manual testing, or end the program? (M/E): ')
