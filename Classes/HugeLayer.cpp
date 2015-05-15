#include "HugeLayer.h"
#define ARROW 0
#define WALLTAG 1

#define FOLLOW 10
HugeLayer* HugeLayer::create()
{
	HugeLayer *layer = new HugeLayer();
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool HugeLayer::init()
{
	if (!BaseLayer::init()) {
		return false;
	}
	back = Sprite::create("hugeBack.png");
	auto rateWith = back->getContentSize().width / _visibleSize.width; // >1
	auto rateHeight = back->getContentSize().height / _visibleSize.height; // >1
	//back->setAnchorPoint(Vec2((rateHeight-1)*1/rateHeight*0.5,(rateHeight-1)*1/rateHeight*0.5));
	back->setAnchorPoint(Vec2::ZERO);
	auto mid = Node::create();
	mid->setPosition(Vec2(back->getContentSize().width / 2, back->getContentSize().height / 2));
	back->addChild(mid);
	auto size = back->getContentSize();
	auto as = Follow::create(mid);
	as->setTag(FOLLOW);
	back->runAction(as);
	addChild(back);
	auto node = Node::create();
	node->setPhysicsBody(PhysicsBody::createBox(Size(back->getContentSize().width,100), PhysicsMaterial(1, 0, 0)));
	node->getPhysicsBody()->setGravityEnable(false);
	node->getPhysicsBody()->setDynamic(false);
	node->getPhysicsBody()->setContactTestBitmask(0x1);
	node->setTag(WALLTAG);
	back->addChild(node, 10);
	node->setPosition(Vec2(back->getContentSize().width / 2, 0));

	auto wallBd = PhysicsBody::createBox(Size(100, back->getContentSize().height), PhysicsMaterial(1, 0, 0));
	wallBd->setGravityEnable(false);
	wallBd->setDynamic(false);
	wallBd->setContactTestBitmask(0x1);
	auto wallBd2 = PhysicsBody::createBox(Size(100, back->getContentSize().height), PhysicsMaterial(1, 0, 0));
	wallBd2->setGravityEnable(false);
	wallBd2->setDynamic(false);
	wallBd2->setContactTestBitmask(0x1);

	auto node2 = Node::create();
	node2->setTag(WALLTAG);
	node2->setPhysicsBody(wallBd);
	node2->setPosition(Vec2(10, back->getContentSize().height / 2));
	back->addChild(node2,10);
	auto node3 = Node::create();
	node3->setTag(WALLTAG);
	node3->setPhysicsBody(wallBd2);
	node3->setPosition(Vec2(back->getContentSize().width, back->getContentSize().height / 2));
	back->addChild(node3, 10);



	fakeArrow = createArrow();
	fakeArrow->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height -200));
	//addChild(fakeArrow);
	return true;
}

void HugeLayer::exitCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(GameOverScene::createScene(-1));
}

void HugeLayer::restartCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(RotateWithVeloc::createScene());
}

void HugeLayer::debugCallback(Ref *pSender)
{
	auto w = Director::getInstance()->getRunningScene()->getPhysicsWorld();
	if (w->getDebugDrawMask() == PhysicsWorld::DEBUGDRAW_ALL) {
		w->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	}
	else {
		w->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}

void HugeLayer::onEnter()
{
	BaseLayer::onEnter();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HugeLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HugeLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HugeLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HugeLayer::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	scheduleUpdate();
}

void HugeLayer::onExit()
{
	BaseLayer::onExit();
}
void HugeLayer::update(float delta)
{
	for (auto &arraw : allArrow)
	{
		if (arraw != nullptr && arraw->getPhysicsBody() != nullptr && arraw->getPhysicsBody()->getVelocity() != Vec2::ZERO &&arraw->getPhysicsBody()->isGravityEnabled() == true) {
			arraw->setRotation(-arraw->getPhysicsBody()->getVelocity().getAngle() * 180 / PI);
			//fakeArrow->setRotation(arraw->getRotation());
		}
	}
}

Sprite* HugeLayer::createArrow()
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

bool HugeLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto sprite = createArrow();
	auto pos1 = touch->getLocation();
	auto pos2 = touch->getLocationInView();
	sprite->setPosition(pos1+Vec2(back->getContentSize().width/2,back->getContentSize().height/2));
	allArrow.push_back(sprite);
	back->addChild(allArrow.back(), 300);
	beginPoint = pos1;
	back->stopActionByTag(FOLLOW);
	back->runAction(Follow::create(allArrow.back()));
	return true;

}

void HugeLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	float baseLength = 200;
	auto vect = beginPoint - touch->getLocation();
	allArrow.back()->setVisible(true);
	allArrow.back()->setRotation(-vect.getAngle() * 180 / PI);
	allArrow.back()->setScaleX(vect.getLength() / baseLength);
	//fakeArrow->setRotation(allArrow.back()->getRotation());
}

void HugeLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	allArrow.back()->setVisible(true);
	allArrow.back()->setScale(1);
	allArrow.back()->getPhysicsBody()->setGravityEnable(true);
	allArrow.back()->getPhysicsBody()->applyImpulse((beginPoint - touch->getLocation()) * 500000);
	
}

bool HugeLayer::onContactBegin(const PhysicsContact &contact)
{
	auto spriteA = contact.getShapeA()->getBody()->getNode();
	auto spriteB = contact.getShapeB()->getBody()->getNode();

	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();
	if (tagA == WALLTAG) {
		spriteB->setPhysicsBody(nullptr);
	}
	if (tagB == WALLTAG) {
		spriteA->setPhysicsBody(nullptr);
	}

	return true;
}

void HugeLayer::nextCallback(Ref *pSender)
{
	NativeAlert::showWithCallback("My Title", "message content", "Cancel", "Back", "OtherButton", 111, CC_CALLBACK_2(HugeLayer::onNativeCallback, this));
}

void HugeLayer::onNativeCallback(int tag, NativeAlert::ButtonType type)
{
	log("Native callback");
	switch (type)
	{
	case cocos2d::NativeAlert::ButtonType::CANCEL:
		break;
	case cocos2d::NativeAlert::ButtonType::OTHER:
		break;
	case cocos2d::NativeAlert::ButtonType::RETURN:
		break;
	default:
		break;
	}
}


