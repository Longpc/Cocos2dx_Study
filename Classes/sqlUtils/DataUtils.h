#ifndef _DATA_UTILS_H__
#define _DATA_UTILS_H__

#include <stdlib.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
class DataUtils
{
public:
	/*
	convert number to string
	@number float : number to convert into a string
	Return: a string
	*/
	static string numberToString(float number);
	/*Convert string containing the number to number
	@str string: string containing the number
	Return: the number if it was contained by inputted string or default value = 0
	*/
	static float stringToFloat(const string str);
	/*
	
	*/
	static char* MultiByteToUTF8(const char* src);

	static float randomBetween(float min, float max);

	/*
	@Convert Angle from Radian to Degree
	Input: Value in Radian, Output Value in Degree
	*/
	static float radianToDegree(float radian);
};

#endif