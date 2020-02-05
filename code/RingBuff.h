class RingBuff {

    protected:
        int buf_size; 
 
    public:
        double* buffer;
        unsigned offset;
 
        RingBuff(int buf_size) ; 
        void process(double sample);
        void reset_buffer();
        ~RingBuff();    
 
};
