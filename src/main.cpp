/* 
		uCee - a Micro Crawler Robot
*/

#include <Arduino.h>
#include <Metro.h>
#include "RangeFinder.h"
#include "HeartbeatLED.h"

// Teensy 3.1 has the LED on pin 13
const int ledPin = 13;
const int serialBaudRate = 115200;

const int sharpPin = 21;
const int proxDotPin = 20;

RangeFinder rangeFinder;
HeartbeatLED heartbeat;
Metro rangeTimer = Metro(100);

void setup() {
	// initialize the digital pin as an output.
	Serial1.begin(serialBaudRate);
	Serial1.println("uCee Range Test");
	rangeFinder.begin(sharpPin, proxDotPin);
	heartbeat.begin(ledPin, 100, 900);
}

// the loop() methor runs over and over again,
// as long as the board has power

void loop() {
	heartbeat.update();
	if (rangeTimer.check()) {
		int distance = rangeFinder.getDistance();
		Serial1.print("Distance: ");
		Serial1.println(distance);
	}
}
