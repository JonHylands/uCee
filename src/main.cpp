/* 
		uCee - a Micro Crawler Robot
*/

#include <Arduino.h>
#include <Metro.h>
#include "RangeFinder.h"
#include "HeartbeatLED.h"
#include "MotorDriver.h"
#include "main.h"

RangeFinder rangeFinder;
HeartbeatLED heartbeat;
Metro rangeTimer = Metro(100);
MotorDriver leftMotor;
MotorDriver rightMotor;

void setup() {
	Serial1.begin(serialBaudRate);
	Serial1.println("uCee Test");
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
