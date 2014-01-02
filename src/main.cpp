/* 
		uCee - a Micro Crawler Robot
*/

#include <Arduino.h>
#include <Metro.h>
#include "RangeFinder.h"
#include "HeartbeatLED.h"
#include "MotorDriver.h"
#include "main.h"

// Sensor and Actuator Objects
RangeFinder leftRangeFinder;
RangeFinder rightRangeFinder;
RangeFinder frontRangeFinder;
MotorDriver leftMotor = MotorDriver(leftEncoderAPin, leftEncoderBPin);
MotorDriver rightMotor = MotorDriver(rightEncoderAPin, rightEncoderBPin);

// Other Misc Objects
HeartbeatLED heartbeat;
Metro cycleTimer = Metro(100);

void setup() {
	Serial1.begin(serialBaudRate);
	Serial1.println("uCee Test");

	leftRangeFinder.begin(leftSharpPin, leftProxDotPin);
	rightRangeFinder.begin(rightSharpPin, rightProxDotPin);
	frontRangeFinder.begin(frontSharpPin, frontProxDotPin);

	leftMotor.begin(leftPwmPin, leftDirectionPin, leftEnablePin, leftCurrentPin);
	rightMotor.begin(rightPwmPin, rightDirectionPin, rightEnablePin, rightCurrentPin);
	
	heartbeat.begin(ledPin, 100, 900);
}

void loop() {
	heartbeat.update();
	if (cycleTimer.check()) {
		int range = rightRangeFinder.getDistance();
		int speed = range;
		if (speed < 0)
			speed = 200;
		rightMotor.setSpeed(speed);
		rightMotor.update();
		float current = rightMotor.getCurrent();
		Serial1.print("Current: ");
		Serial1.println(current * 1000);
	}
}
