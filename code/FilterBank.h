#include <Iir.h>
#include <vector>

using namespace std;

//wrapper class to allow instancting template classes
class Filter {
    protected:
        const float fs;
        const float fc;
        Iir::Butterworth::HighPass<4> filt;  //setup fourth order filter

    public:
        Filter(float fs, float fc):
        fs(fs), fc(fc){filt.setup(fs,fc);}
        double filter(double sample){return filt.filter(sample);}
};

class FilterBank {
    protected:
        int numberfilter;   // number of filters required
        const float fs;     // sample rate
        float* fcarray;     // array of cutoff frequencies
        double* arrout;     // pointer to array of processed samples

        // double pointer to filter wrapper
        Filter** filterarray; //look up smart pointers
        
    public:

        FilterBank(int numberfilter, float fs, float* fcarray); 
        ~FilterBank();

        double* filter_sample(double sample);   
};    