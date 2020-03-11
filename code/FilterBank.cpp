#include "FilterBank.h"


FilterBank::FilterBank(int numberOfFilters, int filterOrder, double sampleRate, double *cutoffFrequencies):
    numberOfFilters(numberOfFilters),
    sampleRate(sampleRate),
    filterOrder(filterOrder),
    outputArray(new double[numberOfFilters]()){ // create output array of number filter length

    filterObjArray = new Filter*[numberOfFilters];  //create array of poitners to  Filter
    //instantiate each Filter with consecutive elements of cutoff frequencies array
    for(int i = 0;i < numberOfFilters; i++){
        filterObjArray[i] = new Filter(filterOrder,sampleRate, cutoffFrequencies[i]);
    }
}

void FilterBank::setup(){
    for(int i = 0;i < numberOfFilters; i++){
        filterObjArray[i]->setup();
    }
}

//filter single sample though the array of filters
double* FilterBank::filter(double sample){
    for (int i = 0; i < numberOfFilters; i++){
        outputArray[i] = filterObjArray[i]->filter(sample);
    }
    return outputArray;   // returns pointer to array of processed sample
}

 


