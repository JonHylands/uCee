#ifndef MotionController_h
#define MotionController_h

#include <MotorDriver.h>

class MotionController {

public:
	MotionController(int leftEncoderAPin, int leftEncoderBPin, int rightEncoderAPin, int rightEncoderBPin);
	void setupLeftMotor(int pwmPin, int directionPin, int enablePin, int currentPin);
	void setupRightMotor(int pwmPin, int directionPin, int enablePin, int currentPin);
	void setDesiredSpeed(float speed);
	void setDesiredTurnRate(float turnRate);
	void update();

private:
	uint16_t _leftMotorDesiredSpeed;
	uint16_t _rightMotorDesiredSpeed;
	float _desiredSpeed;
	float _desiredTurnRate;
	MotorDriver _leftMotorDriver;
	MotorDriver _rightMotorDriver;
};

#endif // MotionController_h
