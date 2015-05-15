#include "DataUtils.h"


std::string DataUtils::numberToString(float number)
{
	std::stringstream text;
	text << number;
	return text.str().c_str();
}

float DataUtils::stringToFloat(const string str)
{
	stringstream ss(str);
	float result;
	return ss >> result ? result : 0;
}

char* DataUtils::MultiByteToUTF8(const char* src)
{
	/*unsigned int sizeWide = MultiByteToWideChar(0, 0, src, -1, nullptr, 0);
	wchar_t* bufferWide = new wchar_t[sizeWide + 1]();
	MultiByteToWideChar(0, 0x00000001, src, -1, bufferWide, sizeWide);
	unsigned int sizeUtf8 = WideCharToMultiByte(65001, 0, bufferWide, -1, nullptr, 0, nullptr, nullptr);
	char* bufferUtf8 = new char[sizeUtf8 + 1]();
	WideCharToMultiByte(65001, 0, bufferWide, -1, bufferUtf8, sizeUtf8, nullptr, nullptr);
	delete bufferWide;
	return bufferUtf8;*/
	return NULL;
}

float DataUtils::randomBetween(float min, float max)
{
	int off = 1000;
	int minOff = min * off;
	int maxOff = max * off;
	srand(time(NULL));
	return (rand() % (maxOff - minOff) + minOff)/off;
}

float DataUtils::radianToDegree(float radian)
{
	#define PI 3.14159265
	return radian * 180 / PI;
}
