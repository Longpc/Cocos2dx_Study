
#ifndef ___048__PopLayer__
#define ___048__PopLayer__

#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "SpriteSheetScene.h"
#include "GameOverScene.h"
USING_NS_CC;

class PopLayer : public LayerColor
{
public:
    static PopLayer* create(const Color4B& color,int offset);
    virtual bool initWithColor(const Color4B& color,int offset);
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
private:
    void onRestart(Ref* pSender);
    void onExit(Ref* pSender);
    void onContinue(Ref* pSender);
	int _offset;
};

#endif /* defined(___048__PopLayer__) */
