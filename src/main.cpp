/* 
		uCee - a Micro Crawler Robot
*/

#include <Arduino.h>
#include <Metro.h>
#include <Encoder.h>
#include "RangeFinder.h"
#include "HeartbeatLED.h"
#include "MotorDriver.h"
#include "main.h"

// Sensor and Actuator Objects
RangeFinder leftRangeFinder;
RangeFinder rightRangeFinder;
RangeFinder frontRangeFinder;
MotorDriver leftMotor;
MotorDriver rightMotor;
Encoder leftEncoder = Encoder(leftEncoderAPin, leftEncoderBPin);
Encoder rightEncoder = Encoder(rightEncoderAPin, rightEncoderBPin);

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
		int distance = rightRangeFinder.getDistance();
		int speed = distance;
		if (speed < 0)
			speed = 200;
		float motorSpeed = (float)speed / 200.0;
		leftMotor.setSpeed(motorSpeed);
		Serial1.print("Distance: ");
		Serial1.println(distance);
	}
}
