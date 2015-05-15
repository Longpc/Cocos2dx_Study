#include "TestBodyParser.h"

USING_NS_CC;

Scene* BodyTestScene::createScene() {
	auto scene = cocos2d::Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, -1000.0f));
	auto layer = BodyTestScene::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}
BodyTestScene* BodyTestScene::create() {
	BodyTestScene *layer = new BodyTestScene();
	if (layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
bool BodyTestScene::init() {
	if (!Layer::init()) {
		return false;
	}
	size = Director::getInstance()->getWinSize();
	_backButton = Sprite::create("close.png");
	_backButton->setPosition(Vec2(size.width - _backButton->getContentSize().width, size.height - _backButton->getContentSize().height / 2));
	addChild(_backButton);
	_testSprite = Sprite::create("2dx.png");
	_testSprite->setPosition(Vec2(size.width / 2, size.height / 2));
	this->setAccelerometerEnabled(true);
	auto aListener = EventListenerAcceleration::create(CC_CALLBACK_2(BodyTestScene::onAccleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(aListener,this);
	MyBodyParser::getInstance()->parseJsonFile("test.json");
	auto _body = MyBodyParser::getInstance()->bodyFormJson(_testSprite, "Name");
	if (_body != nullptr) {
		_body->setDynamic(false);
		//_body->setCollisionBitmask(0x000001);
		_body->setContactTestBitmask(CONTACT_TEST_BITMASK);
		_testSprite->setPhysicsBody(_body);
	}
	addChild(_testSprite);
	_screenBolder = Sprite::create();
	auto boundBody = PhysicsBody::createEdgeBox(Size(size.width - 100, size.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	boundBody->getShape(0)->setRestitution(0.5f);
	boundBody->getShape(0)->setFriction(0.0f);
	boundBody->getShape(0)->setDensity(1.0f);
	_screenBolder->setPosition(Point(size.width / 2, size.height / 2));
	_screenBolder->setPhysicsBody(boundBody);
	boundBody->setContactTestBitmask(CONTACT_TEST_BITMASK);
	this->addChild(_screenBolder);
	_screenBolder->setTag(SPRITE_TAG::WALL);

	_ball = Sprite::create("ball.png", Rect(0, 0, 90, 90));
	//_ball->setScale(5.5f);
	_ball->setPosition(100, size.height-_ball->getContentSize().height);
	auto ballBd = PhysicsBody::createCircle(_ball->getContentSize().width / 2.);
	ballBd->getShape(0)->setRestitution(1.0f);
	ballBd->getShape(0)->setFriction(0.0f);
	ballBd->getShape(0)->setDensity(10.0f);
	ballBd->setGravityEnable(false);
	ballBd->setRotationEnable(true);
	//Vect force = Vect(INIT_VECTOR_X, INIT_VECTOR_Y);
	//ballBd->applyImpulse(force);
	//_ball->setPhysicsBody(ballBd);
	ballBd->setContactTestBitmask(CONTACT_TEST_BITMASK);
	_ball->setTag(SPRITE_TAG::BALL);
	this->addChild(_ball);
	auto dispath = Director::getInstance()->getEventDispatcher();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(BodyTestScene::onContactBegin, this);
	dispath->addEventListenerWithSceneGraphPriority(contactListener, this);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(BodyTestScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(BodyTestScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(BodyTestScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(BodyTestScene::onTouchCancelled, this);
	touchListener->setEnabled(true);
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	this->scheduleUpdate();
	toggleOfDebugDraw();
	return true;
}
void BodyTestScene::update(float dt) {
	//cocos2d::log("update");
	auto pos = _ball->getPosition();
	pos.x = _moveSpeedX;
	pos.y = _moveSpeedY;
	/*if (pos.x < _ball->getContentSize().width) {
		pos.x = _ball->getContentSize().width;
	}
	pos.y = _moveSpeedY;
	if (pos.y < _ball->getContentSize().height) {
		pos.y = _ball->getContentSize().height;
	} */
	_ball->setPosition(pos);
}
void BodyTestScene::createBall(Vec2 point) {
	//auto ball2 = new Ball("ball.png",TAG_BALL,"ball");
	auto ball2 = Sprite::create("ball.png");/*Ball::Ball("ball.png", TAG_BALL, "name"); */
	ball2/*.getSprite()*/->setPosition(point);
	//_ball->setScale(5.5f);
	auto ballBd = PhysicsBody::createCircle(ball2/*.getSprite()*/->getContentSize().width / 2.);
	ballBd->getShape(0)->setRestitution(1.0f);
	ballBd->getShape(0)->setFriction(0.0f);
	ballBd->getShape(0)->setDensity(10.0f);
	ballBd->setGravityEnable(true);
	ballBd->setRotationEnable(true);
	//Vect force = Vect(INIT_VECTOR_X, INIT_VECTOR_Y);
	//ballBd->applyImpulse(force);
	ball2/*.getSprite()*/->setPhysicsBody(ballBd);
	ballBd->setContactTestBitmask(CONTACT_TEST_BITMASK);
	this->addChild(ball2/*.getSprite()*/);
}
bool BodyTestScene::onContactBegin(const PhysicsContact &contact) {
	return true;
}
bool BodyTestScene::onTouchBegan(Touch* touch, Event* event) {
	cocos2d::log("TOuch begin");
	Vec2 point = touch->getLocation();
	Rect rec = _backButton->getBoundingBox();
	
	if (rec.containsPoint(point)) {
		auto scene = GameOverScene::createScene(-1);
		Director::getInstance()->replaceScene(TransitionProgressRadialCW::create(2,scene));
		return false;
	}
	//_ball->setPosition(point);
	createBall(point);
	return true;
}
void BodyTestScene::onTouchEnded(Touch* touch, Event* event)
{
	
}

void BodyTestScene::onTouchMoved(Touch* touch, Event* event)
{
	//cocos2d::log("touch moved");
}

void BodyTestScene::onTouchCancelled(Touch* touch, Event* event)
{
	//cocos2d::log("touch cancelled");
}
void BodyTestScene::onAccleration(Acceleration* pAccelerationValue, Event * event) {

#define MAXX size.width-_ball->getContentSize().width/2
#define MINX _ball->getContentSize().width
#define MAXY size.height - _ball->getContentSize().height/2
#define MINY _ball->getContentSize().height
#define DEC 1.0f
#define SPEED 20

	_moveSpeedX = _moveSpeedX*DEC + SPEED*pAccelerationValue->x;
	_moveSpeedY = _moveSpeedY*DEC + SPEED*pAccelerationValue->y;

	if (_moveSpeedX > MAXX) {
		_moveSpeedX = MAXX;
	}
	else if (_moveSpeedX < MINX) {
		_moveSpeedX = MINX;
	}
	if (_moveSpeedY > MAXY) {
		_moveSpeedY = MAXY;
	}
	else if (_moveSpeedY < MINY) {
		_moveSpeedY = MINY;
	}
}
void BodyTestScene::toggleOfDebugDraw(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto toggleItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(BodyTestScene::btnDebugDrawCallback, this));
	toggleItem->setPosition(Point(origin.x + visibleSize.width - toggleItem->getContentSize().width / 2,
		origin.y + toggleItem->getContentSize().height / 2));
	auto menu = Menu::create(toggleItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 100);
}
void BodyTestScene::btnDebugDrawCallback(Ref *pSender)
{
	if (_myWorld->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE) {
		_myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	}
	else {
		_myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}
BodyTestScene::BodyTestScene()
{
}

BodyTestScene::~BodyTestScene()
{
}