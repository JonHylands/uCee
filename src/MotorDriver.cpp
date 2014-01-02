
#include <Arduino.h>
#include "MotorDriver.h"


MotorDriver::MotorDriver() {
}

void MotorDriver::begin(int pwmPin, int directionPin, int enablePin, int currentPin, int encoderAPin, int encoderBPin) {
	_pwmPin = pwmPin;
	_directionPin = directionPin;
	_enablePin = enablePin;
	_currentPin = currentPin;

	_encoderAPin = encoderAPin;
	_encoderBPin = encoderBPin;
// 	_motorEncoder = Encoder(_encoderAPin, _encoderBPin);

	_pidSetpoint = 0.0;
	_pidInput = 0.0;
// 	_motorPID = PID(&_pidInput, &_pidOutput, &pidSetpoint, pidKp, pidKi, pidKd, DIRECT);
	_motorPID..SetMode(AUTOMATIC);
	_encoderLastCount = 0;

	pinMode(_pwmPin, OUTPUT);
	pinMode(_directionPin, OUTPUT);
	pinMode(_enablePin, OUTPUT);
	digitalWrite(_pwmPin, LOW);
	digitalWrite(_directionPin, LOW); // enable active braking with LOW/LOW
	digitalWrite(_enablePin, HIGH);

	analogWriteFrequency(_pwmPin, motorPwmFrequency);
	analogWriteResolution(motorPwmResolution);
	analogWrite(_pwmPin, 0);

	pinMode(_currentPin, INPUT);
	_previousSpeed = 0;
}

/*=================================
 * 
 * 		MotorDriver::setSpeed
 * 
 * 		Set the desired speed, in mm/second.
 * 
 * ================================*/

void MotorDrive::setSpeed(int16_t speed) {
	_pidInput = (double)speed;
}

/*=================================
 * 
 * 		MotorDriver::update
 * 
 * 		Call this every 100 ms
 * 
 * ================================*/

void MotorDriver::update() {
	uint32_t currentCount = _motorEncoder.read();
	uint32_t deltaCount = currentCount - _encoderLastCount;
	_pidInput = (double)deltaCount * encoderToPidRatio;
	if (_motorPID.Compute()) {
		directSetSpeed(_pidOutput);
		_encoderLastCount = currentCount;
	} else {
		Serial1.println("PID Loop Fail");
	}
}

float MotorDriver::getCurrent() {
	int value = analogRead(_currentPin);
	return (float)value / motorCurrentFactor;
}

void MotorDriver::directSetSpeed(int16_t newSpeed) {
	if (newSpeed != _previousSpeed) {
		if (newSpeed >= 0) {
			digitalWrite(_directionPin, LOW);
			analogWrite(_pwmPin, newSpeed);
		} else {
			digitalWrite(_directionPin, HIGH);
			analogWrite(_pwmPin, 1023 + newSpeed);
		}
		_previousSpeed = newSpeed;
	}
}

