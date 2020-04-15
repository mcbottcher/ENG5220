mkdir -p build && cd build

sudo apt-get update

sudo apt-get install qt5-default qtdeclarative5-dev-tools libqwt-qt5-dev qtmultimedia5-dev \
libqt5multimedia5 libqt5multimedia5-plugins  qtspeech5-flite-plugin libqt5texttospeech5-dev \
flite1-dev libflite1 speech-dispatcher-flite pulseaudio gstreamer1.0-pulseaudio libatlas-base-dev \
libhdf5-serial-dev 

git clone https://github.com/Dobiasd/FunctionalPlus
cd FunctionalPlus
mkdir -p build && cd build
cmake ..
make && sudo make install
cd ../..

git clone -b '3.3.5' --single-branch --depth 1 https://github.com/eigenteam/eigen-git-mirror
cd eigen-git-mirror
mkdir -p build && cd build
cmake ..
make && sudo make install
sudo ln -s /usr/local/include/eigen3/Eigen /usr/local/include/Eigen
cd ../..

git clone -b 'v3.7.1' --single-branch --depth 1 https://github.com/nlohmann/json
cd json
mkdir -p build && cd build
cmake -DBUILD_TESTING=OFF ..
make && sudo make install
cd ../..

git clone https://github.com/Dobiasd/frugally-deep
cd frugally-deep
mkdir -p build && cd build
cmake ..
make && sudo make install
cd ../..

git clone https://github.com/berndporr/iir1.git
cd iir1
mkdir -p build && cd build
cmake ..
make && sudo make install
cd ../..

sudo apt-get install python3

pip3 install numpy tensorflow keras pandas

cd ..
