#include "RotateWithVeloc.h"
#define LINE 1
#define LAND 2
#define ARROW 3
#define OBJECTTAG 4
#define WALLTAG 5
#define LAYER 0
Scene* RotateWithVeloc::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, -1000));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = RotateWithVeloc::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	layer->setTag(LAYER);
	scene->addChild(layer);
	return scene;
}

bool RotateWithVeloc::init()
{
	if (!BaseLayer::init()) {
		return false;
	}
	
	//_mySprite = createNewArrow();
	//_mySprite->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
	//allArrow.push_back(_mySprite);
	//spriteParent->addChild(allArrow.back(), 100);

	

	return true;
}

void RotateWithVeloc::setPhysicWorld(PhysicsWorld* world)
{
	_myWold = world;
}
void RotateWithVeloc::onEnter()
{
	BaseLayer::onEnter();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(RotateWithVeloc::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(RotateWithVeloc::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(RotateWithVeloc::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(RotateWithVeloc::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	Vec2 vec[2] = {
		Vec2(-100, 100),
		Vec2(_visibleSize.width + 100, 100)
	};

	auto land = Node::create();
	land->setPhysicsBody(PhysicsBody::createBox(Size(_visibleSize.width * 2, 100), PhysicsMaterial(1, 0, 0)));
	land->setPosition(Vec2::ZERO);
	land->getPhysicsBody()->setGravityEnable(false);
	land->getPhysicsBody()->setDynamic(false);
	land->getPhysicsBody()->setContactTestBitmask(0x1);
	land->setTag(LAND);
	addChild(land);
	auto wall = Node::create();
	wall->setPosition(Vec2(_visibleSize.width, _visibleSize.height/2));
	wall->setPhysicsBody(PhysicsBody::createBox(Size(50, _visibleSize.height), PhysicsMaterial(1, 0, 0)));
	wall->getPhysicsBody()->setDynamic(false);
	wall->getPhysicsBody()->setContactTestBitmask(0x1);
	wall->getPhysicsBody()->setGravityEnable(false);
	wall->setTag(WALLTAG);
	addChild(wall);

	auto line = Sprite::create("line.png");
	line->setPosition(Vec2(550, 750));
	line->setPhysicsBody(PhysicsBody::createBox(Size(10, 150), PhysicsMaterial(0, 0, 0)));
	line->getPhysicsBody()->setGravityEnable(false);
	line->getPhysicsBody()->setDynamic(false);
	line->getPhysicsBody()->setContactTestBitmask(0x1);
	line->setTag(LINE);
	addChild(line);

	auto obj = Sprite::create("ball.png");
	obj->setPhysicsBody(PhysicsBody::createCircle(obj->getContentSize().width / 2, PhysicsMaterial(100, 0, 0)));
	obj->getPhysicsBody()->setContactTestBitmask(0x1);
	obj->setTag(OBJECTTAG);
	obj->setPosition(line->getPosition() - Vec2(0, 100));
	addChild(obj,200);

	joint = PhysicsJointPin::construct(line->getPhysicsBody(), obj->getPhysicsBody(), line->getPosition() - Vec2(0, 50));
	joint->setCollisionEnable(false);
	
	_myWold->addJoint(joint);

	scheduleUpdate();
}

void RotateWithVeloc::update(float dt)
{
	for (auto &arraw :allArrow)
	{
		if (arraw != nullptr && arraw->getPhysicsBody() != nullptr && arraw->getPhysicsBody()->getVelocity()!=Vec2::ZERO &&arraw->getPhysicsBody()->isGravityEnabled() == true) {
			arraw->setRotation(-arraw->getPhysicsBody()->getVelocity().getAngle() * 180 / PI);
		}
	}
	
}

void RotateWithVeloc::exitCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, GameOverScene::createScene(-1)));
}

void RotateWithVeloc::restartCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(RotateWithVeloc::createScene());
}

