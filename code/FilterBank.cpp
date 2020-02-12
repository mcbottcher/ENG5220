#include "FilterBank.h"


FilterBank::FilterBank(int numberfilter, float fs, float *fcarray):
    numberfilter(numberfilter),
    fs(fs),
    arrout(new double[numberfilter]()){ // create output array of number filter length

    filterarray = new Filter*[numberfilter];  //create array of poitners to  Filter
    //instantiate each Filter with consecutive elements of cutoff frequencies array
    for(int i = 0;i < numberfilter; i++){
        filterarray[i] = new Filter(fs, fcarray[i]);
    }
}

//filter single sample though the array of filters
double* FilterBank::filter_sample(double sample){
    for (int i = 0; i < numberfilter; i++){
        arrout[i] = filterarray[i]->filter(sample);
    }
    return arrout;   // returns pointer to array of processed sample
}

 


