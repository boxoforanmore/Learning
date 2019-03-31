import keras
from keras.models import Sequential
from keras.layers import Dense

model = Sequential()

model.add(Dense(3, activation='relu', input_shape=(1,)))
model.add(Dense(1, activation='linear'))

print('Model Summary %s')
print(model.summary())


:
