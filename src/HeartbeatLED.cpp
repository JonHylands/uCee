
#include <Arduino.h>
#include "HeartbeatLED.h"


HeartbeatLED::HeartbeatLED()
{
	_ledPin = -1;
	_onInterval = 100;
	_offInterval = 900;
	_ledState = LOW;
}

void HeartbeatLED::begin(int ledPin, int onInterval, int offInterval)
{
	_ledPin = ledPin;
	pinMode(_ledPin, OUTPUT);
	_onInterval = onInterval;
	_offInterval = offInterval;
	_ledTimer.interval(_offInterval);
	_ledState = LOW;
	digitalWrite(_ledPin, _ledState);
}

void HeartbeatLED::update()
{
	if (_ledTimer.check()) {
		if (_ledState == HIGH) {
			_ledState = LOW;
			if (_onInterval != _offInterval)
				_ledTimer.interval(_offInterval);
		} else {
			_ledState = HIGH;
			if (_onInterval != _offInterval)
				_ledTimer.interval(_onInterval);
		}
		digitalWrite(_ledPin, _ledState);
	}
}
