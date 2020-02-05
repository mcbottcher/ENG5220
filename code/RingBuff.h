class RingBuff {

    protected:
        int buf_size; 
 
    public:
        double* buffer;
        unsigned buff_point;
 
        RingBuff(int buf_size) ; 
        void insert_sample(double sample);
        void reset_buffer();
        ~RingBuff();    
 
};