void RotateWithVeloc::debugCallback(Ref *pSender)
{
	if (_myWold->getDebugDrawMask() == PhysicsWorld::DEBUGDRAW_ALL)
	{
		_myWold->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	} 
	else
	{
		_myWold->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}

bool RotateWithVeloc::onTouchBegan(Touch *touch, Event *unused_event)
{
	 auto spriteParent = Node::create();
	spriteParent->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
	addChild(spriteParent);
	beginPoint = touch->getLocation();
	log("%f - %f", beginPoint.x, beginPoint.y);
	spriteParent->setPosition(beginPoint);
	auto sprite = createNewArrow();
	sprite->setVisible(false);
	allArrow.push_back(sprite);
	spriteParent->addChild(allArrow.back(),100);
	return true;
}

void RotateWithVeloc::onTouchMoved(Touch *touch, Event *unused_event)
{
	float baseLength = 200;
	auto vect = beginPoint - touch->getLocation();
	allArrow.back()->setVisible(true);
	allArrow.back()->setRotation(-vect.getAngle() * 180 / PI);
	allArrow.back()->setScaleX(vect.getLength() / baseLength);
}

void RotateWithVeloc::onTouchEnded(Touch *touch, Event *unused_event)
{
	allArrow.back()->setVisible(true);
	allArrow.back()->setScale(1);
	allArrow.back()->getPhysicsBody()->setGravityEnable(true);
	allArrow.back()->getPhysicsBody()->applyImpulse((beginPoint - touch->getLocation()) * 500000);
}

Sprite* RotateWithVeloc::createNewArrow()
{
	auto sprite = Sprite::create("arrow.png");
	sprite->setPhysicsBody(PhysicsBody::createBox(Size(50, 20), PhysicsMaterial(100, 1, 1)));
	sprite->getPhysicsBody()->setGravityEnable(false);
	sprite->getPhysicsBody()->setCollisionBitmask(0x00000010);
	sprite->getPhysicsBody()->setCategoryBitmask(0x00000001);
	sprite->getPhysicsBody()->setContactTestBitmask(0x1);
	sprite->setTag(ARROW);
	return sprite;
}

bool RotateWithVeloc::onContactBegin(const PhysicsContact &contact)
{
	log("contact begin");
	auto spriteA = contact.getShapeA()->getBody()->getNode();
	auto spriteB = contact.getShapeB()->getBody()->getNode();
	auto p = contact.getContactData()->points;
	log("Pos: %f - %f", p[0].x, p[0].y);
	if (spriteA == nullptr || spriteB == nullptr) {
		log("JADG+JKGFJG+FJKGFJKG+FKG+FG+F");
		return false;
	}
	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();
	if (tagA == LAND )
	{
		//spriteB->getPhysicsBody()->setVelocity(Vect(0, 0));
		//spriteB->getPhysicsBody()->setGravityEnable(false);
		spriteB->setPhysicsBody(nullptr);
	}
	if (tagB == LAND)
	{
		//spriteA->getPhysicsBody()->setVelocity(Vect(0, 0));
		//spriteA->getPhysicsBody()->setGravityEnable(false);
		spriteA->setPhysicsBody(nullptr);
	}

	if (tagA == LINE)
	{
		joint->removeFormWorld();
		spriteA->removeFromPhysicsWorld();
		spriteA->setVisible(false);
		spriteB->setPhysicsBody(nullptr);
		spriteB->setVisible(false);
	}
	if (tagB == LINE) {
		joint->removeFormWorld();
		spriteB->removeFromPhysicsWorld();
		spriteB->setVisible(false);
		spriteA->setPhysicsBody(nullptr);
		spriteA->setVisible(false);
	}
	auto body = PhysicsBody::createBox(Size(100, 10), PhysicsMaterial(1, 0, 0));
	body->setDynamic(false);
	body->setGravityEnable(false);
	if (tagA == WALLTAG && tagB == ARROW) {
		auto save = spriteB->getPhysicsBody()->getVelocity().getAngle();
		//spriteB->getPhysicsBody()->setGravityEnable(false);
		spriteB->setPhysicsBody(body);
		spriteB->setRotation(-save);
	}
	if (tagB == WALLTAG && tagA == ARROW)
	{
		auto save = spriteA->getPhysicsBody()->getVelocity().getAngle();
		//spriteA->getPhysicsBody()->setVelocity(Vect(0,0));
		//spriteA->getPhysicsBody()->setGravityEnable(false);
		spriteA->setPhysicsBody(body);
		spriteA->setRotation(-save);
	}
	if (tagA == OBJECTTAG && tagB == ARROW) {
		fakeJointObject(spriteA->getPhysicsBody(), spriteB->getPhysicsBody(),p[0]);
	}
	if (tagA == ARROW && tagB == OBJECTTAG)
	{
		fakeJointObject(spriteA->getPhysicsBody(), spriteB->getPhysicsBody(),p[0]);
	}
	return true;
}

void RotateWithVeloc::nextCallback(Ref *pSender)
{
	HugeLayer * layer = HugeLayer::create();
	getParent()->addChild(layer);
	removeAllChildren();
	removeFromParent();
}

void RotateWithVeloc::fakeJointObject(PhysicsBody *bdA, PhysicsBody *bdB,Vec2 pos)
{
	auto sprite = Sprite::create("arrow.png");
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	Vec2 basePos;
	if (bdA->getNode()->getTag() == OBJECTTAG)
	{
		basePos = bdA->getPosition();
		Size size = bdA->getNode()->getContentSize();
		Vec2 posna = bdA->getNode()->convertToNodeSpace(pos);
		bdA->getNode()->addChild(sprite);
		log("Rotation Off: %f\nRotation: %f\n\n", bdA->getRotationOffset(), bdA->getRotation());
		Vec2 posB = caculatePos(posna, -bdA->getRotation());
		sprite->setPosition(posB);
		//sprite->setPosition(Vec2(caculatePos(basePos.x,pos.x,size.width),caculatePos(basePos.y,pos.y,size.height)));
		sprite->setRotation(-bdB->getVelocity().getAngle() * 180 / PI -bdA->getRotation());
		bdB->getNode()->setVisible(false);
		bdB->removeFromWorld();
	}
	else {
		basePos = bdB->getPosition();
		Size size = bdB->getNode()->getContentSize();
		Vec2 posna = bdB->getNode()->convertToNodeSpace(pos);
		bdB->getNode()->addChild(sprite);
		log("Rotation Off: %f\nRotation: %f\n\n", bdB->getRotationOffset(), bdB->getRotation());
		Vec2 posnB = caculatePos(posna,-bdB->getRotation());
		sprite->setPosition(posnB);
		//sprite->setPosition(Vec2(caculatePos(basePos.x,pos.x,size.width),caculatePos(basePos.y,pos.y,size.height)));
		sprite->setRotation(-bdA->getVelocity().getAngle() * 180 / PI - bdB->getRotation());
		bdA->getNode()->setVisible(false);
		bdA->removeFromWorld();
	}

}

Vec2 RotateWithVeloc::caculatePos(Vec2 beforePos, float angle)
{
	Vec2 returnPos;
	returnPos.x = beforePos.x*cos(angle) - beforePos.y*sin(angle);
	returnPos.y = beforePos.x*sin(angle) + beforePos.y*cos(angle);
	return returnPos;
}
