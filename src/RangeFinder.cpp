
#include <Arduino.h>
#include "RangeFinder.h"


RangeFinder::RangeFinder() {
	_rangePin = -1;
	_proxDotPin = -1;
}

void RangeFinder::begin(int rangePin, int proxDotPin) {
	_rangePin = rangePin;
	pinMode(_rangePin, INPUT);

	_proxDotPin = proxDotPin;
	pinMode(_proxDotPin, INPUT);
}

int RangeFinder::getDistance() {
	if ((_rangePin == -1) || (_proxDotPin == -1)) {
		return -2;
	}
	int value = analogRead(_rangePin);
	float voltage = value * 0.0032258; // 0-1023 -> 0-3.3 volts
	float exactDistance = (100 * ((1.25 / voltage) - 0.15));
	int distance = (int)exactDistance;
	int proxDot = digitalRead(_proxDotPin); // ProxDots read active low
	if ((distance > 200) && proxDot) { // if both sensors read nothing close
		return -1;
	}
	if (!proxDot) {
		distance = max(0, 55 - distance);
	}
	return distance;
}
