#ifndef _TEST_FOLLOW_H__
#define _TEST_FOLLOW_H__
#include "base/BaseLayer.h"
#include "../GameOverScene.h"


class TestFollow :public BaseLayer
{
public:
	static Scene* createScene();
	virtual void exitCallback(Ref *pSender) override;
	virtual void restartCallback(Ref *pSender) override;
	virtual void debugCallback(Ref *pSender) override;
	CREATE_FUNC(TestFollow);
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual bool init();
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void touchCapture(Ref *pSender, Widget::TouchEventType type);
	virtual void afterCaptured(bool succeed, const string& outputFile);
private:
	Sprite *ball;
	Sprite *sprite;
	Button *captureScreen;
};



#endif


