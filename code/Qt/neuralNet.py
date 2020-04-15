#!/usr/bin/python

import convert_model
import sys
import os
import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from keras.utils import to_categorical
from numpy import genfromtxt
import pandas as pd


# number of arguments : len(sys.argv)
# list of strings of arugments: str(sys.argv)

training_data = np.empty(shape=(0,220))
training_labels = np.empty(shape=(0))

net_output_map = dict()

for argument_number in range(1,len(sys.argv)): #first argument is the filename...
    
    filename = os.path.join(os.path.dirname(__file__), '../movementData/') + str(sys.argv[argument_number])
    
    if (argument_number - 1) not in net_output_map.keys():
        net_output_map[(argument_number - 1)] = filename
    
    csv_file = pd.read_csv(filename)
    csv_data = csv_file.to_numpy()
    
    #delete the nans
    csv_data = np.delete(csv_data, 220, 1) #this 220 assumes 2 seconds at 10 hz
    for row in range(len(csv_data)):
    
        temp = csv_data[row]
        temp[:120] = (temp[:120]/2**15)
        temp[120:] = (temp[120:]/2**12) - 0.5
        
        label = np.zeros(1)
        label[0] = argument_number - 1
        
        training_labels = np.append(training_labels, label, 0)
        
    training_data = np.append(training_data, csv_data, 0)
    
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# Build the model.
model = Sequential([
  Dense(330, activation='relu', input_shape=(220,)),
  Dense(64, activation='relu'),
  Dense(64, activation='relu'),
  Dense(len(sys.argv)-1, activation='softmax'),
])

# Compile the model.
model.compile(
  optimizer='adam',
  loss='categorical_crossentropy',
  metrics=['accuracy'],
)

# Train the model.
model.fit(
  training_data,
  to_categorical(training_labels),
  epochs=200,
  batch_size=32,
)

model.save('keras_model.h5', include_optimizer=False)

file1 = open("outputMap.txt","w")
for key in net_output_map.keys():
    file1.write(net_output_map[key].replace("../movementData/","").replace(".csv","").replace("_"," "))
    file1.write("\n")
file1.close() 

convert_model.convert('keras_model.h5', 'fdeep_model.json', False)

#verificationfilename = os.path.join(os.path.dirname(__file__), '../movementData/verificationData.csv')
#df5 = pd.read_csv(verificationfilename)
#predict_data = df5.to_numpy()
#delete the nans
#predict_data = np.delete(predict_data, 220, 1)
#for i in range(len(predict_data)):
#    temp = predict_data[i]
#    temp[:120] = (temp[:120]/2**15)
#    temp[120:] = (temp[120:]/2**12) - 0.5

#predictions = model.predict(predict_data)

#for i in range(len(predictions)):
#    print(predictions[i])

#print(np.argmax(predictions, axis=1))
