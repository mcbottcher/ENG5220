#include <stdio.h>
#include <curses.h>
#include <python3.6m/Python.h>

#define FILENAME "attempt1.py"

class TrainNet {
    private:
    protected:
    public:
    TrainNet(){
        char filename[] = FILENAME;
        FILE* fp;
        Py_Initialize();
        fp = _Py_fopen(filename, "r");
        PyRun_SimpleFile(fp, filename);
        Py_Finalize();
    }


};