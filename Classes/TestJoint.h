#ifndef _TestJoint_SCENE_H__
#define _TestJoint_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"

#include "Define.h"
#include "InfoLayer.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "MyBodyParser.h"
#include "PopLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocos2d::network;

const PhysicsMaterial MASTERIAL(10.0f, 0.4f, 1.0f);

class TestJoint : public cocos2d::Layer
{
public:
	TestJoint();
	~TestJoint();

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(TestJoint);

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

	void update(float dt);

	virtual void clickBack(Ref *pSender, Widget::TouchEventType type);
	virtual void addSprite(int offset);

	//////VARIABLES//////////////////
	PhysicsWorld* _myWorld;

private:
	Node* mouse;
	Size visibleSize;
};


#endif 
