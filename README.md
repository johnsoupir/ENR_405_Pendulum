# Inverted Pendulum Control

This code controls the balance of an inverted pendulum and crane using a proportional-integral-derivative (PID) control algorithm. The code runs on an Arduino or Pi Pico microcontroller and interfaces with a motor, an encoder, a set of endstops, a display, and some buttons.
## Getting Started

To get started, you will need the following:

* An Arduino/Pi Pico microcontroller
* A motor + driver
* An encoder
* A set of endstops
* Some buttons
* The code in this repository

Once you have the hardware set up, upload the code to your Arduino/Pico and power it on.

### Usage

When the Arduino is powered on, it will auto home, then enter a menu mode on the display. Here, you can select the mode of operation by flipping the up / down switch to choose between inverted pendulum and crane modes. Press the go button to start the selected mode.

Once the mode has been selected, the motor will begin moving the pendulum to cancel motion. The encoder will continuously monitor the position of the pendulum, and the PID algorithm will adjust the motor output voltage in an attempt to keep the pendulum stable.

The stop button will immediately stop the motor and return the system to the menu mode. The code will also detect if the pendulum has gone too far off balance or if it has reached one of the endstops, in which case it will stop the motor and return to the menu.

### Configuration

The PID values can be adjusted in the code to optimize the control algorithm for your specific setup. The upwardPID() and downwardPID() functions define the PID values for the "up" and "down" modes, respectively.

The motorLimit variable can be adjusted to set a maximum output voltage for the motor, for safety reasons.

### Contributing

You are welcome to contribute. and also feel free to use and modify the code for your own purposes.
#### License

This code is licensed under the GPL2 licence. 
