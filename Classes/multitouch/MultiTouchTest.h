#ifndef _MULTI_TOUCH_TEST_H
#define _MULTI_TOUCH_TEST_H

#include "../base/BaseLayer.h"
#include "../FlowerMouse.h"
#include "../GameOverScene.h"

#include "network/SocketIO.h"

#include "json/rapidjson.h"
#include "json/document.h"

#include <math.h>

using namespace cocos2d::network;
class MultiTouchTest :public BaseLayer, SocketIO::SIODelegate
{
public:
	virtual void onEnter() override;
	virtual void onExit() override;

	virtual void exitCallback(Ref *pSender) override;
	virtual void restartCallback(Ref *pSender) override;
	virtual void debugCallback(Ref *pSender) override;

	static Scene* createScene();
	CREATE_FUNC(MultiTouchTest);
	bool init();
	void setPhysicWorld(PhysicsWorld* world) {
		myWorld = world;
	}
	void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);

private:
	virtual void moveUnit();
	virtual void actionUnit();
	virtual void createMoveData();
	virtual void checkEnemy(SIOClient* client, const std::string& data);
	virtual bool onContactBegin(const PhysicsContact &contact);
	virtual void update(float delta);
	virtual void createParticleEffect(Vec2 pos);
	FlowerMouse *unit;
	Node *attackUnit;	
	vector<FlowerMouse*> allEnemyUnit;
	FlowerMouse *explosion;
	PhysicsWorld *myWorld;
	Vec2 beginTouchLeft;
	Vec2 beginTouchRight;
	Vec2 _savePos = Vec2::ZERO;

	float limitSpeed = 300;
	float minLength = 50;
	float enemyNum = 10;

	virtual void onConnect(SIOClient* client);
	virtual void onMessage(SIOClient* client, const std::string& data);
	virtual void onClose(SIOClient* client);
	virtual void onError(SIOClient* client, const std::string& data);

	SIOClient* _client;
};


#endif