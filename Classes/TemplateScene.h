#ifndef _TEMPLATE_SCENE_H__
#define _TEMPLATE_SCENE_H__

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

class Template : public cocos2d::Layer
{
public:
	Template();
	~Template();

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Template);

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

	//////VARIABLES//////////////////
	PhysicsWorld* _myWorld;

private:
	Size visibleSize;
};


#endif 
