

#include <iostream>
using namespace std;

class RingBuff {
 
    protected:
        int number_taps; 
    public:
        
        double* buffer;
        unsigned offset = 0;
        RingBuff(int number_taps) ; 
        void process(double sample);
        void reset();
        ~RingBuff();    
};

RingBuff::RingBuff(int number_taps) :
    buffer(new double[number_taps]()) ,
    number_taps(number_taps)
    {
    reset();
     
}
 
 // RingBuff Class destructor
RingBuff::~RingBuff(){
    delete[] buffer;
}
void RingBuff::reset(){
    for(unsigned int i = 0; i < number_taps; i++)
    {
        buffer[i] = 0;
    }
 
}
void RingBuff::process(double sample){
    double *val = buffer + offset;
    *val = sample;
    if (++offset>= number_taps){
        offset = 0;
    }
}

int main(){
    int taps = 2;
    RingBuff delayobj(taps);
    

    cout << "input 1" << endl;
    delayobj.process(1);
    for (int i = 0; i < taps;i++){
        cout << delayobj.buffer[i];
    }
    cout << endl;

    cout << "input 2" << endl;
    delayobj.process(2);
    for (int i = 0; i < taps;i++){
        cout << delayobj.buffer[i];
    }
    cout << endl;

    cout << "input 3" << endl;
    delayobj.process(3);
    for (int i = 0; i < taps;i++){
        cout << delayobj.buffer[i];
    }
    cout << endl;

    cout << "reset" << endl;
    delayobj.reset();

    for (int i = 0; i < taps;i++){
        cout << delayobj.buffer[i];
    }
    cout << endl;



    return 0;
}