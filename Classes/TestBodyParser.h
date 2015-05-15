#ifndef __BODY_SCENE_H__
#define __BODY_SCENE_H__
#include "cocos2d.h"
#include "Define.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "MyBodyParser.h"
#include "Ball.h"
USING_NS_CC;
using namespace std;
class BodyTestScene :public Layer
{
public:
	BodyTestScene();
	~BodyTestScene();
	PhysicsWorld* _myWorld;
	Sprite* _ball;
	Sprite* _screenBolder;
	static Scene* createScene();
	static BodyTestScene* create();
	virtual bool init();
	void update(float) override;
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
	void setPhysicWorld(PhysicsWorld* world) {
		_myWorld = world;
	}
	bool onContactBegin(const PhysicsContact &contact);
	void createBall(Vec2 point);
	virtual void onAccleration(Acceleration *pAccelerationValue, Event *event);
	void btnDebugDrawCallback(Ref *pSender);
	void toggleOfDebugDraw();
private:
	Sprite* _backButton;
	Sprite* _testSprite;
	Size size;
	float _moveSpeedX = 200;
	float _moveSpeedY = 200;
};


#endif