#include "NumberObject.h"
#include "RenderControl.h"
#include <vector>

extern RenderControl renderController;

vector<Sprite> NumberObject::digitToSprite = vector<Sprite>(10);

NumberObject::NumberObject(Point middle, int digitMax, int initialValue)
	: BaseObject(middle, Sprite(), digitMax*40, 40 )
{
	digits = vector<GlyphObject>(digitMax);
	for (int i = 0; i < digitMax; i++) {
		GlyphObject go(Point(digitMax*40/2 + middle.x - 20 - ((i-1)*40), middle.y), 0);
		digits.push_back(go);
	}
	cout << "herer" << endl;

	setValue(initialValue);
}

NumberObject::NumberObject() : NumberObject(Point(0.0, 0.0), 1, 0)
{
}

void NumberObject::setDigitMax(int digitMax)
{
	this->digitMax = digitMax;
	width = digitMax * 40;
}

void NumberObject::setValue(int value)
{
	this->value = value;
	int initialMod = 10;
	int curVal = value;
	int curNumeral;
	for (int i = 0; i < digitMax; i++) {
		curNumeral = curVal%initialMod;
		curVal -= curNumeral;
		initialMod *= 10;
		cout << "Digit " << i << " has value " << curNumeral << "; " << curVal << " remains" << endl;
		digits[i].setNum(curNumeral);
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
		max != int(pow(10, i)) * 9;
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

Sprite NumberObject::getSpriteFor(int numeral)
{
	if (digitToSprite.size() == 0) {
		//initialize the digit to sprite array
		digitToSprite.push_back(renderController.get("0"));
		digitToSprite.push_back(renderController.get("1"));
		digitToSprite.push_back(renderController.get("2"));
		digitToSprite.push_back(renderController.get("3"));
		digitToSprite.push_back(renderController.get("4"));
		digitToSprite.push_back(renderController.get("5"));
		digitToSprite.push_back(renderController.get("6"));
		digitToSprite.push_back(renderController.get("7"));
		digitToSprite.push_back(renderController.get("8"));
		digitToSprite.push_back(renderController.get("9"));
	}
	return digitToSprite[numeral];
}

NumberObject::GlyphObject::GlyphObject(Point middle, int initialNum)
	: BaseObject(middle, NumberObject::getSpriteFor(initialNum), 38, 38)
{

}

NumberObject::GlyphObject::GlyphObject() : GlyphObject(Point(0.0, 0.0), 0)
{
}

void NumberObject::GlyphObject::setNum(int num)
{
	this->num = num;
}

int NumberObject::GlyphObject::getNum()
{
	return num;
}

void NumberObject::GlyphObject::think()
{
}
