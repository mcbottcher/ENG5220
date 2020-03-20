#include "NeuralNet.h"
#include "CSVreader.h"

#include <iostream>

int main(){

    NeuralNet mynet;
    
    CSVreader indata("verificationData.csv");
	indata.readCSV();
	vector<vector<float>> data = indata.getVectorArray();



    for(int k=0; k<20; k++){

        vector<float> firstrow = data[k];

        float temp[11];
        
        for(int i=0; i<20; i++){
            
            for(int j=0; j<11; j++){
                temp[j] = firstrow[(i + j*20)];
            }
 
            mynet.insertSamples(temp);    
            
        }
        
        
        
        mynet.predict();
     }
        
    
    return 0;
}
