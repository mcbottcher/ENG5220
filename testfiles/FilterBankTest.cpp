#include <iostream>
#include <string>
#include <fstream>

#include "../code/FilterBank.cpp"

using namespace std;

int main(){
    const int numberfilters = 4;                // number of filters required
    const float fs = 500;                       // sample rate
    const int numbersamples = 500;              // number of samples
    float fc[numberfilters] = {10,50,150,240};  // array of fequency cutoffs

    double samples[numbersamples];                  // setup sample input array
    double samplesout[numberfilters][numbersamples];// setup sample output array

    //read the samples in
    ifstream file("testdata/sin.bin", ios::in | ios::binary);        
    file.read((char*)samples, sizeof(double)*numbersamples);

    //create instance of filterbank with array of cutoff frequencies
    FilterBank filt(numberfilters, fs, fc);


    // filter the samples
    for (int i = 0; i < numbersamples; i++){
        double *temp = filt.filter_sample(samples[i]);

        // place samples in output array
        for (int j =0; j<numberfilters; j++){
            samplesout[j][i] = temp[j];
        }
    }
    
    //save the filtered samples
    ofstream myfile0 ("testdata/filtered0.bin", ios::out | ios::binary);
    myfile0.write(reinterpret_cast <char*> (samplesout[0]), sizeof(double)*numbersamples);

    ofstream myfile1 ("testdata/filtered1.bin", ios::out | ios::binary);
    myfile1.write(reinterpret_cast <char*> (samplesout[1]), sizeof(double)*numbersamples);

    ofstream myfile2 ("testdata/filtered2.bin", ios::out | ios::binary);
    myfile2.write(reinterpret_cast <char*> (samplesout[2]), sizeof(double)*numbersamples);

    ofstream myfile3 ("testdata/filtered3.bin", ios::out | ios::binary);
    myfile3.write(reinterpret_cast <char*> (samplesout[3]), sizeof(double)*numbersamples);




    FilterBank f(numberfilters, fs, fc);
    

    double impulseresponse[numberfilters][numbersamples];

    // filter the samples
	for(int i=0;i<numbersamples;i++) {
		double a=0;
		if (i==10) {a = 1;}
		double *temp = f.filter_sample(a);
        for(int j=0;j<numberfilters; j++){
            impulseresponse[j][i] = temp[j];
        }
        
	}

    ofstream impulse0 ("testdata/impulse0.bin", ios::out | ios::binary);
    impulse0.write(reinterpret_cast <char*> (impulseresponse[0]), sizeof(double)*numbersamples);
    
    ofstream impulse1 ("testdata/impulse1.bin", ios::out | ios::binary);
    impulse1.write(reinterpret_cast <char*> (impulseresponse[1]), sizeof(double)*numbersamples);

    ofstream impulse2 ("testdata/impulse2.bin", ios::out | ios::binary);
    impulse2.write(reinterpret_cast <char*> (impulseresponse[2]), sizeof(double)*numbersamples);

    ofstream impulse3 ("testdata/impulse3.bin", ios::out | ios::binary);
    impulse3.write(reinterpret_cast <char*> (impulseresponse[3]), sizeof(double)*numbersamples);


    return 0;
}