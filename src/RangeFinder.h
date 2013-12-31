#ifndef RangerFinder_h
#define RangerFinder_h


class RangeFinder
{
public:
	RangeFinder();
	void begin(int rangePin, int proxDotPin);
	int getDistance();
private:
	int _rangePin;
	int _proxDotPin;
};

#endif // RangerFinder_h