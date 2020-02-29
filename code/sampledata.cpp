#include <unistd.h>
#include <stdio.h> 

#include "CppTimer.h"


class Ticker : public CppTimer{

	void timerEvent{
				
		//insert function calls here...
		
	}

}


int main(){

	Ticker sampleTimer;
	sampleTimer.start(100000000); //time in ns == 100ms

}
