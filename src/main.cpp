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

RangeFinder leftRangeFinder;
RangeFinder rightRangeFinder;
RangeFinder frontRangeFinder;
HeartbeatLED heartbeat;
Metro rangeTimer = Metro(100);
MotorDriver leftMotor;
MotorDriver rightMotor;
Encoder leftEncoder = Encoder(leftEncoderAPin, leftEncoderBPin);
Encoder rightEncoder = Encoder(rightEncoderAPin, rightEncoderBPin);

void setup() {
	Serial1.begin(serialBaudRate);
	Serial1.println("uCee Test");

	leftRangeFinder.begin(leftSharpPin, leftProxDotPin);
	rightRangeFinder.begin(rightSharpPin, rightProxDotPin);
	frontRangeFinder.begin(frontSharpPin, frontProxDotPin);

	heartbeat.begin(ledPin, 100, 900);

	leftMotor.begin(leftPwmPin, leftDirectionPin, leftEnablePin, leftCurrentPin);
	rightMotor.begin(rightPwmPin, rightDirectionPin, rightEnablePin, rightCurrentPin);
}

void loop() {
	heartbeat.update();
	if (rangeTimer.check()) {
		int distance = rightRangeFinder.getDistance();
		int speed = distance;
		if (speed < 0)
			speed = 0;
		float motorSpeed = (float)speed / 200.0;
		leftMotor.setSpeed(motorSpeed);
		Serial1.print("Distance: ");
		Serial1.println(distance);
	}
}
