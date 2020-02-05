class Delay {
 
    protected:
        int number_taps; 
    public:
        
        double* buffer; 
        Delay(int number_taps) ; 
        void process(double sample);
        void resetline();
        ~Delay();    
};

Delay::Delay(int number_taps) :
    buffer(new double[number_taps]()) ,
    number_taps(number_taps)
    {
    resetline();
}
 
 // Delay Class destructor
Delay::~Delay(){
    delete[] buffer;
}

//Reset buffer
void Delay::resetline(){
    for(unsigned int i = 0; i < number_taps; i++)
    {
        buffer[i] = 0;
    }
}

//Insert sample into buffer
void Delay::process(double sample){
    // roll elements along delayline
    for (int8_t i = number_taps-1; i >= 1; i--) {
        buffer[i] = buffer[i-1]; 
    }
    
    buffer[0] = sample; // insert sample into base of delay line
}
