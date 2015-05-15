#include "LoadingLayer.h"


Scene* LoadingLayer::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
	auto layer = LoadingLayer::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	auto infoLayer = InforLayer::create();
	scene->addChild(infoLayer);
	return scene;
}

bool LoadingLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	auto back = LayerGradient::create(Color4B(10, 10, 10, 150), Color4B(0, 0, 0, 100));
	addChild(back);

	auto sprite = Sprite::create("loading.png");
	loader = ProgressTimer::create(sprite);
	loader->setType(ProgressTimer::Type::RADIAL);
	loader->setPercentage(0.0f);
	loader->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(loader);

	auto text = Text::create("Loading...", "", 30);
	text->setPosition(loader->getPosition() - Vec2(0, 200));
	addChild(text);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(LoadingLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(LoadingLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(LoadingLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	this->scheduleUpdate();

	return true;
}
void LoadingLayer::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();

}
void LoadingLayer::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();

}

bool LoadingLayer::onTouchBegan(Touch* touch, Event* evnet) {
	auto location = touch->getLocation();

	return true;
}
void LoadingLayer::onTouchEnded(Touch* touch, Event* event) {

}
void LoadingLayer::onTouchMoved(Touch* touch, Event* event){
	Point touchLocation = touch->getLocation();

}
void LoadingLayer::update(float dt) {
	float per = loader->getPercentage();
	per += 40.0f*dt;
	loader->setPercentage(per);
	if (per>100.0f)
	{
		this->unscheduleUpdate();
		this->removeFromParent();
	}
}
void LoadingLayer::onAccleration(Acceleration *pAccelerationValue, Event *event) {
	cocos2d::log("onAccleration");

}
bool LoadingLayer::onContactBegin(const PhysicsContact &contact) {
	cocos2d::log("contact");

	return true;
}


LoadingLayer::LoadingLayer() {
	cocos2d::log("On con-truct");

}
LoadingLayer::~LoadingLayer() {
	cocos2d::log("On LoadingLayer Destruct");

}

