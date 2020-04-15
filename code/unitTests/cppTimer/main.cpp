#include "../../cppTimer/CppTimer.h"
#include <unistd.h>
#include <time.h>
#include <thread>
#include <stdio.h>
#include <iostream>

static int count = 0;
static int stop_count = 0;

class Timer1 : public CppTimer {

	void timerEvent() {
		count++;
	}
};


int main( int argc, const char* argv[]){

	Timer1 Timer1;
	
	try{
		Timer1.start(1000000000);
		std::this_thread::sleep_for(std::chrono::seconds(2));
		Timer1.stop();
		
		if(!count){throw std::string("timer did not start");}
    }catch (std::string e){
        std::cout << "An exception occurred with cppTimer: " << e << '\n' << std::endl;
        return EXIT_FAILURE;
    }
    
    stop_count = count;    

    try{
    	std::this_thread::sleep_for(std::chrono::seconds(2));
    	if(count!=stop_count){throw std::string("timer did not stop");}
    }catch (std::string e){
        std::cout << "An exception occurred with cppTimer: " << e << '\n' << std::endl;
        return EXIT_FAILURE;
    }
    
    
    try{
    	Timer1.start(1000000000);
    	std::this_thread::sleep_for(std::chrono::seconds(2));
    	Timer1.stop();
    	if(count==stop_count){throw std::string("timer did not restart");}
    }catch (std::string e){
        std::cout << "An exception occurred with cppTimer: " << e << '\n' << std::endl;
        return EXIT_FAILURE;
    }
    
    
    std::cout << "cppTimer Module Passed Tests" << std::endl << std::endl;
    
    return EXIT_SUCCESS;
    
}
