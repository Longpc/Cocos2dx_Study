#include "JumpGame.h"


Scene* JumpGame::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, -1000.0f));
	auto layer = JumpGame::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	auto infoLayer = InforLayer::create();
	scene->addChild(infoLayer);
	return scene;
}

bool JumpGame::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	this->setAccelerometerEnabled(true);
	auto aListener = EventListenerAcceleration::create(CC_CALLBACK_2(JumpGame::onAccleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(aListener, this);

	birdLeftPos = Vec2(20, visibleSize.height - 150);
	birdRightPos = Vec2(visibleSize.width - 30, visibleSize.height - 150);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(JumpGame::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(JumpGame::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(JumpGame::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(JumpGame::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	
	auto back = Button::create("close.png", "close.png");
	back->setTouchEnabled(true);
	back->addTouchEventListener(CC_CALLBACK_2(JumpGame::backToGameOverScreen, this));
	back->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 50));
	addChild(back,10);

	auto jumpButton = Button::create("Button/redButton111x71.png", "Button/redBrightButton111x71.png");
	jumpButton->setTouchEnabled(true);
	jumpButton->setTitleFontSize(25);
	jumpButton->setTitleText("jump");
	jumpButton->addTouchEventListener(CC_CALLBACK_2(JumpGame::touchJump, this));
	jumpButton->setPosition(Vec2(jumpButton->getContentSize().width/2, 100));
	addChild(jumpButton,10);

	auto landButton = Button::create("Button/redButton111x71.png", "Button/redBrightButton111x71.png");
	landButton->setTouchEnabled(true);
	landButton->setTitleFontSize(25);
	landButton->setTitleText("create");
	landButton->addTouchEventListener(CC_CALLBACK_2(JumpGame::touchCreateLand, this));
	landButton->setPosition(Vec2(landButton->getContentSize().width / 2, 200));
	addChild(landButton, 10);

	srand(time(NULL));
	return true;
}
void JumpGame::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	back1 = Sprite::create("Jump/back2.png");
	back1->setScaleX(visibleSize.width / back1->getContentSize().width);
	back1->setScaleY(visibleSize.height / back1->getContentSize().height);
	addChild(back1,-100);
	back1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	back2 = Sprite::create("Jump/back2.png");
	back2->setScaleX(back1->getScaleX());
	back2->setScaleY(back1->getScaleY());
	addChild(back2,-100);
	back2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*1.5));

	position2 = back2->getPosition();

	jumper = Sprite::create("Jump/jumper.png");
	jumper->setPosition(Vec2(visibleSize.width / 2, 350));
	/*MyBodyParser::getInstance()->parseJsonFile("body/jumper.json");
	auto jumperBd = MyBodyParser::getInstance()->bodyFormJson(jumper, "jumper");*/
	auto jumperBd = PhysicsBody::createBox(jumper->getContentSize(), PhysicsMaterial(100, 1, 0));
	jumperBd->setContactTestBitmask(CONTACT_TEST_BITMASK);
	jumperBd->setMass(1.0f);
	jumperBd->setRotationEnable(false);
	jumper->setPhysicsBody(jumperBd);
	addChild(jumper);

	initLand(200);
	/*panda = Sprite::create("Jump/panda.png");
	panda->setPosition(Vec2(50, 300));
	MyBodyParser::getInstance()->parseJsonFile("body/panda.json");
	auto pandaBody = MyBodyParser::getInstance()->bodyFormJson(panda, "panda");
	pandaBody->setContactTestBitmask(CONTACT_TEST_BITMASK);
	//pandaBody->setCollisionBitmask(0x00000000);
	pandaBody->setGravityEnable(false);
	pandaBody->setDynamic(false);
	pandaBody->getShape(0)->setDensity(10.0f);
	panda->setPhysicsBody(pandaBody);
	panda->setTag(SPRITE_TAG::PANDA);

	addChild(panda);
	onLeft = true;*/
	jumperBd->applyImpulse(Vect(0, 1000));
	effectMouse = FlowerMouse::create(Size(100, 100),"Flower");
	effectMouse->setPosition(Vec2(-200, -200));
	effectMouse->setVisible(false);
	addChild(effectMouse, 100);
	this->scheduleUpdate();
}
void JumpGame::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();

}

