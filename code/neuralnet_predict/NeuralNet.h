#include <fdeep/fdeep.hpp>


#define NUMBER_OF_ROWS 11
#define NUMBER_OF_COLUMNS 20

class NeuralNet{

    public:
        NeuralNet();
        ~NeuralNet();

	void predict();

	void insertSamples(float* sampleBuff);
        
    private:
        
        fdeep::model _model = fdeep::load_model("fdeep_model.json");
        
        //11 rows, 20 columns
        float netInputs[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = {0};
        
};
