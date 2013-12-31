
#include <Arduino.h>
#include "MotorDriver.h"


MotorDriver::MotorDriver()
{
}

void MotorDriver::begin(int pwmPin, int directionPin, int enablePin, int currentPin)
{
	_pwmPin = pwmPin;
	_directionPin = directionPin;
	_enablePin = enablePin;
	_currentPin = currentPin;

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

void MotorDriver::setSpeed(float speed)
{
	int newSpeed = (int)(speed * motorPwmFactor);
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

float MotorDriver::getCurrent()
{
	int value = analogRead(_currentPin);
	return (float)value / motorCurrentFactor;
}
