#ifndef MotorDriver_h
#define MotorDriver_h

#include <Encoder.h>
#include <PID_v1.h>

const int motorPwmFrequency = 10000;
const int motorPwmResolution = 10;
const int motorPwmFactor = 1023;
const float motorCurrentFactor = 1023.0;

const double pidKp = 2.0;
const double pidKi = 5.0;
const double pidKd = 1.0;

const double encoderToPidRatio = 1.948;

class MotorDriver {

public:
	MotorDriver();
	void begin(int pwmPin, int directionPin, int enablePin, int currentPin, int encoderAPin, int encoderBPin);
	void setSpeed(int16_t speed);
	void update();
	float getCurrent();

private:
	int _pwmPin;
	int _directionPin;
	int _enablePin;
	int _currentPin;
	int _previousSpeed;
	PID _motorPID = PID(&_pidInput, &_pidOutput, &_pidSetpoint, pidKp, pidKi, pidKd, DIRECT);
	double _pidSetpoint;
	double _pidInput;
	double _pidOutput;
	Encoder _motorEncoder = Encoder(_encoderAPin, _encoderBPin);
	int _encoderAPin;
	int _encoderBPin;
	uint32_t _encoderLastCount;
	void directSetSpeed(int16_t speed);
};

#endif // MotorDriver_h
