#ifndef _TESTBOX2D_H__
#define _TESTBOX2D_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "Box2D\Box2D.h"
#include "extensions\cocos-ext.h"

#include "GameOverScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class TestBox2D : public cocos2d::Layer, public b2ContactListener
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	b2World *world;
	float deltaTime;



	Sprite *ball;
	bool existBall;
	float ballX;
	float ballY;
	int dragOffsetStartX;
	int dragOffsetEndX;
	int dragOffsetStartY;
	int dragOffsetEndY;
	float powerMultiplier;
	b2Body *ballBody;
	b2CircleShape ballShape;
	b2BodyDef ballBodyDef;

	

	void defineBall();
	void defineNode(Point);
	Mat4 _modelViewMV;
	CustomCommand _customCommand;
	Sprite *points[100];

	void addWall(float w, float h, float px, float py);
	void simulateTrajectory(b2Vec2 coord);

	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
	void onDraw();

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);


	void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(TestBox2D);
	virtual void clickBack(Ref *pSender, Widget::TouchEventType type);
};

#endif // __TestBox2D_SCENE_H__
