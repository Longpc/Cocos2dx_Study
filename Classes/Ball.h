/* Header for the Time class (Time.h) */
#include "cocos2d.h"
#include "GameOverScene.h"
USING_NS_CC;
using namespace std;
#ifndef BALL_H  
#define BALL_H   
//  this header will not get included more than once
class Ball {
private:  // private section
	// private data members
	//Sprite image
	Sprite* sprite;   
	//Image File Path
	char *filename;
	//Ball tag
	int tag;   
	//Ball name
	string name; 
	ccMenuCallback handler;
public:   // public section
	// public member function prototypes
	Ball(char *filename, int tag, string name);
	Sprite* getSprite() const;   
	int getTag() const; 
	void setTag1(int m); 
	string getName() const; 
	void setName(string name); 
	void setBall(char *filename, int tag, string name);
	void print() const; 
	void addEvent(const ccMenuCallback handler);
	void playCallback();
};  

#endif  // end of "#ifndef" block