#include "TestChipmurk.h"

Scene* TestChipmurk::createScene() {
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = TestChipmurk::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer,0);
	return scene;
}
TestChipmurk* TestChipmurk::create() {
	TestChipmurk *layer = new TestChipmurk();
	if (layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
bool TestChipmurk::init() {
	if (!Layer::init()) {
		return false;
	}
	winSize = Director::getInstance()->getWinSize();
	ordinSize = Director::getInstance()->getVisibleOrigin();
	auto backGround = Sprite::create("back.png");//backwin
	//backGround->setRotation(45);
	//if ()
	backGround->setScale(MIN(float((winSize.width-100) / backGround->getContentSize().width), float((winSize.height - 100) / backGround->getContentSize().height)));
	cocos2d::log("BACKGROUND SCALE: %lf", backGround->getScale());
	backGroundScaleRatio = backGround->getScale();
	backGround->setPosition(winSize.width / 2, winSize.height / 2);
	addChild(backGround);
	auto backWidth = backGround->getContentSize()*backGround->getScale();
	//cocos2d::log("winsize: %f %f \n backWidth: %f,%f", winSize.width, winSize.height, backWidth.width, backWidth.height);
	Vec2 vec[5] = {
		Vec2(winSize.width / 2 - backWidth.width / 2 + 30, winSize.height / 2 - backWidth.height / 2 + 30),
		Vec2(winSize.width / 2 - backWidth.width / 2 + 30, winSize.height / 2 + backWidth.height / 2 - 30),
		Vec2(winSize.width / 2 + backWidth.width / 2 - 30, winSize.height / 2 + backWidth.height / 2 - 30),
		Vec2(winSize.width / 2 + backWidth.width / 2 - 30, winSize.height / 2 - backWidth.height / 2 + 30),
		Vec2(winSize.width / 2 - backWidth.width / 2 + 30, winSize.height / 2 - backWidth.height / 2 + 30)
	};

	auto buton = Button::create("close.png", "close.png");
	buton->setTouchEnabled(true);
	buton->setPosition(Vec2(30, winSize.height - 40));
	buton->addTouchEventListener(CC_CALLBACK_2(TestChipmurk::clickBack, this));
	addChild(buton);

	srand(time(NULL));
	auto boderDb = PhysicsBody::createEdgeChain(vec, 5, PHYSICSBODY_MATERIAL_DEFAULT);
	auto node = Node::create();
	boderDb->getShape(0)->setRestitution(0.9f);
	boderDb->getShape(0)->setFriction(1.0f);
	node->setPhysicsBody(boderDb);
	node->setTag(11111);
	node->setPosition(Vec2::ZERO);
	addChild(node);


	strengthSlider = Slider::create();
	strengthSlider->loadBarTexture("Button/streng_background.png");
	strengthSlider->loadProgressBarTexture("Button/process.png");
	strengthSlider->loadSlidBallTextures("Button/hand.png", "Button/hand.png", "");
	strengthSlider->setPercent(0);
	strengthSlider->setTouchEnabled(false);
	strengthSlider->setScale9Enabled(true);
	strengthSlider->setRotation(90);
	strengthSlider->setPosition(Vec2(strengthSlider->getContentSize().height,0 + strengthSlider->getContentSize().width));
	addChild(strengthSlider);


	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(TestChipmurk::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(TestChipmurk::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TestChipmurk::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(TestChipmurk::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(TestChipmurk::onTouchCancelled, this);
	touchListener->setEnabled(true);
	touchListener->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);


	debugButton = Button::create("CloseNormal.png", "CloseSelected.png");
	debugButton->setTouchEnabled(true);
	debugButton->setPosition(Vec2(winSize.width - 20, winSize.height - 20));
	debugButton->addTouchEventListener(CC_CALLBACK_2(TestChipmurk::drawDebug, this));
	addChild(debugButton);

	//cocos2d::log("Vec1: %f, %f",vec[0].x,vec[0].y );

	

	return true;
}

void TestChipmurk::onEnterTransitionDidFinish() {

	_ball = Sprite::create("baseball.png");
	_ball->setScale(backGroundScaleRatio);
	_ball->setPosition(winSize.width / 2, winSize.height / 2);
	_ball->setTag(BIA::BASE_BALL);
	addChild(_ball);
	_arraw = Sprite::create("arraw.png");
	_arraw->setAnchorPoint(Vec2(0, 0.5));
	_arraw->setTag(SPRITE_TAG::ARRAW);
	addChild(_arraw);
	//_arraw->setVisible(true);
	//_arraw->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	auto ballBodyWidth = backGroundScaleRatio*(_ball->getContentSize().width / (2) - 6);

	_ballBody = PhysicsBody::createCircle(ballBodyWidth, MY_MASTERIAL);
	_ballBody->setVelocityLimit(BIA::MAX_SPEED);
	_ballBody->setLinearDamping(LINEAR_DUMPING);
	_ballBody->setAngularDamping(ANGULARDUMPING);
	_ball->setPhysicsBody(_ballBody);
	_allBox.push_back(_ball);

	auto pribody = PhysicsBody::createCircle(ballBodyWidth, MY_MASTERIAL);

	pribody->setVelocityLimit(BIA::MAX_SPEED);
	pribody->setLinearDamping(LINEAR_DUMPING);
	pribody->setAngularDamping(ANGULARDUMPING);

	auto sprite = Sprite::create("priball.png");
	sprite->setTag(BIA::PRI_BALL);
	sprite->setScale(backGroundScaleRatio);
	_allBox.push_back(sprite);
	addChild(_allBox.back());
	_allBox.back()->setPosition(Vec2(winSize.width/2 - 100, winSize.height - 200));
	_allBox.back()->setPhysicsBody(pribody);

	auto secbody = PhysicsBody::createCircle(ballBodyWidth, MY_MASTERIAL);

	secbody->setVelocityLimit(BIA::MAX_SPEED);
	secbody->setLinearDamping(LINEAR_DUMPING);
	secbody->setAngularDamping(ANGULARDUMPING);

	auto secBall = Sprite::create("secball.png");
	secBall->setTag(BIA::SEC_BALL);
	secBall->setScale(backGroundScaleRatio);
	_allBox.push_back(secBall);
	addChild(_allBox.back());
	_allBox.back()->setPosition(Vec2(winSize.width/2 + 100, winSize.height - 200));
	_allBox.back()->setPhysicsBody(secbody);
	float x = 0, y = 0, z = 0;
	///Need this code for fix position bug of node position when layer was scale in cocos2dx v3.4
	auto node = getChildByTag(11111);
	node->setPosition(Vec2::ZERO);

	cameraButton = Button::create();
	cameraButton->loadTextureNormal("4.png");
	cameraButton->setPosition(Vec2(winSize.width - 50, 100));
	cameraButton->setTouchEnabled(true);
	cameraButton->addTouchEventListener(CC_CALLBACK_2(TestChipmurk::touchCameraButton, this));
	addChild(cameraButton,100);

	
	//Vec2 pos = _ball->getPosition();
	//this->runAction(CustomFollow::create(_ball, Rect(pos.x,pos.y,winSize.width-pos.x,winSize.height-pos.y)));
	scheduleUpdate();
}
void TestChipmurk::update(float dt) {
	/*if (abs(_ballBody->getVelocity().x) > BIA::MAX_SPEED) {
		if (_ballBody->getVelocity().x > 0) {
			_ballBody->setVelocity(Vect(MAX_SPEED, _ballBody->getVelocity().y));
		}
		else
		{
			_ballBody->setVelocity(Vect(-MAX_SPEED, _ballBody->getVelocity().y));
		}
	}
	if (abs(_ballBody->getVelocity().y) > BIA::MAX_SPEED) {
		if (_ballBody->getVelocity().y> 0) {
			_ballBody->setVelocity(Vect(_ballBody->getVelocity().x,MAX_SPEED));
		}
		else
		{
			_ballBody->setVelocity(Vect(_ballBody->getVelocity().x, -MAX_SPEED));
		}
	} */
	float minSpeed = 0;
	if (onBegin == false) return;
	for (Sprite* ball : _allBox)
	{
		float speed = ball->getPhysicsBody()->getVelocity().lengthSquared();
		if (minSpeed < speed) {
			minSpeed = speed;
		}
		if (minSpeed < BIA::MIN_SPEED) {
			//destroyBallBody(ball->getPhysicsBody());
			canTouch = true;
		}
		
	}
	if (onCamera) {
		Camera *ca = Director::getInstance()->getRunningScene()->getCameras().front();
		ca->setPosition(_ball->getPosition());
		
	}
	//cocos2d::log("MIN SPEED: %lf", minSpeed);
}
bool TestChipmurk::onContactBegin(const PhysicsContact &contact) {
	auto spriteA = contact.getShapeA()->getBody()->getNode();
	auto spriteB = contact.getShapeB()->getBody()->getNode();

	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();

	return true;
}
bool TestChipmurk::onTouchBegan(Touch* touch, Event* event) {
	cocos2d::log("====touch began====");
	if (canTouch == false) return false;
	onBegin = false;
	beginPoint = touch->getLocation();
	//cocos2d::log("Position: x %f- y %f", beginPoint.x, beginPoint.y);
	//auto node = getChildByTag(11111);
	//node->setPosition(beginPoint);
	//_ball->setPosition(beginPoint);
	//_ballBody->setCollisionBitmask(COLLISION_BITMASK::NON);
	for (Sprite* ball : _allBox)
	{
		/*float speed = ball->getPhysicsBody()->getVelocity().lengthSquared();
		if (minSpeed > speed) {
		minSpeed = speed;
		}*/
		destroyBallBody(ball->getPhysicsBody());
	}
	
	//_arraw->setVisible(true);
	_arraw->setPosition(_ball->getPosition());
	_arraw->setScale(1);
	return true;
}
void TestChipmurk::onTouchMoved(Touch* touch, Event* event) {
	auto point = touch->getLocation();
	Vec2 distan = beginPoint -point;
	auto scaleRatio = distan.length() / 128;
	if (scaleRatio > MAX_SCALE) scaleRatio = MAX_SCALE;
	_arraw->setScaleX(scaleRatio);
	//cocos2d::log("SCALE %lf",_arraw->getScaleX());
	_arraw->setVisible(true);
	//auto a = atan(distan.y / (distan.x)) *180/PI;
	auto a = distan.getAngle() *180/PI;
	//log("distan X %lf, y %lf: ", distan.x, distan.y);
	log("goc: %lf", a);
	/*if (distan.x < 0) {
		_arraw->setFlippedX(true);
		_arraw->setAnchorPoint(Vec2(1, 0.5));
	}
	else {
		_arraw->setFlippedX(false);
		_arraw->setAnchorPoint(Vec2(0, 0.5));
	}*/
	_arraw->setRotation(-a);
	if (abs(distan.x) > PUSH_LIMIT*backGroundScaleRatio) {
		distan.y = distan.y * abs(PUSH_LIMIT*backGroundScaleRatio / distan.x);
		if (distan.x > 0) {
			distan.x = PUSH_LIMIT*backGroundScaleRatio;
		}
		else {
			distan.x = -PUSH_LIMIT*backGroundScaleRatio;
		}
	}
	if (abs(distan.y) > PUSH_LIMIT*backGroundScaleRatio) {
		distan.x = distan.x * abs(PUSH_LIMIT*backGroundScaleRatio / distan.y);
		if (distan.y > 0) {
			distan.y = PUSH_LIMIT*backGroundScaleRatio;
		}
		else {
			distan.y = -PUSH_LIMIT*backGroundScaleRatio;
		}
	}
	strengthSlider->setPercent(ceil(distan.lengthSquared()/ PUSH_LIMIT*backGroundScaleRatio));
}
void TestChipmurk::onTouchEnded(Touch* touch, Event* event) {
	onBegin = true;
	canTouch = false;
	endPoint = touch->getLocation();
	auto push = beginPoint - endPoint;
	_ballBody->setGravityEnable(true);
	_ballBody->setCollisionBitmask(COLLISION_BITMASK::NORMAL);
	log(" %lf %lf", push.x, push.y);
	if (abs(push.x) > PUSH_LIMIT*backGroundScaleRatio) {
		push.y = push.y * abs(PUSH_LIMIT*backGroundScaleRatio / push.x);
		if (push.x > 0) {
			push.x = PUSH_LIMIT*backGroundScaleRatio;
		}
		else {
			push.x = -PUSH_LIMIT*backGroundScaleRatio;
		}
	}
	if (abs(push.y) > PUSH_LIMIT*backGroundScaleRatio) {
		push.x = push.x * abs(PUSH_LIMIT*backGroundScaleRatio / push.y);
		if (push.y > 0) {
			push.y = PUSH_LIMIT*backGroundScaleRatio;
		}
		else {
			push.y = -PUSH_LIMIT*backGroundScaleRatio;
		}
	}
	log(" %f %f", push.x, push.y);
	_ballBody->applyImpulse(push*BIA::MULTIPLE);
	_arraw->setVisible(false);
	strengthSlider->setPercent(0);
	this->runAction(Sequence::create(DelayTime::create(5), CallFunc::create(this, callfunc_selector(TestChipmurk::afterTensecond)), nullptr));
}
void TestChipmurk::destroyBallBody(PhysicsBody* body) {
	body->setGravityEnable(false);
	body->setVelocity(Vect(0, 0));
	body->setAngularVelocity(0);
}
void TestChipmurk::drawDebug(Ref* pSender, Widget::TouchEventType type) {
	cocos2d::log("CLICK");
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		checkDrawDebug();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
void TestChipmurk::clickBack(Ref *pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameOverScene::createScene(-1)));
		Director::getInstance()->resume();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
void TestChipmurk::checkDrawDebug() {
	log("debug");
	if (_myWorld->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE) {
		_myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	}
	else {
		_myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}

void TestChipmurk::afterTensecond()
{
	canTouch = true;
}

void TestChipmurk::touchCameraButton(Ref *pSender, Widget::TouchEventType type)
{
	cocos2d::log("TOuch Button");
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		if (onCamera) {
			onCamera = false;
			cocos2d::log("FALSE");
		}
		else {
			onCamera = true;
			cocos2d::log("TRUE");
		}
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
