#include "TemplateScene.h"


Scene* Template::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
	auto layer = Template::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

bool Template::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	this->setAccelerometerEnabled(true);
	auto aListener = EventListenerAcceleration::create(CC_CALLBACK_2(Template::onAccleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(aListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Template::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Template::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Template::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Template::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->scheduleUpdate();

	return true;
}
void Template::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();

}
void Template::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	
}

bool Template::onTouchBegan(Touch* touch, Event* evnet) {
	auto location = touch->getLocation();
	
	return true;
}
void Template::onTouchEnded(Touch* touch, Event* event) {

}
void Template::onTouchMoved(Touch* touch, Event* event){
	Point touchLocation = touch->getLocation();
	
}
void Template::update(float dt) {
	
}
void Template::onAccleration(Acceleration *pAccelerationValue, Event *event) {
	cocos2d::log("accleration");

}
bool Template::onContactBegin(const PhysicsContact &contact) {
	cocos2d::log("contact");

	return true;
}


Template::Template() {
	cocos2d::log("On contruct");

}
Template::~Template() {
	cocos2d::log("On Template Destruct");

}

