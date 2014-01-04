
#include <Arduino.h>
#include "MotionController.h"


MotionController::MotionController(int leftEncoderAPin, int leftEncoderBPin, int rightEncoderAPin, int rightEncoderBPin)
: 	_leftMotorDriver(int leftEncoderAPin, int leftEncoderBPin),
	_rightMotorDriver(int rightEncoderAPin, int rightEncoderBPin) {
}

void MotionController::setupLeftMotor(int pwmPin, int directionPin, int enablePin, int currentPin) {
	_leftMotorDriver.begin(int pwmPin, int directionPin, int enablePin, int currentPin);
	_leftMotorDesiredSpeed = 0;
}

void MotionController::setupRightMotor(int pwmPin, int directionPin, int enablePin, int currentPin) {
	_rightMotorDriver.begin(int pwmPin, int directionPin, int enablePin, int currentPin);
	_rightMotorDesiredSpeed = 0;
}

void MotionController::setDesiredSpeed(float speed) {
	_leftMotorDesiredSpeed = (uint16_t)(speed * 1023.0);
	_rightMotorDesiredSpeed = (uint16_t)(speed * 1023.0);
}

void MotionController::setDesiredTurnRate(float turnRate) {

}

void MotionController::update() {
	_leftMotorDriver.setDesiredSpeed(_leftMotorDesiredSpeed);
	_leftMotorDriver.update();
	_rightMotorDriver.setDesiredSpeed(_rightMotorDesiredSpeed);
	_rightMotorDriver.update();
}
