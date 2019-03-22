import numpy as np
from keras.models import Sequential
from keras.layers import Dense


x = [[1],[2],[3],[4]]
y = [[2],[4],[6],[8]]


model = Sequential()
model.add(Dense(1, activation='linear', input_shape=(1,)))
model.summary()


from keras.optimizers import SGD

sgd = SGD(lr=0.01)

model.compile(optimizer=sgd,loss='mean_squared_error',metrics=['accuracy'])



from copy import deepcopy
w_ = deepcopy(model.get_weights())

print('\n\nWeights:\n',w_)



def feed_forward(inputs, outputs, weights):
    pre_hidden = np.dot(inputs,weights[0])+ weights[1]
    ## The following line acts as a sigmoid activation function
    hidden = 1/(1+np.exp(-pre_hidden))
    out = np.dot(hidden, weights[2]) + weights[3]
    squared_error = (np.square(pred_out - outputs))
    return squared_error


####################################
#### Other activation functions ####
####################################

def tanh(x):
    return (exp(x)-exp(-x))/(exp(x)+exp(-x))

def relu(x):
    return np.where(x>0,x,0)

def linear(x):
    return x

def softmax(x):
    ## Usually for labelling outputs
    return np.exp(x)/np.sum(np.exp(x))


################################
#### Typical Loss Functions ####
################################

def mse(p, y):
    ## Usually for continuous values
    return np.mean(np.square(p - y))

def mae(p, y):
    ## Usually for continuous values
    return np.mean(np.abs(p-y))

def cat_cross_entropy(p, y):
    return -np.sum((y*np.log2(p)+(1-y)*np.log2(1-p)))


