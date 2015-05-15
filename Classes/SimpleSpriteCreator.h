#ifndef _SPRITE_CREATOR_H
#define _SPRITE_CREATOR_H

#include "cocos2d.h"

USING_NS_CC;
typedef std::function<void(Touch *touch, Event* event)> MyTouchEvent;
class SimpleSpriteCreator : public Sprite
{
public:
	SimpleSpriteCreator(void);
	virtual ~SimpleSpriteCreator(void);

	Rect getRect();
	bool initWithTexture(Texture2D* aTexture);
	bool initWithImage(char* file);
	virtual void onEnter() override;
	virtual void onExit() override;
	bool containsTouchLocation(Touch* touch);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);

	static SimpleSpriteCreator* createWithTexture(Texture2D* aTexture);
	static SimpleSpriteCreator* createWithImage(std::string filepath);
	virtual void addTouchEvent(MyTouchEvent touch);

	MyTouchEvent _touchEvent;
};

#endif
