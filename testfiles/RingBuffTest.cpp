#include <iostream>
#include "../code/RingBuff.cpp"


using namespace std;

void print_buff(double* buff, int len){
        for (int i = 0; i < len;i++){
            cout << "[" << buff[i] << "]";
        }
        cout << endl;
    }


int main(){
    int len = 4;
    RingBuff delayobj(len);
    
    cout << "input 1" << endl;
    delayobj.insert_sample(1.3);
    print_buff(delayobj.buffer, len);

    cout << "input 2" << endl;
    delayobj.insert_sample(2.1);
    print_buff(delayobj.buffer, len);
    cout << endl;

    cout << "input 3" << endl;
    delayobj.insert_sample(3.6);
    print_buff(delayobj.buffer, len);
    cout << endl;

    cout << "input 4" << endl;
    delayobj.insert_sample(4.8);
    print_buff(delayobj.buffer, len);
    cout << endl;

    cout << "input 5" << endl;
    delayobj.insert_sample(5.4);
    print_buff(delayobj.buffer, len);
    cout << endl;

    cout << "reset_buffer" << endl;
    delayobj.reset_buffer();
    print_buff(delayobj.buffer, len);
    cout << endl;

    cout << "buffer address: "<< delayobj.get_buff_address() << endl;
    cout << "buffer length: " << delayobj.get_buff_len()<< endl;


    return 0;
}
