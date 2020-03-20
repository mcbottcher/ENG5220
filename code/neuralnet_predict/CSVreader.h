#include <vector>
#include <iostream>


using namespace std;

class CSVreader{

  public:
    CSVreader(string filename);
    ~CSVreader();
    
    void readCSV();
    void printVectorArray();
    
    vector<vector<float>> getVectorArray();  
    const long int * getValueArray();
  
  private:
  
    string _filename;
    string line;
    vector<vector<float>> vectorarray;
    //TODO dynamically allocate
    long int valuearray[220];
    float fltvaluearray[220];

};
