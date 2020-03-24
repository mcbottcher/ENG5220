<p align="center">
  <img height="269" width="500" src="https://github.com/mcbottcher/ENG5220/blob/master/images/logo_with_text-1.png">
</p>

# The Power Is In Your Hands

The Lexicon Glove is a wearable glove capable of interpreting hand movements to produce speech and text outputs so that the wearer can communicate in ways they may be unable to otherwise. A combination of flex sensors and an accelerometer/gyroscope provide data about the position and movement of the user's hands. Using this data to train a neural network, the user can teach custom gestures to the Lexicon Glove to suit their individual needs. Gestures are linked with words or phrases that will be output as text and audio when the glove is interpreting the user's movements. The Lexicon Glove is controlled using a Qt application run on a Raspberry Pi and displayed on a monitor. There are two modes of operation; Training Mode and Interpret Mode.

In Training Mode, the user can create a new custom gesture linked to a word or phrase of their choice. During training, they will be taken through the process of creating training data for the neural network by repeating the movement a number of times. Once training is completed, the training data for all of the gestures is used to create a neural network model. In Interpret Mode, the model is used to correctly output words/phrases based on the glove movements in real time.

### Applications
The Lexicon Glove could be useful as a sign language interpretation glove, allowing deaf people and other sign language users to communicate more easily with people who don't understand sign language, as well as a tool for sign language education. With further development, an online database could be created for users to share and access movement data to create large libraries of gestures. The glove's ability to learn custom gestures means it could also be very useful for people with a range of other disabilites to communicate using movements that are easy for them.


### Build Instructions



Proposed hardware:
* Sensors on fingers.
* RaspberryPi to read movements and produce sounds.

Proposed software:
* Neural network to classify hand movement inputs.
* Button interface to switch between learning and predicting mode
* Tk/Qt interface?

Follow us on [Twitter](https://twitter.com/GloveLexicon)! 
