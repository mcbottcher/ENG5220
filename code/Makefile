sample.exe: MCP3428.o sampledata.o MPU6050.o I2Cdev.o RingBuff.o
	g++ MCP3428.o sampledata.o MPU6050.o I2Cdev.o RingBuff.o -o sample.exe -lrt

MCP3428.o: MCP3428/MCP3428.cpp MCP3428/MCP3428.h
	g++ -c MCP3428/MCP3428.cpp

MPU6050.o: MPU6050/MPU6050.cpp MPU6050/MPU6050.h
	g++ -c MPU6050/MPU6050.cpp

I2Cdev.o: MPU6050/I2Cdev/I2Cdev.cpp MPU6050/I2Cdev/I2Cdev.h
	g++ -c MPU6050/I2Cdev/I2Cdev.cpp

RingBuff.o: RingBuff.h RingBuff.cpp
	g++ -c RingBuff.cpp

sampledata.o: sampledata.cpp cppTimer/CppTimer.h MCP3428/MCP3428.h 
	g++ -c sampledata.cpp

clean:
	rm *.o sample.exe
