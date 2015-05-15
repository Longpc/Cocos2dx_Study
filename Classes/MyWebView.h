#ifndef _WEBVIEW_H__
#define _WEBVIEW_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

#include "network/HttpClient.h"
#include "Define.h"
#include "GameOverScene.h"
#include "SimpleSpriteCreator.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
using namespace cocos2d::ui;
using namespace cocos2d::network;

typedef std::unordered_map<string, string> MyMap;

class MyWeb : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MyWeb);
protected:
private:
	virtual void clickBack(Ref *pSender, Widget::TouchEventType type);
	virtual void testTouchEvent(Touch *touch, Event* event);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onEnter();
	Size visibleSize;
	ParticleSystemQuad *test;
};
#endif