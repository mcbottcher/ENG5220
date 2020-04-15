cd cppTimer
qmake
make
./cppTimerTest

cd ..

cd neuralNetwork
chmod +x neuralNetTestSetup.sh
./neuralNetTestSetup.sh
qmake
make 
./neuralNetTest

cd ..
