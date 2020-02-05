

#include <iostream>
using namespace std;

class RingBuff {
 
    protected:
        int buf_size; 
    public:
        
        double* buffer;
        unsigned offset = 0;
        RingBuff(int buf_size) ; 
        void process(double sample);
        void reset_buffer();
        ~RingBuff();    
};

RingBuff::RingBuff(int buf_size) :
    buffer(new double[buf_size]()) ,
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
    double *val = &buffer[offset];
    *val = sample;
    if (++offset>= buf_size){
        offset = 0;
    }
}

int main(){
    int taps = 5;
    RingBuff delayobj(taps);
    

    cout << "input 1" << endl;
    delayobj.process(1.3);
    for (int i = 0; i < taps;i++){
        cout << delayobj.buffer[i] << " " ;
    }
    cout << endl;

    cout << "input 2" << endl;
    delayobj.process(2.1);
    for (int i = 0; i < taps;i++){
        cout << delayobj.buffer[i] << " " ;
    }
    cout << endl;

    cout << "input 3" << endl;
    delayobj.process(3.6);
    for (int i = 0; i < taps;i++){
        cout << delayobj.buffer[i] << " " ;
    }
    cout << endl;

    cout << "input 4" << endl;
    delayobj.process(4.8);
    for (int i = 0; i < taps;i++){
        cout << delayobj.buffer[i] << " " ;
    }
    cout << endl;

    cout << "input 5" << endl;
    delayobj.process(5.4);
    for (int i = 0; i < taps;i++){
        cout << delayobj.buffer[i] << " " ;
    }
    cout << endl;

    cout << "reset_buffer" << endl;
    delayobj.reset_buffer();

    for (int i = 0; i < taps;i++){
        cout << delayobj.buffer[i] << " " ;
    }
    cout << endl;



    return 0;
}