#include "RingBuff.h"

RingBuff::RingBuff(int bufSize) :
    buffer(new double[bufSize]()),
    elementPtr(0), 
    bufSize(bufSize){
    resetBuffer();
}

void RingBuff::resetBuffer(){
    for(unsigned int i = 0; i < bufSize; i++){
        buffer[i] = 0;
    }
}

void RingBuff::insertSample(double sample){
    double* val = &buffer[elementPtr];
    *val = sample;
    if (++elementPtr >= bufSize){
        elementPtr = 0;
    }
}

double* RingBuff::readBuffer(){

    double outputBuffer[bufSize];
    int tempBuffPtr = elementPtr;
    int i = 0;


    for (int count=1; tempBuffPtr+count<bufSize; count++){
        outputBuffer[i]=buffer[tempBuffPtr+count];
        i++;
    }

    for (int count=0; count<=tempBuffPtr; count++){
        outputBuffer[i] = buffer[count];
        i++;
    }

    return outputBuffer;

}
