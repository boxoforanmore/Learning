import keras
from keras.models import Sequential
from keras.layers import Dense
from keras.optimizers import SGD
import numpy as np


X = [[1], [2], [3], [4]]
y = [[2], [4], [6], [8]]
# w_ = [[[-0.82203424, -0.9185806 , 0.03494298]], [0., 0., 0.], [[1.0692896 ],[ 0.62761235],[-0.5426246 ]], [0]]


model = Sequential()

model.add(Dense(3, activation='relu', input_shape=(1,)))
model.add(Dense(1, activation='linear'))

print('Model Summary:')
print(model.summary())

sgd = SGD(lr=0.01)

model.compile(optimizer=sgd,loss='mean_squared_error')
model.fit(np.array(X), np.array(y), epochs=120, batch_size=4, verbose=0)


print('Weights:')
print(model.get_weights())


X_pred = [[5], [6]]

print('Prediction on: %s' % (X_pred))
print(model.predict(np.array(X_pred)))