bool JumpGame::onTouchBegan(Touch* touch, Event* evnet) {
	auto location = touch->getLocation();
	jumper->setPosition(location);
	jumper->getPhysicsBody()->setVelocity(Vect(0, 0));
	effectMouse->setVisible(true);
	effectMouse->setPosition(location-Vec2(effectMouse->getContentSize().width/2,effectMouse->getContentSize().height/2));
	return true;
}
void JumpGame::onTouchEnded(Touch* touch, Event* event) {
	//createStar(touch->getLocation());
	//effectMouse->setVisible(false);
}
void JumpGame::onTouchMoved(Touch* touch, Event* event){
	Vec2 touchLocation = touch->getLocation();
	if (effectMouse != nullptr) {
		effectMouse->setPosition(touchLocation - Vec2(effectMouse->getContentSize().width / 2, effectMouse->getContentSize().height / 2));
	}
}
void JumpGame::update(float dt) {
	
	auto pos1 = back1->getPosition();
	auto pos2 = back2->getPosition();
	
	pos1.y = pos1.y - jumpOffset;
	pos2.y = pos2.y - jumpOffset;
	currentJump += jumpOffset;
	float speed = jumper->getPhysicsBody()->getVelocity().y;
	//cocos2d::log("%f",speed );
	if (currentJump >= 300) {
		return;
	}
	
	for (int i = 0; i<allLand.size(); i++)
	{
		auto pos = allLand[i]->getPosition();
		pos.y -= jumpOffset;
		if (pos.y > 0) {
			allLand[i]->setPosition(pos);
		}
		else {
			int x = allLand[i]->getContentSize().width/2 + rand() % int(visibleSize.width - allLand[i]->getContentSize().width);
			allLand[i]->setPosition(Vec2(x, visibleSize.height));
		}
		
	}

	if (pos1.y < -(visibleSize.height/2 - jumpOffset)) {
		back1->removeAllChildrenWithCleanup(true);
		back1->setPosition(position2);
	}
	else {
		back1->setPosition(pos1);
	}
	if (pos2.y < -(visibleSize.height/2- jumpOffset)) {
		back2->removeAllChildrenWithCleanup(true);
		back2->setPosition(position2);
	}
	else {
		back2->setPosition(pos2);
	}


}
void JumpGame::onAccleration(Acceleration *pAccelerationValue, Event *event) {
	cocos2d::log("accleration");

}
bool JumpGame::onContactBegin(const PhysicsContact &contact) {
	
	if (contact.getContactData()->normal.y >= 0) return false;
	cocos2d::log("contact");
	currentJump = 0;
	jumper->getPhysicsBody()->applyImpulse(Vect(0, 1000));
}


JumpGame::JumpGame() {
	cocos2d::log("On contruct");

}
JumpGame::~JumpGame() {
	cocos2d::log("On JumpGame Destruct");

}

void JumpGame::backToGameOverScreen(Ref *pSender, Widget::TouchEventType type)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameOverScene::createScene(-1)));
}

