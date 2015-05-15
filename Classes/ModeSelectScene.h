#ifndef _MODE_CHOOSE11__
#define _MODE_CHOOSE11__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui\CocosGUI.h"

#include "SpriteSheetScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class ModeSelect : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	static ModeSelect* create();
	
	virtual void clickStart(Ref *pSender, Widget::TouchEventType type);
private:
	Button* startButton;
	CheckBox* modeEasy;
	virtual void easyChooseListenr(Ref* pSender, CheckBox::EventType type);
	CheckBox* modeNormal;
	virtual void normalChooseListenr(Ref* pSender, CheckBox::EventType type);
	CheckBox* modeHard;
	virtual void hardChooseListenr(Ref* pSender, CheckBox::EventType type);

	CheckBox* fruitMode;
	virtual void fruitChooseListenr(Ref* pSender, CheckBox::EventType type);
	CheckBox* bearMode;
	virtual void bearChooseListenr(Ref* pSender, CheckBox::EventType type);

	//4 for EASY, 5 for NORMAL, 6 for HARD
	int gameLevel; 
	//set: 1 for FRUIT UI and 2 for BEAR UI
	int gameUIMode;
};

#endif