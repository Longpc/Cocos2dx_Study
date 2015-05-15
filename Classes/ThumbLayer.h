
#ifndef ___THUMB_LAYER__
#define ___THUMB_LAYER__

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "SpriteSheetScene.h"
#include "GameOverScene.h"
USING_NS_CC;

class ThumbLayer : public LayerColor
{
public:
	static ThumbLayer* create(const Color4B& color);
	virtual bool initWithColor(const Color4B& color);

	virtual void setThumb(string filepath);
	virtual void setText(string name);
	virtual void setTextSize(int size);
	virtual void setTColor(Color4B color);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
private:
	Text *text;
};

#endif 