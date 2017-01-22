#pragma once

#include "BaseObject.h"

//For drawing text (currency, wave counter, etc)

class NumberObject : public BaseObject {
public:
	NumberObject(int digitMax, int initialValue);
	void setDigitMax(int digitMax);
	void setValue(int value);
	void addValue(int value);
	int getValue();
	int getDigitMax();
private:
	int digitMax;
	int value;
};