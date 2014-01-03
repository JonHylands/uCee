#ifndef MotorDriver_h
#define MotorDriver_h

#include <Encoder.h>
#include <PID_v1.h>

const int motorPwmFrequency = 10000;
const int motorPwmResolution = 10;
const int motorPwmFactor = 1023;
const float motorCurrentFactor = 1023.0;

const double pidKp = 0.25;
const double pidKi = 0.75;
const double pidKd = 0.01;

const double encoderToPidRatio = 0.487;

class MotorDriver {

public:
	MotorDriver(int encoderAPin, int encoderBPin);
	void begin(int pwmPin, int directionPin, int enablePin, int currentPin);
	void setDesiredSpeed(int16_t speed);
	void setPID(uint16_t p, uint16_t i, uint16_t d);
	void displayEncoder();
	void update();
	float getCurrent();

private:
	int _pwmPin;
	int _directionPin;
	int _enablePin;
	int _currentPin;
	int _previousSpeed;
	PID _motorPID; // = PID(&_pidInput, &_pidOutput, &_pidSetpoint, pidKp, pidKi, pidKd, DIRECT);
	double _pidSetpoint;
	double _pidInput;
	double _pidOutput;
	Encoder _motorEncoder; //  = Encoder(_encoderAPin, _encoderBPin);
	uint32_t _encoderLastCount;
	void directSetSpeed(int16_t speed);
};

#endif // MotorDriver_h
