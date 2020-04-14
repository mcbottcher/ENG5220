#ifndef FILTERBANK_H
#define FILTERBANK_H


#include <Iir.h>
using namespace std;


//!  A Filter wrapper class 
/*!
    A wrapper class allowing a pointer to pointers
    of the Butterworth Lowpass Iir filter class.

    Link: <a href="https://github.com/berndporr/iir1">Iir class GitHub</a> 
*/
class Filter {

    private:
        
    protected:
        //! Sampling rate double.
        /*! The Sampling rate of the filters. */
        const double sampleRate;
        //! Cutoff frequency double.
        /*! The cutoff frequency of the filter. */
        const double cutoffFrequency;
        //! Filter order integer.
        /*! the required order of the filter. */
        int filterOrder;
        //! Butterworth Lowpass filter object.
        /*!  */
        Iir::Butterworth::LowPass<10> *filt;  

    public:
        //! Filter constructor
        /*!
            Constructor for the Filter wrapper class.
            \param sampleRate The sampling rate if the filter.
            \param cutffFrequency The cutoff frequency of the filter.
            \param filterOrder The required order of the filter.
        */
        Filter(int filterOrder, double sampleRate, double cutoffFrequency):
            sampleRate(sampleRate), cutoffFrequency(cutoffFrequency), 
            filterOrder(filterOrder){
                filt = new Iir::Butterworth::LowPass<10>;
            }

        //! Setup method
        /*!
            A method to setup the filter with the filter order, sample rate and cutoff frequency
        */
        void setup(){filt->setup(filterOrder, sampleRate, cutoffFrequency);}
        
        //! Filter method
        /*!
            A method to send the sample to the filter and
            return the sample processed by the filter.
        */
        double filter(double sample){return filt->filter(sample);}
};

//!  A Filterbank class 
/*!
    A class allowing multiple instances of Filters to be setup in parallel.
    A sample sent to the FilterBank will be sent to each filter and the 
    output of each filter returned as a pointer to an array of processed samples.
    \sa Filter()
*/
class FilterBank {
    private:

    protected:
        //! Number of filters integer.
        /*! The number of filter objects required to run in parallel. */
        int numberOfFilters;   
        //! Sampling rate double.
        /*! The Sampling rate of the filters. */
        const double sampleRate;
        //! Filter order integer.
        /*! the required order of the filter. */
        int filterOrder;     
        //! Output array pointer.
        /*! Pointer to array of processed samples. */
        double* outputArray;     
        //! Filter pointer.
        /*! An array of pointers to the Filter class.
            \sa Filter()
         */
        Filter** filterObjArray; 
        
        
    public:
        //! FilterBank constructor.
        /*!
        Instanciate the FilterBank class and setup the filters with the given parameters
        \param numberOfFilters The number of filters that are required.
        \param filterOrder The required order of the filters.
        \param sampleRate The sampling rate of the filters.
        \param cutoffFrequencies a pointer to an array of cuttoff frequencies for each filter in the FilterBank
        */
        FilterBank(int numberOfFilters, int filterOrder, double sampleRate, double* cutoffFrequencies); 
        //! FilterBank destructor.
        /*!
        Free up the memory and delete the array of Filer objects. 
        */
        ~FilterBank(){delete[] filterObjArray;};
        //! Filter method
        /*!
            A method to send the sample to each filter in parallel
        \param sample The sample to be passed through to all filters.
        \return returns pointer to array of processed sample
        */
        double* filter(double sample); 
        //! Get Array method
        /*!

        \return returns pointer to array of processed sample
        */
        double* getArray(){return outputArray;};
        //! Setup method
        /*!
            A method to setup the FilterBank
        
        */
        void setup();
};    

#endif // FILTERBANK_H