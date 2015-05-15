#include "ParticleSystem.h"


Scene* ParticleSystemTest::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
	auto layer = ParticleSystemTest::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	auto infoLayer = InforLayer::create();
	scene->addChild(infoLayer);
	return scene;
}

bool ParticleSystemTest::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	

	this->scheduleUpdate();

	auto button = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button->setTouchEnabled(true);
	button->setTitleFontSize(30);
	button->setTitleText("Clean");
	button->setPosition(Vec2(visibleSize.width - button->getContentSize().width / 2, 200));
	button->addTouchEventListener(CC_CALLBACK_2(ParticleSystemTest::clickClean, this));
	addChild(button);
	auto button1 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button1->setTouchEnabled(true);
	button1->setTitleFontSize(30);
	button1->setTitleText("Back");
	button1->setPosition(Vec2(visibleSize.width - button1->getContentSize().width / 2, visibleSize.height-button1->getContentSize().height));
	button1->addTouchEventListener(CC_CALLBACK_2(ParticleSystemTest::clickBack, this));
	addChild(button1);
	auto button2 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button2->setTouchEnabled(true);
	button2->setTitleFontSize(30);
	button2->setTitleText("Rain");
	button2->setPosition(Vec2(button2->getContentSize().width / 2, 200));
	button2->addTouchEventListener(CC_CALLBACK_2(ParticleSystemTest::clickRain, this));
	addChild(button2);
	auto button3 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button3->setTouchEnabled(true);
	button3->setTitleFontSize(30);
	button3->setTitleText("Snow");
	button3->setPosition(Vec2(button2->getContentSize().width / 2, 100));
	button3->addTouchEventListener(CC_CALLBACK_2(ParticleSystemTest::clickSnow, this));
	addChild(button3);

	auto butto4 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	butto4->setTouchEnabled(true);
	butto4->setTitleFontSize(30);
	butto4->setTitleText("CAMERA");
	butto4->setPosition(Vec2(butto4->getContentSize().width / 2, 300));
	butto4->addTouchEventListener(CC_CALLBACK_2(ParticleSystemTest::switchCamera, this));
	addChild(butto4);

	return true;
}
void ParticleSystemTest::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	this->setAccelerometerEnabled(true);
	auto aListener = EventListenerAcceleration::create(CC_CALLBACK_2(ParticleSystemTest::onAccleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(aListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(ParticleSystemTest::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(ParticleSystemTest::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(ParticleSystemTest::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(ParticleSystemTest::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto mouse = FlowerMouse::create(Size(1, 1), "Flower");
	mouse->setTag(10);
	mouse->setPosition(Vec2(-500, -500));
	addChild(mouse, 100);
}
void ParticleSystemTest::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();

}

bool ParticleSystemTest::onTouchBegan(Touch* touch, Event* evnet) {
	auto location = touch->getLocation();
	auto mouse = getChildByTag(10);
	mouse->setPosition(location - Vec2(mouse->getContentSize().width / 2, mouse->getContentSize().height / 2));

	int a = rand() % 9 + 1;
	switch (a)
	{
	case 1:
		cocos2d::log("SUN");
		createSun(location);
		break;
	case 2:
		cocos2d::log("Rain");
		createRain();
		break;
	case 3:
		cocos2d::log("FIRE");
		createFire(location);
		break;
	case 4:
		cocos2d::log("FIREworks");
		createFireworks(location);
		break;
	case 5:
		cocos2d::log("Smoke");
		createSmoke(location);
		break;
	case 6:
		cocos2d::log("Explosion");
		createExplotion(location);
		break;
	case 7:
		cocos2d::log("Flower");
		createFlower(location);
		break;
	case 8:
		cocos2d::log("Galaxy");
		createGalaxy(location);
		break;
	case 9:
		cocos2d::log("Snow");
		createSnow();
		break;

	default:
		break;
	}
	return true;
}
void ParticleSystemTest::onTouchEnded(Touch* touch, Event* event) {

}
void ParticleSystemTest::onTouchMoved(Touch* touch, Event* event){
	Vec2 touchLocation = touch->getLocation();
	auto mouse = getChildByTag(10);
	mouse->setPosition(touchLocation - Vec2(mouse->getContentSize().width / 2, mouse->getContentSize().height / 2));
}
void ParticleSystemTest::update(float dt) {

}
void ParticleSystemTest::onAccleration(Acceleration *pAccelerationValue, Event *event) {
	cocos2d::log("accleration");

}
bool ParticleSystemTest::onContactBegin(const PhysicsContact &contact) {
	cocos2d::log("contact");

	return true;
}


ParticleSystemTest::ParticleSystemTest() {
	cocos2d::log("On contruct");

}
ParticleSystemTest::~ParticleSystemTest() {
	cocos2d::log("On ParticleSystemTest Destruct");

}

void ParticleSystemTest::createSun(Vec2 point)
{
	auto m_emitter = ParticleSnow::createWithTotalParticles(1);
	m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("sun.png"));
	m_emitter->setDuration(-1);
	m_emitter->setGravity(Vec2(0, 0));
	/*m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);
	m_emitter->setRadialAccel(50);
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);*/
	m_emitter->setPosition(point);
	m_emitter->setPosVar(Vec2(400, 0));
	m_emitter->setLife(4);
	m_emitter->setLifeVar(2);
	m_emitter->setStartSpin(30);
	m_emitter->setStartSpinVar(60);
	m_emitter->setEndSpin(60);
	m_emitter->setEndSpinVar(60);
	m_emitter->setStartColor(Color4F(255, 255, 255, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(0, 0, 0, 1));
	m_emitter->setEndColorVar(Color4F(255, 255, 255, 0));
	m_emitter->setStartSize(30);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(20.0f);
	m_emitter->setEndSizeVar(0);
	m_emitter->setEmissionRate(100);
	m_emitter->setScale(5);
	m_emitter->setTag(1);
	addChild(m_emitter);
}

void ParticleSystemTest::createRain()
{
	auto m_emitter = ParticleSnow::createWithTotalParticles(1000);
	m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("rain.png"));
	m_emitter->setDuration(-1);
	m_emitter->setGravity(Vec2(0, -200));
	m_emitter->setAngle(0);
	m_emitter->setAngleVar(0);
	m_emitter->setRadialAccel(0);
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);
	m_emitter->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
	m_emitter->setPosVar(Vec2(400, 0));
	m_emitter->setLife(4);
	m_emitter->setLifeVar(2);
	m_emitter->setStartSpin(0);
	m_emitter->setStartSpinVar(0);
	m_emitter->setEndSpin(0);
	m_emitter->setEndSpinVar(0);
	m_emitter->setStartColor(Color4F(255, 255, 255, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(255, 255, 255, 1));
	m_emitter->setEndColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setStartSize(30);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(20.0f);
	m_emitter->setEndSizeVar(0);
	m_emitter->setEmissionRate(100);
	m_emitter->setTag(1);
	addChild(m_emitter);
}

void ParticleSystemTest::createFire(Vec2 point)
{
	auto m_emitter = ParticleSnow::createWithTotalParticles(1);
	//m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("fire.png"));
	m_emitter->setDuration(-1);
	m_emitter->setGravity(Vec2(0, -0));
	/*m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);
	m_emitter->setRadialAccel(50);
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);*/
	m_emitter->setPosition(point);/*
	m_emitter->setPosVar(Vec2(400, 0));
	m_emitter->setLife(4);
	m_emitter->setLifeVar(2);
	m_emitter->setStartSpin(30);
	m_emitter->setStartSpinVar(60);
	m_emitter->setEndSpin(60);
	m_emitter->setEndSpinVar(60);
	m_emitter->setStartColor(Color4F(255, 255, 255, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(0, 0, 0, 1));
	m_emitter->setEndColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setStartSize(30);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(20.0f);
	m_emitter->setEndSizeVar(0);
	m_emitter->setEmissionRate(100); */
	m_emitter->setTag(1);
	m_emitter->setScale(5);
	addChild(m_emitter);
}

void ParticleSystemTest::createFireworks(Vec2 point)
{
	auto m_emitter = ParticleSnow::createWithTotalParticles(10);
//	m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("firework.png"));
	m_emitter->setDuration(-1);
	m_emitter->setGravity(Vec2(0, 0));
	/*m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);
	m_emitter->setRadialAccel(50);
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);*/
	m_emitter->setPosition(point);
	/*m_emitter->setPosVar(Vec2(400, 0));
	m_emitter->setLife(4);
	m_emitter->setLifeVar(2);
	m_emitter->setStartSpin(30);
	m_emitter->setStartSpinVar(60);
	m_emitter->setEndSpin(60);
	m_emitter->setEndSpinVar(60);
	m_emitter->setStartColor(Color4F(255, 255, 255, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(0, 0, 0, 1));
	m_emitter->setEndColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setStartSize(30);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(20.0f);
	m_emitter->setEndSizeVar(0);
	m_emitter->setEmissionRate(100); */
	m_emitter->setTag(1);
	m_emitter->setScale(10);
	addChild(m_emitter);
}

void ParticleSystemTest::createSmoke(Vec2 point)
{
	auto m_emitter = ParticleSnow::createWithTotalParticles(1);
//	m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("node1.png"));
	/*m_emitter->setDuration(-1);
	m_emitter->setGravity(Vec2(0, -200));
	m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);
	m_emitter->setRadialAccel(50);
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);*/
	m_emitter->setPosition(point);
	/*m_emitter->setPosVar(Vec2(400, 0));
	m_emitter->setLife(4);
	m_emitter->setLifeVar(2);
	m_emitter->setStartSpin(30);
	m_emitter->setStartSpinVar(60);
	m_emitter->setEndSpin(60);
	m_emitter->setEndSpinVar(60);
	m_emitter->setStartColor(Color4F(255, 255, 255, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(0, 0, 0, 1));
	m_emitter->setEndColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setStartSize(30);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(20.0f);
	m_emitter->setEndSizeVar(0);
	m_emitter->setEmissionRate(100); */
	m_emitter->setTag(1);
	addChild(m_emitter);
}

void ParticleSystemTest::createExplotion(Vec2 point)
{
	auto m_emitter = ParticleSnow::createWithTotalParticles(1);
	//m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("explo.png"));
	m_emitter->setDuration(-1);
	m_emitter->setGravity(Vec2(0, 0));
	/*m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);
	m_emitter->setRadialAccel(50);
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);*/
	m_emitter->setPosition(point);
	/*m_emitter->setPosVar(Vec2(400, 0));
	m_emitter->setLife(4);
	m_emitter->setLifeVar(2);
	m_emitter->setStartSpin(30);
	m_emitter->setStartSpinVar(60);
	m_emitter->setEndSpin(60);
	m_emitter->setEndSpinVar(60);
	m_emitter->setStartColor(Color4F(255, 255, 255, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(0, 0, 0, 1));
	m_emitter->setEndColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setStartSize(30);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(20.0f);
	m_emitter->setEndSizeVar(0);
	m_emitter->setEmissionRate(100); */
	m_emitter->setTag(1);
	m_emitter->setScale(10);
	addChild(m_emitter);
}

void ParticleSystemTest::createFlower(Vec2 point)
{
	auto m_emitter = ParticleSnow::createWithTotalParticles(1);
	//m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("flower.png"));
	m_emitter->setDuration(-1);
	m_emitter->setGravity(Vec2(0, 0));
	/*m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);
	m_emitter->setRadialAccel(50);
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);*/
	m_emitter->setPosition(point);
	/*m_emitter->setPosVar(Vec2(400, 0));
	m_emitter->setLife(4);
	m_emitter->setLifeVar(2);
	m_emitter->setStartSpin(30);
	m_emitter->setStartSpinVar(60);
	m_emitter->setEndSpin(60);
	m_emitter->setEndSpinVar(60);
	m_emitter->setStartColor(Color4F(255, 255, 255, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(0, 0, 0, 1));
	m_emitter->setEndColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setStartSize(30);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(20.0f);
	m_emitter->setEndSizeVar(0);
	m_emitter->setEmissionRate(100); */
	m_emitter->setTag(1);
	m_emitter->setScale(5);
	addChild(m_emitter);
}

void ParticleSystemTest::createGalaxy(Vec2 point)
{
	auto m_emitter = ParticleSnow::createWithTotalParticles(1000);
	//m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("node1.png"));
	/*m_emitter->setDuration(-1);
	m_emitter->setGravity(Vec2(0, -200));
	m_emitter->setAngle(90);
	m_emitter->setAngleVar(360);
	m_emitter->setRadialAccel(50);
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(30);
	m_emitter->setTangentialAccelVar(0);*/
	m_emitter->setPosition(point);
	/*m_emitter->setPosVar(Vec2(400, 0));
	m_emitter->setLife(4);
	m_emitter->setLifeVar(2);
	m_emitter->setStartSpin(30);
	m_emitter->setStartSpinVar(60);
	m_emitter->setEndSpin(60);
	m_emitter->setEndSpinVar(60);
	m_emitter->setStartColor(Color4F(255, 255, 255, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(0, 0, 0, 1));
	m_emitter->setEndColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setStartSize(30);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(20.0f);
	m_emitter->setEndSizeVar(0);
	m_emitter->setEmissionRate(100); */
	m_emitter->setTag(1);
	addChild(m_emitter);
}

void ParticleSystemTest::createSnow()
{
	auto m_emitter = ParticleSnow::createWithTotalParticles(1000);
	m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("node1.png"));
	m_emitter->setDuration(-1);
	m_emitter->setGravity(Vec2(0, -10));
	m_emitter->setAngle(90); //xoay
	m_emitter->setAngleVar(360);
	m_emitter->setRadialAccel(0); //roi tack nhau
	m_emitter->setRadialAccelVar(0);
	m_emitter->setTangentialAccel(0);
	m_emitter->setTangentialAccelVar(0);
	m_emitter->setPosition(Vec2(visibleSize.width / 2, visibleSize.height-100));
	m_emitter->setPosVar(Vec2(400, 0));
	m_emitter->setLife(3);
	m_emitter->setLifeVar(1);
	m_emitter->setSpeed(130);
	m_emitter->setSpeedVar(30);
	m_emitter->setStartSpin(30);
	m_emitter->setStartSpinVar(60);
	m_emitter->setEndSpin(60);
	m_emitter->setEndSpinVar(60);
	m_emitter->setStartColor(Color4F(255, 255, 255, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(255, 255, 255, 1));
	m_emitter->setEndColorVar(Color4F(255, 255, 255, 255));
	m_emitter->setStartSize(30);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(20.0f);
	m_emitter->setEndSizeVar(0);
	m_emitter->setEmissionRate(m_emitter->getTotalParticles()/m_emitter->getLife());
	m_emitter->setTag(1);
	addChild(m_emitter);
}

void ParticleSystemTest::clickClean(Ref *pSender, Widget::TouchEventType type)
{
	while (getChildByTag(1)!=nullptr)
	{
		removeChildByTag(1);
	}
}

void ParticleSystemTest::clickBack(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		back();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}

void ParticleSystemTest::clickRain(Ref *pSender, Widget::TouchEventType type)
{
	createRain();
}

void ParticleSystemTest::clickSnow(Ref *pSender, Widget::TouchEventType type)
{
	createSnow();
}

void ParticleSystemTest::back()
{
	auto scene = GameOverScene::createScene(-1);
	Director::getInstance()->replaceScene(TransitionFadeDown::create(1, scene));
}

void ParticleSystemTest::switchCamera(Ref *pSender, Widget::TouchEventType type)
{
	Camera *ca = Director::getInstance()->getRunningScene()->getCameras().front();
	auto move = MoveBy::create(10, Vec2(visibleSize.width, 200));
	ca->runAction(Sequence::create(move,move->reverse(),nullptr));
}

