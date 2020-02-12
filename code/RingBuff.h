using namespace std;

class RingBuff {
    protected:
        int buf_size;
 
    public:
        double* buffer;
        unsigned element_ptr;
        RingBuff(int buf_size); 
        ~RingBuff(){delete[] buffer;};
        void insert_sample(double sample);
        void reset_buffer();
        double* get_buff_address(){return buffer;}
        int get_buff_len(){return buf_size;}
        int get_element_ptr(){return element_ptr;}
};    
 
