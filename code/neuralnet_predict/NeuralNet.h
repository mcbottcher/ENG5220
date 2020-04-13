#include <fdeep/fdeep.hpp>

/** Defines neural net input row size */
#define NUMBER_OF_ROWS 11
/** Defines neural net input column size */
#define NUMBER_OF_COLUMNS 20

/** 
* A class defining a feed forward neural network based on a Keras model 
*/
class NeuralNet{

    public:
        NeuralNet();
        ~NeuralNet();
	
	/** 
	* A function to perform one feed forward run of the neural network
	* \return A tensor containing the predicted output layer weights
	*/
	fdeep::tensor predict();

    /**
    * A function to insert an array of new samples into the neural network inputs.
    * The function shifts exisiting inputs by one place inserting the new sample at the first input
    * and disgrading the last input
    *
    * @param sampleBuff a pointer to a buffer of new samples, buffer must have a size equal to the number 
    * of net input rows
    *
    * @see netInputs
    */
	void insertSamples(float* sampleBuff);

    /**
    * A function to return the number of network output nodes
    * \return Number of network output nodes
    */
	int get_number_of_outputs();
        
    private:
        
        /** Holds the Cpp implementation of a Keras defined neural network model */
        fdeep::model _model = fdeep::load_model("Qt/fdeep_model.json");
        
        /** Array to hold inputs to the neural network */
        float netInputs[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = {0};

};
