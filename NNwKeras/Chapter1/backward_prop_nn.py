import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from copy import deepcopy

X = [[1], [2], [3], [4]]
y = [[2], [4], [6], [8]]

w = [[[1.477867]], [0.]]

'''
def feed_forward(inputs, outputs, weights):
    out = np.dot(inputs, weights[0]) + weights[1]
    squared_error = (np.square(out - outputs))
    return squared_error

def update_weights(inputs, outputs, weights, epochs):  
    for epoch in range(epochs):
        org_loss = feed_forward(inputs, outputs, weights)
        wts_tmp = deepcopy(weights)
        wts_tmp2 = deepcopy(weights)
        for ix, wt in enumerate(weights): # Kishore gaaru this is the only line I changed.
            print(ix, wt)
            wts_tmp[-(ix+1)] += 0.0001
            # print('wts_tmp:', wts_tmp)
            loss = feed_forward(inputs, outputs, wts_tmp)
            # print('loss', loss)
            delta_loss = np.sum(org_loss - loss)/(0.0001*len(inputs))
            wts_tmp2[-(ix+1)] += delta_loss*0.01
            wts_tmp = deepcopy(weights)

        weights = deepcopy(wts_tmp2)
    return wts_tmp2
'''

## Hidden layer
def feed_forward(inputs, outputs, weights):
    pre_hidden = np.dot(inputs,weights[0])+ weights[1]
    hidden = np.where(pre_hidden<0, 0, pre_hidden)
    out = np.dot(hidden, weights[2]) + weights[3]
    squared_error = (np.square(out - outputs))
    return squared_error


def update_weights(inputs, outputs, weights, epochs):
    for epoch in range(epochs):
        org_loss = feed_forward(inputs, outputs, weights)
        wts_tmp = deepcopy(weights)
        wts_tmp2 = deepcopy(weights)
        for i, layer in enumerate(reversed(weights)):
            for index, weight in np.ndenumerate(layer):
                try:
                    wts_tmp[-(i+1)][index[0]] += 0.0001
                    loss = feed_forward(inputs, outputs, wts_tmp)
                    del_loss = np.sum(org_loss - loss)/(0.0001*len(inputs))
                    wts_tmp2[-(i+1)][index[0]] += del_loss*0.01
                    wts_tmp = deepcopy(weights)
                    weights = deepcopy(wts_tmp2)
                except (TypeError):
                    break
    return weights



w_ = [[[-0.82203424, -0.9185806 , 0.03494298]], [0., 0., 0.], [[1.0692896 ],[ 0.62761235],[-0.5426246 ]], [0]]

model = update_weights(X, y, w_, 1000)

print(model)
