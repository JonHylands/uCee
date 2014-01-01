#ifndef HeartbeatLED_h
#define HeartbeatLED_h

#include <Metro.h>

class HeartbeatLED {

public:
	HeartbeatLED();
	void begin(int ledPin, int onInterval, int offInterval);
	void update();
	void end();

private:
	int _ledPin;
	int _onInterval;
	int _offInterval;
	int _ledState;
	Metro _ledTimer = Metro(1000);
};

#endif // HeartbeatLED_h