void JumpGame::touchJump(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if (jumper->getNumberOfRunningActions() == 0) {
			currentJump = 0;
			animationJUmper(jumper);
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
	/*if (getChildByTag(SPRITE_TAG::BIRD) == nullptr) return;
	animationBird(getChildByTag(SPRITE_TAG::BIRD));*/
}

Sprite* JumpGame::createLand()
{
	auto land = Sprite::create("Jump/land.png");
	auto body = PhysicsBody::createBox(land->getContentSize()-Size(40,40), PhysicsMaterial(1, 1, 0));
	body->setGravityEnable(false);
	body->setDynamic(false);
	body->setContactTestBitmask(CONTACT_TEST_BITMASK);
	land->setPhysicsBody(body);
	land->setTag(SPRITE_TAG::BLOCK);
	return land;
}

void JumpGame::touchCreateLand(Ref *pSender, Widget::TouchEventType type)
{
	if (canCreate == false) return;
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		//createBird();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}

void JumpGame::animationJUmper(Sprite *sprite)
{
	jumper->getPhysicsBody()->setVelocity(Vect(0, 0));
	auto movey = MoveBy::create(duration / 2, Vec2(0, 100));
	auto scaley = ScaleBy::create(duration / 2, 1.0f,0.8f);
	auto sequen1 = Sequence::create(movey, movey->reverse(), nullptr);
	auto sequen2 = Sequence::create(scaley, scaley->reverse(), nullptr);
	sprite->runAction(Spawn::create(sequen1, sequen2, nullptr));
	jumper->getPhysicsBody()->applyImpulse(Vect(0, 10));
}

void JumpGame::createStar(Vec2 position)
{
	auto note = Sprite::create("particle/star.png");
	note->setPosition(position);
	auto particleSystem = ParticleSystem::create("particle/explosion.plist");
	particleSystem->setPosition(position.x, note->getBoundingBox().size.width / 2);
	note->addChild(particleSystem);
	addChild(note);
}

void JumpGame::initLand(int offset)
{
	allLand.clear();
	while (allLand.size() < visibleSize.height/offset)
	{
		allLand.push_back(createLand());
		float x = allLand[allLand.size()-1]->getContentSize().width + rand() % int(round(visibleSize.width - allLand[allLand.size()-1]->getContentSize().width));
		allLand[allLand.size()-1]->setPosition(Vec2(x, offset*(allLand.size())));
		addChild(allLand[allLand.size() - 1]);
	}
}

/*
void JumpGame::jumRightAnimation(Sprite *sprite)
{

	auto moveX = MoveBy::create(duration, Vec2(visibleSize.width - 100, 0));
	auto moveY = MoveBy::create(duration/2, Vec2(0, 100));
	auto moveYAll = Sequence::create(moveY, moveY->reverse(), nullptr);
	auto rotate = RotateBy::create(duration, 360);

	sprite->runAction(Spawn::create(moveX, moveYAll, rotate, nullptr));
}

void JumpGame::jumLeftAnimation(Sprite *sprite)
{
	auto moveX = MoveBy::create(duration, Vec2(-(visibleSize.width - 100), 0));
	auto moveY = MoveBy::create(duration/2, Vec2(0, 100));
	auto moveYAll = Sequence::create(moveY, moveY->reverse(), nullptr);
	auto rotate = RotateBy::create(duration, -360);

	sprite->runAction(Spawn::create(moveX, moveYAll, rotate, nullptr));
}

void JumpGame::createBird()
{
	
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("Jump/bird.plist");
	Vector<SpriteFrame*> birdAni;
	birdAni.pushBack(spritecache->getSpriteFrameByName("1.png"));
	birdAni.pushBack(spritecache->getSpriteFrameByName("2.png"));
	birdAni.pushBack(spritecache->getSpriteFrameByName("3.png"));
	birdAni.pushBack(spritecache->getSpriteFrameByName("4.png"));
	birdAni.pushBack(spritecache->getSpriteFrameByName("5.png"));
	birdAni.pushBack(spritecache->getSpriteFrameByName("4.png"));
	birdAni.pushBack(spritecache->getSpriteFrameByName("3.png"));
	birdAni.pushBack(spritecache->getSpriteFrameByName("2.png"));
	Animation *animation = Animation::createWithSpriteFrames(birdAni, 0.1f);
	Animate *animate = Animate::create(animation);
	auto bird = Sprite::createWithSpriteFrame(birdAni.front());
	resetBird(bird);
	addChild(bird);
	bird->runAction(RepeatForever::create(animate));
	bird->setPosition(birdLeftPos);
	auto body = PhysicsBody::createBox(bird->getContentSize() - Size(10, 10), PhysicsMaterial(1, 1, 1));
	body->setContactTestBitmask(CONTACT_TEST_BITMASK);
	body->setGravityEnable(false);
	//body->setDynamic(false);
	bird->setPhysicsBody(body);
	bird->setTag(SPRITE_TAG::BIRD);
	canCreate = false;
}

void JumpGame::animationBird(Node *sprite)
{
	if (sprite->getPositionX() < visibleSize.width / 2) {
		auto moveX = MoveBy::create(1, Vec2((visibleSize.width - 100), -visibleSize.height/2));
		auto rotate = RotateTo::create(0.1, 45);
		sprite->runAction(Spawn::create(moveX, rotate, nullptr));
	}
}

void JumpGame::resetBird(Sprite *sprite)
{
	sprite->setVisible(true);
	sprite->setRotation(0);
}

*/