#ifndef _BASE_LAYER_H__
#define _BASE_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include "../sqlUtils/DataUtils.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace std;
class BaseLayer :public Layer
{
public:
	bool init();
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void exitCallback(Ref *pSender);
	virtual void restartCallback(Ref *pSender);
	virtual void debugCallback(Ref *pSender);
	virtual void nextCallback(Ref *pSender);
	virtual void closeCaptureCallback(Ref *pSender, Widget::TouchEventType type);
	Size _visibleSize;
	Size _winSize;
	Size _orginSize;

	TextField *_text1;
	TextField *_text2;
	Sprite *capturedView;
	Button *closeImage;

	Menu *_menu;
	MenuItemImage *_item1;
	MenuItemImage *_item2;
	MenuItemImage *_item3;
	MenuItemImage *_item4;
};


#endif