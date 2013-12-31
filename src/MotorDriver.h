#ifndef MotorDriver_h
#define MotorDriver_h

const int motorPwmFrequency = 10000;
const int motorPwmResolution = 10;
const int motorPwmFactor = 1023;
const float motorCurrentFactor = 1023.0;

class MotorDriver
{
public:
	MotorDriver();
	void begin(int pwmPin, int directionPin, int enablePin, int currentPin);
	void setSpeed(float speed);
	float getCurrent();
private:
	int _pwmPin;
	int _directionPin;
	int _enablePin;
	int _currentPin;
	int _previousSpeed;
};

#endif // MotorDriver_h
