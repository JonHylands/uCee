#include "Arduino.h"

/* LED Blink, Teensyduino Tutorial #1
	http://www.pjrc.com/teensy/tutorial.html
 
	This example code is in the public domain.
*/

// Teensy 2.0 has the LED on pin 11
// Teensy++ 2.0 has the LED on pin 6
// Teensy 3.0 has the LED on pin 13
const int ledPin = 13;

// the setup() method runs once, when the sketch starts

void setup() {
	// initialize the digital pin as an output.
	pinMode(ledPin, OUTPUT);
	Serial1.begin(57600);
	Serial1.println("LED Blink Test");
}

// the loop() methor runs over and over again,
// as long as the board has power

void loop() {
	digitalWrite(ledPin, HIGH);   // set the LED on
	delay(100);                  // wait for a second
	digitalWrite(ledPin, LOW);    // set the LED off
	delay(900);                  // wait for a second
}
