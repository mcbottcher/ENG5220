// main.cpp


#include "NeuralNet.h"

#include <vector>


using namespace std;


NeuralNet::NeuralNet(){
    
}

NeuralNet::~NeuralNet(){

}

void NeuralNet::predict(){
    
    const auto result = _model.predict({fdeep::tensor(fdeep::tensor_shape(static_cast<std::size_t>(220)),{netInputs[0][0],netInputs[0][1],netInputs[0][2],netInputs[0][3],netInputs[0][4],netInputs[0][5],netInputs[0][6],netInputs[0][7],netInputs[0][8],netInputs[0][9],netInputs[0][10],netInputs[0][11],netInputs[0][12],netInputs[0][13],netInputs[0][14],netInputs[0][15],netInputs[0][16],netInputs[0][17],netInputs[0][18],netInputs[0][19],netInputs[1][0],netInputs[1][1],netInputs[1][2],netInputs[1][3],netInputs[1][4],netInputs[1][5],netInputs[1][6],netInputs[1][7],netInputs[1][8],netInputs[1][9],netInputs[1][10],netInputs[1][11],netInputs[1][12],netInputs[1][13],netInputs[1][14],netInputs[1][15],netInputs[1][16],netInputs[1][17],netInputs[1][18],netInputs[1][19],netInputs[2][0],netInputs[2][1],netInputs[2][2],netInputs[2][3],netInputs[2][4],netInputs[2][5],netInputs[2][6],netInputs[2][7],netInputs[2][8],netInputs[2][9],netInputs[2][10],netInputs[2][11],netInputs[2][12],netInputs[2][13],netInputs[2][14],netInputs[2][15],netInputs[2][16],netInputs[2][17],netInputs[2][18],netInputs[2][19],netInputs[3][0],netInputs[3][1],netInputs[3][2],netInputs[3][3],netInputs[3][4],netInputs[3][5],netInputs[3][6],netInputs[3][7],netInputs[3][8],netInputs[3][9],netInputs[3][10],netInputs[3][11],netInputs[3][12],netInputs[3][13],netInputs[3][14],netInputs[3][15],netInputs[3][16],netInputs[3][17],netInputs[3][18],netInputs[3][19],netInputs[4][0],netInputs[4][1],netInputs[4][2],netInputs[4][3],netInputs[4][4],netInputs[4][5],netInputs[4][6],netInputs[4][7],netInputs[4][8],netInputs[4][9],netInputs[4][10],netInputs[4][11],netInputs[4][12],netInputs[4][13],netInputs[4][14],netInputs[4][15],netInputs[4][16],netInputs[4][17],netInputs[4][18],netInputs[4][19],netInputs[5][0],netInputs[5][1],netInputs[5][2],netInputs[5][3],netInputs[5][4],netInputs[5][5],netInputs[5][6],netInputs[5][7],netInputs[5][8],netInputs[5][9],netInputs[5][10],netInputs[5][11],netInputs[5][12],netInputs[5][13],netInputs[5][14],netInputs[5][15],netInputs[5][16],netInputs[5][17],netInputs[5][18],netInputs[5][19],netInputs[6][0],netInputs[6][1],netInputs[6][2],netInputs[6][3],netInputs[6][4],netInputs[6][5],netInputs[6][6],netInputs[6][7],netInputs[6][8],netInputs[6][9],netInputs[6][10],netInputs[6][11],netInputs[6][12],netInputs[6][13],netInputs[6][14],netInputs[6][15],netInputs[6][16],netInputs[6][17],netInputs[6][18],netInputs[6][19],netInputs[7][0],netInputs[7][1],netInputs[7][2],netInputs[7][3],netInputs[7][4],netInputs[7][5],netInputs[7][6],netInputs[7][7],netInputs[7][8],netInputs[7][9],netInputs[7][10],netInputs[7][11],netInputs[7][12],netInputs[7][13],netInputs[7][14],netInputs[7][15],netInputs[7][16],netInputs[7][17],netInputs[7][18],netInputs[7][19],netInputs[8][0],netInputs[8][1],netInputs[8][2],netInputs[8][3],netInputs[8][4],netInputs[8][5],netInputs[8][6],netInputs[8][7],netInputs[8][8],netInputs[8][9],netInputs[8][10],netInputs[8][11],netInputs[8][12],netInputs[8][13],netInputs[8][14],netInputs[8][15],netInputs[8][16],netInputs[8][17],netInputs[8][18],netInputs[8][19],netInputs[9][0],netInputs[9][1],netInputs[9][2],netInputs[9][3],netInputs[9][4],netInputs[9][5],netInputs[9][6],netInputs[9][7],netInputs[9][8],netInputs[9][9],netInputs[9][10],netInputs[9][11],netInputs[9][12],netInputs[9][13],netInputs[9][14],netInputs[9][15],netInputs[9][16],netInputs[9][17],netInputs[9][18],netInputs[9][19],netInputs[10][0],netInputs[10][1],netInputs[10][2],netInputs[10][3],netInputs[10][4],netInputs[10][5],netInputs[10][6],netInputs[10][7],netInputs[10][8],netInputs[10][9],netInputs[10][10],netInputs[10][11],netInputs[10][12],netInputs[10][13],netInputs[10][14],netInputs[10][15],netInputs[10][16],netInputs[10][17],netInputs[10][18],netInputs[10][19]})});
        std::cout << fdeep::show_tensors(result) << std::endl;
}

void NeuralNet::insertSamples(float* sampleBuff){

    for(int i=0; i<NUMBER_OF_ROWS; i++){
        
        float* rowptr = &netInputs[i][0];
            
        memmove(&rowptr[0],&rowptr[1], sizeof(float)*(NUMBER_OF_COLUMNS-1));
        
        rowptr[19] = sampleBuff[i]; 

    }

  
}

