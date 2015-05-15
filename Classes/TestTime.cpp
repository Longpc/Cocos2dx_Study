/* Implementation for the Time Class (Time.cpp) */
#include "cocos2d.h"
#include <iostream>
#include <iomanip>
#include "TestTime.h"    // include header of Time class
using namespace std;
USING_NS_CC;
// Constructor with default values. No input validation
Time::Time(int h, int m, int s) {
	hour = h;
	minute = m;
	second = s;
}

// public getter for private data member hour
int Time::getHour() const {
	return hour;
}

// public setter for private data member hour. No input validation
void Time::setHour(int h) {
	hour = h;
}

// public getter for private data member minute
int Time::getMinute() const {
	return minute;
}

// public setter for private data member minute. No input validation
void Time::setMinute(int m) {
	minute = m;
}

// public getter for private data member second
int Time::getSecond() const {
	return second;
}

// public setter for private data member second. No input validation
void Time::setSecond(int s) {
	second = s;
}

// Set hour, minute and second. No input validation
void Time::setTime(int h, int m, int s) {
	hour = h;
	minute = m;
	second = s;
}

// Print this Time instance in the format of "hh:mm:ss", zero filled
void Time::print() const {
	cocos2d::log("%d : %d : %d", hour, minute, second);
}

// Increase this instance by one second
void Time::nextSecond() {
	++second;
	if (second >= 60) {
		second = 0;
		++minute;
	}
	if (minute >= 60) {
		minute = 0;
		++hour;
	}
	if (hour >= 24) {
		hour = 0;
	}
}