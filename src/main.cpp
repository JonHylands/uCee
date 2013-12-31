/* 
		uCee - a Micro Crawler Robot
*/

#include <Arduino.h>
#include <Metro.h>
#include "RangeFinder.h"
#include "HeartbeatLED.h"
#include "MotorDriver.h"

// Teensy 3.1 has the LED on pin 13
const int ledPin = 13;
const int serialBaudRate = 115200;

const int sharpPin = 21;
const int proxDotPin = 20;

const int rightEnablePin = 7;
const int rightDirectionPin = 8;
const int rightPwmPin = 9;
const int leftPwmPin = 10;
const int leftDirectionPin = 11;
const int leftEnablePin = 12;

const int leftCurrentPin = 15;
const int rightCurrentPin = 14;

RangeFinder rangeFinder;
HeartbeatLED heartbeat;
Metro rangeTimer = Metro(100);
MotorDriver leftMotor;
MotorDriver rightMotor;

void setup() {
	// initialize the digital pin as an output.
	Serial1.begin(serialBaudRate);
	Serial1.println("uCee Range Test");
	rangeFinder.begin(sharpPin, proxDotPin);
	heartbeat.begin(ledPin, 100, 900);
	leftMotor.begin(leftPwmPin, leftDirectionPin, leftEnablePin, leftCurrentPin);
	rightMotor.begin(rightPwmPin, rightDirectionPin, rightEnablePin, rightCurrentPin);
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
