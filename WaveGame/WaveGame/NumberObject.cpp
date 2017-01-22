#include "NumberObject.h"
#include "RenderControl.h"
#include <vector>

extern RenderControl renderController;

NumberObject::NumberObject(Point middle, int digitMax, int initialValue)
	: BaseObject(middle, Sprite(0, 0, 0), digitMax*40, 40 )
{
	setDigitMax(digitMax);
	setValue(initialValue);
}

NumberObject::NumberObject(const NumberObject & rhs)
	: BaseObject(rhs.middle, rhs.s, rhs.width, rhs.height)
{
	setDigitMax(rhs.digitMax);
	setValue(rhs.value);
}

void NumberObject::setDigitMax(int digitMax)
{
	this->digitMax = digitMax;
	this->width = digitMax * 40;
	digits = vector<GlyphObject>();
	for (int i = 0; i < digitMax; i++) {
		GlyphObject go(Point(digitMax * 40 / 2 + middle.x - 20 - ((i - 1) * 40), middle.y), 0);
		digits.push_back(go);
	}
}

void NumberObject::setValue(int value)
{
	if (value < 0) {
		value = 0;
	}
	else if (value > getMaxValue()) {
		value = getMaxValue();
	}
	this->value = value;
	int initialMod = 10;
	int curVal = value;
	int curNumeral;
	for (int i = 0; i < digitMax; i++) {
		curNumeral = curVal%initialMod/(initialMod/10);
		curVal -= curNumeral*(10*(i-1));
		initialMod *= 10;
		digits[i].setNum(curNumeral);
		//cout << "Digit " << i << " set to " << curNumeral << endl;
	}
}

void NumberObject::addValue(int value)
{
	setValue(this->value + value);
}

int NumberObject::getValue()
{
	return this->value;
}

int NumberObject::getMaxValue()
{
	int max = 0;
	for (int i = digitMax; i > 0; i--) {
		max += int(pow(10, i-1)) * 9;
	}
	return max;
}

int NumberObject::getDigitMax()
{
	return digitMax;
}

void NumberObject::think()
{
	//Not much
}

void NumberObject::draw()
{
	for (int i = 0; i < digits.size(); i++) {
		digits[i].draw();
	}
}

Sprite &NumberObject::getSpriteFor(int numeral)
{
	switch (numeral) {
	case 0:
		return renderController.get("0");
	case 1:
		return renderController.get("1");
	case 2:
		return renderController.get("2");
	case 3:
		return renderController.get("3");
	case 4:
		return renderController.get("4");
	case 5:
		return renderController.get("5");
	case 6:
		return renderController.get("6");
	case 7:
		return renderController.get("7");
	case 8:
		return renderController.get("8");
	case 9:
		return renderController.get("9");
	}
}

NumberObject::GlyphObject::GlyphObject(Point middle, int initialNum)
	: num(initialNum), BaseObject(middle, NumberObject::getSpriteFor(initialNum), 38, 38)
{
	angle = 0;
}

NumberObject::GlyphObject::GlyphObject(const GlyphObject & glyph)
	: num(glyph.num), BaseObject(glyph.middle, glyph.s, glyph.width, glyph.height)
{
	angle = glyph.angle;
}

void NumberObject::GlyphObject::setNum(int num)
{
	this->num = num;
	this->s = NumberObject::getSpriteFor(num);
}

int NumberObject::GlyphObject::getNum()
{
	return num;
}

void NumberObject::GlyphObject::think()
{
}
