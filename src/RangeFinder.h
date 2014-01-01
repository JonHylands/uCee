#ifndef RangerFinder_h
#define RangerFinder_h

/*=========================
 * 
 * 		RangerFinder
 * 
 *		RangeFinder is a class to support the
 * 		combination of a GP2Y0A41SK0F and
 * 		a ProxDot.
 * 
 * ========================*/

class RangeFinder {

public:
	RangeFinder();
	void begin(int rangePin, int proxDotPin);
	int getDistance();

private:
	int _rangePin;
	int _proxDotPin;
};

#endif // RangerFinder_h
