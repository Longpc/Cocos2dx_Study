#ifndef _JumpGame_SCENE_H__
#define _JumpGame_SCENE_H__

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
#include "sqlUtils\DataUtils.h"
#include "FlowerMouse.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocos2d::network;

class JumpGame : public cocos2d::Layer
{
public:
	JumpGame();
	~JumpGame();

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(JumpGame);

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


	virtual void backToGameOverScreen(Ref *pSender, Widget::TouchEventType type);
	virtual void touchJump(Ref *pSender, Widget::TouchEventType type);
	virtual void touchCreateLand(Ref *pSender, Widget::TouchEventType type);

	//virtual void jumRightAnimation(Sprite *sprite);
	//virtual void jumLeftAnimation(Sprite *sprite);


	//virtual void animationBird(Node *sprite);

	virtual void initLand(int offset);
	virtual Sprite* createLand();
	virtual void animationJUmper(Sprite *sprite);
	virtual void createStar(Vec2 position);
	//virtual void createBird();
	//virtual void resetBird(Sprite *sprite);
	//////VARIABLES//////////////////
	PhysicsWorld* _myWorld;

private:
	FlowerMouse *effectMouse;

	Size visibleSize;
	Vec2 position2;
	Sprite *back1;
	Sprite *back2;

	Sprite *jumper;
	Sprite *panda;
	Sprite *birdLeft;
	Sprite *birdRight;
	std::vector<Sprite *> allLand;

	float jumpOffset = 5;
	float jumpHigh = 300;
	float currentJump = 300;

	float maxLandNum = 20;
	float currenLandNum = 0;

	float backMaxChid = 10;
	float duration = 1;
	float yHigh = 100;

	float onLeft;
	bool canCreate = true;

	Vec2 birdLeftPos;
	Vec2 birdRightPos;
	Node* mouse;
	float mousecreated = false;
	std::unordered_map<int, Node*> _mouses;
};


#endif 
