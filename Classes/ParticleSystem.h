#ifndef _ParticleSystemTest_SCENE_H__
#define _ParticleSystemTest_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"
#include "FlowerMouse.h"
#include "Define.h"
#include "GameOverScene.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocos2d::network;

class ParticleSystemTest : public cocos2d::Layer
{
public:
	ParticleSystemTest();
	~ParticleSystemTest();

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ParticleSystemTest);

	void setPhysicWorld(PhysicsWorld* world) {
		_myWorld = world;
	}
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);

	bool onContactBegin(const PhysicsContact &contact);

	virtual void onAccleration(Acceleration *pAccelerationValue, Event *event);

	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

	virtual void createSun(Vec2);
	virtual void createRain();
	virtual void createFire(Vec2);
	virtual void createFireworks(Vec2);
	virtual void createSmoke(Vec2);
	virtual void createExplotion(Vec2);
	virtual void createFlower(Vec2);
	virtual void createGalaxy(Vec2);
	virtual void createSnow();

	virtual void clickClean(Ref *pSender, Widget::TouchEventType type);
	virtual void clickBack(Ref *pSender, Widget::TouchEventType type);
	virtual void clickRain(Ref *pSender, Widget::TouchEventType type);
	virtual void clickSnow(Ref *pSender, Widget::TouchEventType type);
	virtual void switchCamera(Ref *pSender, Widget::TouchEventType type);
	void update(float dt);
	void back();

	//////VARIABLES//////////////////
	PhysicsWorld* _myWorld;

private:
	Size visibleSize;
};


#endif 
