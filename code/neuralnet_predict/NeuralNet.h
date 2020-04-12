#include <fdeep/fdeep.hpp>

#define NUMBER_OF_ROWS 11
#define NUMBER_OF_COLUMNS 20

class NeuralNet{

    public:
        NeuralNet();
        ~NeuralNet();

	fdeep::tensor predict();

	void insertSamples(float* sampleBuff);

	int get_number_of_outputs();
        
    private:
        
        fdeep::model _model = fdeep::load_model("Qt/fdeep_model.json");
        
        //11 rows, 20 columns
        float netInputs[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = {0};

};
