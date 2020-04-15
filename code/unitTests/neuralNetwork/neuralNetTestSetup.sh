cd ../../Qt

#rename exsisting model
mv fdeep_model.json fdeep_model_COPY.json

#run the python script
python3 neuralNet.py ../unitTests/neuralNetwork/testData/testData1.csv ../unitTests/neuralNetwork/testData/testData2.csv

#move the json to the unit test qt folder
mv fdeep_model.json ../unitTests/neuralNetwork/Qt/fdeep_model.json
mv fdeep_model_COPY.json fdeep_model.json

#run the test 
cd -

#test can be run from test suit .sh

