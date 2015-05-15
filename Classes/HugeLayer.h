#ifndef HUGE_LAYER
#define HUGE_LAYER

#include "./base/BaseLayer.h"
#include "./GameOverScene.h"
#include "./TestFollow/RotateWithVeloc.h"
#include "JNI/JNIAlert.h"
class HugeLayer :public BaseLayer
{
public:
	static HugeLayer* create();
	virtual bool init() override;

	virtual void exitCallback(Ref *pSender);
	virtual void restartCallback(Ref *pSender);
	virtual void debugCallback(Ref *pSender);
	virtual void nextCallback(Ref *pSender);

	virtual void onEnter();
	virtual void onExit();
	
private:
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	virtual void onNativeCallback(int tag, NativeAlert::ButtonType type);
	virtual bool onContactBegin(const PhysicsContact &contact);
	virtual Sprite* createArrow();
	virtual void update(float delta);
	Sprite *back;
	Vec2 beginPoint;
	vector<Sprite*> allArrow;
	Sprite *fakeArrow;
};

#endif