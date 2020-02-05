#include "RingBuff.h"

using namespace std;

RingBuff::RingBuff(int buf_size) :
    buffer(new double[buf_size]()) ,
    offset(0) , 
    buf_size(buf_size){
    reset_buffer();
}
 
 // RingBuff Class destructor
RingBuff::~RingBuff(){
    delete[] buffer;
}

void RingBuff::reset_buffer(){
    for(unsigned int i = 0; i < buf_size; i++){
        buffer[i] = 0;
    }
}

void RingBuff::process(double sample){
    double* val = &buffer[offset];
    *val = sample;
    if (++offset>= buf_size){
        offset = 0;
    }
}