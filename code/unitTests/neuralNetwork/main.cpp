#include "../../neuralnet_predict/NeuralNet.h"
#include "../../neuralnet_predict/CSVreader.h"

#include <iostream>

int main(){

    NeuralNet mynet;
    
    try{
		CSVreader indata("testData/testData1.csv");
		indata.readCSV();
		vector<vector<float>> data = indata.getVectorArray();

		vector<float> firstrow = data[0];
		float temp[11];
		for(int i=0; i<20; i++){
			for(int j=0; j<11; j++){
				temp[j] = firstrow[(i + j*20)];
			}
			mynet.insertSamples(temp);    
		}
		

		fdeep::tensor result = mynet.predict();
		
		float outputWeights[2];
		
		int max = 0;
		int max_index = 0;
		for(int i=0; i<2; i++){
		    
		    outputWeights[i] = result.get(fdeep::tensor_pos(i));
		    
		    if(outputWeights[i]>max){
		        max = outputWeights[i];
		        max_index = i;
		    }

		}
		if(max_index){throw std::string("network did not predict test movement1 correctly");}
    }catch(std::string e){
    	std::cout << "An exception occurred with cppTimer: " << e << '\n' << std::endl;
        return EXIT_FAILURE;
    }    
  	
  	
    try{
		CSVreader indata2("testData/testData2.csv");
		indata2.readCSV();
		vector<vector<float>> data2 = indata2.getVectorArray();

		vector<float> firstrow2 = data2[0];
		float temp2[11];
		for(int i=0; i<20; i++){
			for(int j=0; j<11; j++){
				temp2[j] = firstrow2[(i + j*20)];
			}
			mynet.insertSamples(temp2);    
		}
		

		fdeep::tensor result2 = mynet.predict();
		
		float outputWeights2[2];
		
		int max2 = 0;
		int max_index2 = 0;
		for(int i=0; i<2; i++){
		    
		    outputWeights2[i] = result2.get(fdeep::tensor_pos(i));
		    
		    if(outputWeights2[i]>max2){
		        max2 = outputWeights2[i];
		        max_index2 = i;
		    }

		}
		if(!max_index2){throw std::string("network did not predict test movement2 correctly");}
    }catch(std::string e){
    	std::cout << "An exception occurred with cppTimer: " << e << '\n' << std::endl;
        return EXIT_FAILURE;
    }
  	
  	std::cout << "Unit Neural Network Test Passed" << std::endl;
  	
    return EXIT_SUCCESS;
}
