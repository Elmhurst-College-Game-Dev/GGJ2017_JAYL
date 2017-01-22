#pragma once

#include "BaseObject.h"

//For drawing text (currency, wave counter, etc)

class NumberObject : public BaseObject {
public:
	NumberObject(Point middle, int digitMax, int initialValue);
	NumberObject();
	void setDigitMax(int digitMax);
	void setValue(int value);
	void addValue(int value);
	int getValue();
	int getMaxValue();
	int getDigitMax();
	void think() override;
	void draw() override;
protected:
	class GlyphObject : public BaseObject {
	public:
		GlyphObject(Point middle, int initialNum);
		GlyphObject();
		void setNum(int num); //0-9
		int getNum();
		void think() override;
	private:
		int num;
	};

	static vector<Sprite> digitToSprite;
	static Sprite getSpriteFor(int numeral);
private:
	int digitMax;
	int value;
	vector<GlyphObject> digits;
};