#include "RingBuff.h"

RingBuff::RingBuff(int buf_size) :
    buffer(new double[buf_size]()) ,
    element_ptr(0) , 
    buf_size(buf_size){
    reset_buffer();
}

void RingBuff::reset_buffer(){
    for(unsigned int i = 0; i < buf_size; i++){
        buffer[i] = 0;
    }
}

void RingBuff::insert_sample(double sample){
    double* val = &buffer[element_ptr];
    *val = sample;
    if (++element_ptr >= buf_size){
        element_ptr = 0;
    }
}
