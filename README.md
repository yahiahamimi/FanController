# Fan Controller

This project is a simple fan controller using an ATmega32 microcontroller. The project uses a temperature sensor (LM35) to measure the room temperature and adjust the fan speed accordingly.

The project consists of the following components:

* ATmega32 microcontroller
* LM35 temperature sensor
* Fan motor
* LCD display
* Keypad

The project uses the following features of the ATmega32 microcontroller:

* ADC (Analog to Digital Converter) to read the temperature from the LM35 sensor
* PWM (Pulse Width Modulation) to control the fan speed
* Timer0 to generate a PWM signal
* UART to communicate with the LCD display
* Keypad to input the desired temperature

The project has the following functionalities:

* Measure the room temperature using the LM35 sensor
* Adjust the fan speed according to the measured temperature
* Display the current temperature on the LCD display
* Allow the user to input the desired temperature using the keypad
* Change the fan speed according to the input temperature

The project is implemented using the C programming language and the AVR-GCC compiler. The code is written in a modular fashion, with each component of the project being implemented in a separate file. The code is also well commented, making it easy to understand and modify.
