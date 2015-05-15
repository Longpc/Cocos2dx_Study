#ifndef _CustomScroll_SCENE_H__
#define _CustomScroll_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "network/HttpClient.h"

#include "Define.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "ThumbLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocos2d::network;

class CustomScroll : public cocos2d::Layer, extension::ScrollViewDelegate
{
public:
	CustomScroll();
	~CustomScroll();

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(CustomScroll);

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

	virtual void backToGameOverScreen(Ref *pSender, Widget::TouchEventType type);
	virtual void clickToReset(Ref *pSEnder, Widget::TouchEventType type);
	virtual void clickMove1(Ref *pSender, Widget::TouchEventType type);
	virtual void clickScale1(Ref *pSender, Widget::TouchEventType type);

	virtual void toLeftAnimation(Sprite *sprite);
	virtual void toRightAnimation(Sprite *sprite);
	virtual void leftToMid(Sprite *sprite);
	virtual void rightToMid(Sprite *sprite);
	virtual void move1(Sprite *sprite);
	virtual void scale1(Sprite *sprite);
	
	virtual void resetAll(Sprite *sprite);
	void update(float dt);

	//////VARIABLES//////////////////
	PhysicsWorld* _myWorld;

private:
	Size visibleSize;
	Vec2 beginPoint;
	Vec2 currentPoint;
	extension::ScrollView *myScrollView;
	Sprite *baseSprite;
	Layer *layer1;
	Layer *layer2;
	Layer *layer3;
	Layer *layer4;
	Layer *layer5;
	bool call1 = false;
	bool call2 = false;
	Vec2 pos1;
	Vec2 pos2;
	Vec2 pos3;
	Vec2 pos4;
	Vec2 pos5;
	
};


#endif 
