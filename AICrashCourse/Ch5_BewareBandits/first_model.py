import numpy as np

# Conversion rates (rates of winning) and number of samples
conversionRates = [0.15, 0.04, 0.13, 0.11, 0.05]
N = 10000
d = len(conversionRates)


# Create the dataset
X = np.zeros((N, d))
for i in range(N):
    for j in range(d):
        if np.random.rand() < conversionRates[j]:
            X[i][j] = 1

# Arrays to count wins and losses
nPosReward = np.zeros(d)
nNegReward = np.zeros(d)

# My method to get the best slot machine
#for i in range(N):
#    for j in range(d):
#        if X[i][j] == 1:
#            nPosReward[j] += 1
#        else:
#            nNegReward[j] += 1
#print(nPosReward)
#print(nNegReward)


# Take the best slot machine through beta distribution
# and updating losses and wins
for i in range(N):
    selected = 0
    maxRandom = 0

    for j in range(d):
        randomBeta = np.random.beta(nPosReward[j] + 1,
                                    nNegReward[j] + 1)

        if randomBeta > maxRandom:
            maxRandom = randomBeta
            selected = j

    if X[i][selected] == 1:
        nPosReward[selected] += 1
    else:
        nNegReward[selected] += 1


# Show which slot machine is considered best
nSelected = nPosReward + nNegReward

for i in range(d):
    print(f'Machine Number {i + 1} was selected {nSelected[i]} times')

print(f'CONCLUSION: The best machine is number {np.argmax(nSelected) + 1}')
