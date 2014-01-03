
#include <Arduino.h>
#include "MotorDriver.h"


MotorDriver::MotorDriver(int encoderAPin, int encoderBPin)
: 	_motorPID(&_pidInput, &_pidOutput, &_pidSetpoint, pidKp, pidKi, pidKd, DIRECT),
	_motorEncoder(encoderAPin, encoderBPin) {
}

void MotorDriver::begin(int pwmPin, int directionPin, int enablePin, int currentPin) {
	_pwmPin = pwmPin;
	_directionPin = directionPin;
	_enablePin = enablePin;
	_currentPin = currentPin;

	_pidSetpoint = 0.0;
	_pidInput = 0.0;
	_motorPID.SetMode(AUTOMATIC);
	_motorPID.SetOutputLimits(0, 1023);
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
 * 		MotorDriver::setDesiredSpeed
 * 
 * 		Set the desired speed, in mm/second.
 * 
 * ================================*/

void MotorDriver::setDesiredSpeed(int16_t speed) {
	_pidSetpoint = (double)speed;
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
		Serial1.print("PID Output: ");
		Serial1.print(_pidOutput);
		directSetSpeed(_pidOutput);
		Serial1.print(" - PID Input: ");
		Serial1.println(_pidInput);
		_encoderLastCount = currentCount;
	} else {
		Serial1.println("PID Loop Fail");
	}
}

void MotorDriver::displayEncoder() {
	Serial1.println(_motorEncoder.read());
}

void MotorDriver::setPID(uint16_t p, uint16_t i, uint16_t d) {
	double kp = (double)p / 1023.0 * 5;
	double ki = (double)i / 1023.0 * 5;
	double kd = (double)d / 1023.0 * 5;
// 	Serial1.print("p: ");
// 	Serial1.print(kp);
// 	Serial1.print(" - i: ");
// 	Serial1.print(ki);
// 	Serial1.print(" - d: ");
// 	Serial1.println(kd);
	_motorPID.SetTunings(kp, ki, kd);
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

