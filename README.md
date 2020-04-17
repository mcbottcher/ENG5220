<p align="center">
  <img height="269" width="500" src="https://github.com/mcbottcher/ENG5220/blob/master/images/logo_with_text-1.png">
</p>

# The Power Is In Your Hands

[![Build Status](https://travis-ci.com/mcbottcher/ENG5220.svg?branch=master)](https://travis-ci.com/mcbottcher/ENG5220)

The Lexicon Glove is a wearable glove capable of interpreting hand movements to produce speech and text outputs so that the wearer can communicate in ways they may be unable to otherwise. A combination of flex sensors and an accelerometer/gyroscope provide data about the position and movement of the user's hands. Using this data to train a neural network, the user can teach custom gestures to the Lexicon Glove to suit their individual needs. Gestures are linked with words or phrases that will be output as text and audio when the glove is interpreting the user's movements. The Lexicon Glove is controlled using a Qt application run on a Raspberry Pi and displayed on a monitor. There are two modes of operation; Training Mode and Interpret Mode.

In Training Mode, the user can create a new custom gesture linked to a word or phrase of their choice. During training, they will be taken through the process of creating training data for the neural network by repeating the movement a number of times. Once training is completed, the training data for all of the gestures is used to create a neural network model. In Interpret Mode, the model is used to correctly output words/phrases based on the glove movements in real time.

You can 

For more information about the design of the Lexicon Glove and its applications, see the [Wiki](https://github.com/mcbottcher/ENG5220/wiki), where you can also watch some [Demonstration Videos](https://github.com/mcbottcher/ENG5220/wiki/Demonstration-Videos) of the key features!

<p align="center">
  <img height="227" width="403" src="https://github.com/mcbottcher/ENG5220/blob/master/images/glove_photo_1.jpg">
</p>

### Code Documentation
Avaliable at this repo's [GitHub pages](https://mcbottcher.github.io/ENG5220)!


### Build Instructions

Install the QT5, Qwt and all other relevant packages:
```
  sudo chmod +x installdependencies.sh
  ./installdependencies.sh
```
To build:
```
  cd code
  qmake
  make
```
To setup the i2c functionality (only has to be run first time):
```
  cd code/MCP3428/I2Cdev
  chmod +x setup-i2c.sh
  ./setup-i2c.sh
```

To allow text-to-speech functionality (only has to be run first time):
```
  pulseaudio -D
```

To run:
```
  ./lexicon_glove
```


Follow us on [Twitter](https://twitter.com/GloveLexicon)!
Follow us on [Hackaday.io](https://hackaday.io/project/170876-realtime-gesture-recognition-glove)!

### Authors and Contributors 
* [Mikkel Caschetto-Bottcher](https://github.com/mcbottcher)
* [Dan Wareing](https://github.com/danwareing1)
* [James Lee](https://github.com/jamielee183)

