#ifndef RINGBUFF_H
#define RINGBUFF_H

using namespace std;

class RingBuff {
    protected:
        int bufSize;
        
    public:
        double* buffer;
        unsigned elementPtr;
        RingBuff(int bufSize); 
        ~RingBuff(){delete[] buffer;};
        void insertSample(double sample);
        void resetBuffer();
        double* getBuffAddress(){return buffer;}
        int getBuffLen(){return bufSize;}
        int getElementPtr(){return elementPtr;}
        double* readBuffer();
};    
 
#endif // RINGBUFF_H
