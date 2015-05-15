#ifndef _ROTATE_WITH_VELOC
#define _ROTATE_WITH_VELOC

#include <math.h>
#include "../base/BaseLayer.h"
#include "../GameOverScene.h"
#include "../HugeLayer.h"

class RotateWithVeloc : public BaseLayer
{
public:

	static Scene* createScene();
	CREATE_FUNC(RotateWithVeloc);
	bool init();
	virtual void setPhysicWorld(PhysicsWorld* world);
	virtual void update(float dt);

	virtual void restartCallback(Ref *pSender);
	virtual void exitCallback(Ref *pSender);
	virtual void debugCallback(Ref *pSender);
	virtual void nextCallback(Ref *pSender);
	virtual void onEnter();


private:
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	virtual Sprite* createNewArrow();
	virtual bool onContactBegin(const PhysicsContact &contact);
	virtual void fakeJointObject(PhysicsBody *bdA, PhysicsBody *bdB,Vec2 pos);
	virtual Vec2 caculatePos(Vec2 beforePos, float angle);

	PhysicsWorld  *_myWold;
	Sprite *_mySprite;
	//Node *spriteParent;
	vector<Sprite* > allArrow;
	
	Vec2 beginPoint;
	PhysicsJointPin * joint;

};

#endif