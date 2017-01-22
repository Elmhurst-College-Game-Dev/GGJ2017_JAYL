#pragma once

#include "BaseObject.h"

//For drawing text (currency, wave counter, etc)

class NumberObject : public BaseObject {
public:
	NumberObject(Point middle, int digitMax, int initialValue);
	NumberObject(const NumberObject &rhs);
	NumberObject() = delete;
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
		GlyphObject(const GlyphObject &glyph);
		GlyphObject() = delete;
		void setNum(int num); //0-9
		int getNum();
		void think() override;
	private:
		int num;
	};

	static Sprite &getSpriteFor(int numeral);

private:
	int digitMax;
	int value;
	vector<GlyphObject> digits;
};