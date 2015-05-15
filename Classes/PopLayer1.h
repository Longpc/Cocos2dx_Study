#ifndef ___PopLayer__
#define ___PopLayer__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui\CocosGUI.h"

#include "Define.h"
#include "GameOverScene.h"
#include "SpriteSheetScene.h"
#include "HightScoreScene.h"
#include "ModeSelectScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
class PopLayer1 : public LayerColor
{
public:
    static PopLayer1* create(const Color4B& color,int score);
    virtual bool initWithColor(const Color4B& color,int score);
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void textFieldEvent(Ref *pSender, TextField::EventType type);
	virtual void savename(Ref *pSender, Widget::TouchEventType type);
	virtual void update(float dt) override;
	virtual void onExitTransitionDidStart();
private:
    void onRestart(Ref* pSender);
    void onExit(Ref* pSender);
	void onHighScore(Ref* pSender);
	int userScore;
	int topScore;
	TextField* nameInput;
	Button* saveButton;
	

};

#endif 
