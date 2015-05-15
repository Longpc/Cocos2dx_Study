#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);
	auto infoLayer = InforLayer::create();
	scene->addChild(infoLayer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pha.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("base.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("win.mp3");
	auto backGroundLayer = LayerGradient::create(Color4B(182,224,164,200),Color4B(255,198,194,200));
	this->addChild(backGroundLayer);
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    return true;
}
void HelloWorld::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();

	
	
}
void HelloWorld::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	unscheduleUpdate();
	_myWorld->removeAllBodies();
	_eventDispatcher->removeEventListenersForTarget(this);
	removeAllChildrenWithCleanup(true);
}
void HelloWorld::onPause(Ref* sSender) {
	//pause
	Director::getInstance()->pause();
	PopLayer *pop = PopLayer::create(Color4B(15, 15, 15, 150),1);
	getParent()->addChild(pop);
	

}
bool HelloWorld::onTouchBegan(Touch* touch, Event* evnet) {
	//auto location = touch->getLocation();
	//auto arr = this->getScene()->getPhysicsWorld()->getShapes(location);
	Point p = touch->getLocation();
	Rect rect = _closeButon->getBoundingBox();
	if (rect.containsPoint(p)) {
		winGame();
		return false;
	}
	return true;
}
void HelloWorld::onTouchEnded(Touch* touch, Event* event) {

}
void HelloWorld::onTouchMoved(Touch* touch, Event* event){
	Point touchLocation = touch->getLocation();
	_baseLine->setPositionX(touchLocation.x);
}
void HelloWorld::update(float dt) {
	auto pos = _baseLine->getPosition();
	pos.x = _moveX;
	_baseLine->setPosition(pos);
	cocos2d::log("speed x %f/ y %f",_ball->getPhysicsBody()->getVelocity().x,_ball->getPhysicsBody()->getVelocity().y);
	if (abs(_ball->getPhysicsBody()->getVelocity().y ) < 30) {
		countTime++;
		if (countTime == 30) {
			Vect force = Vect(INIT_VECTOR_X, INIT_VECTOR_Y);
			_ball->getPhysicsBody()->applyImpulse(force);
			countTime = 0;
		}
	}
	else {
		countTime = 0;
	}
}
void HelloWorld::onAccleration(Acceleration *pAccelerationValue, Event *event) {
#define DEC 1.0f
#define SPEED 30
	float maxX = visibleSize.width - _baseLine->getContentSize().width / 2;
	float minX = _baseLine->getContentSize().width / 2;

	_moveX = _moveX*DEC + SPEED*pAccelerationValue->x;

	if (_moveX > maxX) {
		_moveX = maxX;
	}
	else if (_moveX < minX) {
		_moveX = minX;
	}
}
bool HelloWorld::onContactBegin(const PhysicsContact &contact) {
	//if (contact.getContactData()->normal.y >= 0) return false;
	auto spriteA = contact.getShapeA()->getBody()->getNode();
	auto spriteB = contact.getShapeB()->getBody()->getNode();

	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();
	if (tagA == SPRITE_TAG::BLOCK) {
		spriteA->removeFromParentAndCleanup(true);
	}
	if (tagB == SPRITE_TAG::BLOCK) {
		spriteB->removeFromParentAndCleanup(true);
	}
	if (tagA == SPRITE_TAG::BLOCK || tagB == SPRITE_TAG::BLOCK) {
		
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pha.wav");
		callUpdateScore(A);
	}
	if (tagA == SPRITE_TAG::BASE || tagB == SPRITE_TAG::BASE) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("base.wav");
	}
	return true;
}
void HelloWorld::callUpdateScore(InforLayer &layer) {
	HelloWorld::gameScore++;
	//cocos2d::log("Game Score: %d", gameScore);
	
	std::stringstream text;
	text << "Score: " << gameScore << std::endl;
	//cocos2d::log("%s", text.str().c_str());
	string str = text.str().c_str();
	gameScoreLabel->setString(str);
	if (gameScore == BLOCKS_NUMBER) {
		//_ball->getPhysicsBody()->setVelocity(Vect(0x0));

		unsigned int winID = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("win.mp3");
		/*DelayTime * delayAction = DelayTime::create(2);
		CallFuncN * callFunc = CallFuncN::create(CC_CALLBACK_1(HelloWorld::callBackFunction,this));//User CC_CALLBACK_0  for direct call Wingame().<No argument>
		this->runAction(Sequence::createWithTwoActions(delayAction, callFunc));*/
		GAFAsset *ass = GAFAsset::create("GAF/leagueWinFireWorksAnimation/leagueWinFireWorksAnimation.gaf", nullptr);

		GAFObject *object = ass->createObject();
		object->setPosition(Vec2(0, visibleSize.height));
		object->setLooped(false);
		object->setAnimationFinishedPlayDelegate(CC_CALLBACK_1(HelloWorld::winAnimationFinishedCallback, this));
		addChild(object, 1000);
		object->start();
		
	}
}
void HelloWorld::callBackFunction(Ref *pSender)
{
	winGame();
}

void HelloWorld::winGame() {
	_ball->getPhysicsBody()->setVelocity(Vect(0,0));
	auto scene = GameOverScene::createScene(gameScore);
	Director::getInstance()->replaceScene(TransitionSlideInT::create(1, scene));
}
void HelloWorld::initBlocks() {

	for (int i = 0; i < BLOCKS_NUMBER; i++)
	{
		blockArray.push_back(createBlockWithRandomNumber(rand() % 4 + 1));

		float randX = rand() % int(visibleSize.width - MARGIN_X*2 )+ MARGIN_X;
		float randy = rand() % int(visibleSize.height/2) + visibleSize.height / 2/* -blockArray[0]->getContentSize().height/2 */- SCORE_MARGIN *2;
		blockArray[i]->setPosition(Vec2(randX, randy));
		auto blockBody = PhysicsBody::createBox(blockArray[i]->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
		blockBody->getShape(0)->setDensity(10.0f);
		blockBody->getShape(0)->setFriction(0.0f);
		blockBody->getShape(0)->setRestitution(1.05f); 
		blockBody->setDynamic(false); 
		blockBody->setContactTestBitmask(CONTACT_TEST_BITMASK);
		//blockBody->setCollisionBitmask(0x00000000); cac vat khac se dam xuyen qua no
		blockArray[i]->setPhysicsBody(blockBody);
		blockArray[i]->setTag(SPRITE_TAG::BLOCK);
		this->addChild(blockArray[i]);
	}
}
Sprite* HelloWorld::createBlockWithRandomNumber(int number) {
	std::stringstream name;
	name << "" << number << ".png";
	return cocos2d::Sprite::create(name.str().c_str());
}
void HelloWorld::toggleOfDebugDraw(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto toggleItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::btnDebugDrawCallback, this));
	toggleItem->setPosition(Point(origin.x + visibleSize.width - toggleItem->getContentSize().width / 2,
		origin.y + toggleItem->getContentSize().height / 2));
	auto menu = Menu::create(toggleItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 100);
}
void HelloWorld::btnDebugDrawCallback(Ref* pSender)
{
	if (_myWorld->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE) {
		_myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	}
	else {
		_myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}

void HelloWorld::onAnimationFinishedPlayCallback(GAFObject * object)
{
	object->stop();
	object->setVisible(false);

	this->setAccelerometerEnabled(true);
	auto aListener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAccleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(aListener, this);
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	body->getShape(0)->setRestitution(1.0f);
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	_ball = Sprite::create("ball.png", Rect(0, 0, 90, 90));
	//_ball->setScale(5.5f);
	_ball->setPosition(visibleSize.width / 2, 100);
	auto ballBd = PhysicsBody::createCircle(_ball->getContentSize().width / 2);
	ballBd->getShape(0)->setRestitution(2.01f);
	ballBd->getShape(0)->setFriction(0.0f);
	ballBd->getShape(0)->setDensity(1.0f);
	ballBd->setGravityEnable(false);
	ballBd->setVelocityLimit(600);
	ballBd->setRotationEnable(true);
	//ballBd->setVelocity(Vec2(100, 100));
	_ball->setPhysicsBody(ballBd);
	ballBd->setContactTestBitmask(CONTACT_TEST_BITMASK);
	_ball->setTag(SPRITE_TAG::BALL);

	this->addChild(_ball);
	auto rotateBall = RotateBy::create(0.5f, 360);
	auto repeatRotate = RepeatForever::create(rotateBall);
	//_ball->runAction(repeatRotate);

	_baseLine = Sprite::create("base.png");
	_baseLine->setTag(SPRITE_TAG::BASE);

	_baseLine->setPosition(visibleSize.width / 2, _baseLine->getContentSize().height);
	auto _baseLineBd = PhysicsBody::createBox(_baseLine->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	_baseLineBd->getShape(0)->setRestitution(1.002f);
	_baseLineBd->getShape(0)->setFriction(0.0f);
	_baseLineBd->getShape(0)->setDensity(10.0f);
	_baseLineBd->setGravityEnable(false); //
	_baseLineBd->setDynamic(false);
	_baseLineBd->setContactTestBitmask(CONTACT_TEST_BITMASK);
	//Vect force2 = Vect(2002000.0f, -2002000.0f); //Vector Luc x,y
	//_baseLineBd->applyImpulse(force2);


	_baseLine->setPhysicsBody(_baseLineBd);

	addChild(_baseLine);
	/*MyBodyParser::getInstance()->parseJsonFile("baseline.json");
	auto _baselineBody = MyBodyParser::getInstance()->bodyFormJson(_baseLine, "baseline");
	if (_baselineBody != nullptr) {
	_baselineBody->setDynamic(false);
	_baselineBody->setContactTestBitmask(CONTACT_TEST_BITMASK);
	_baselineBody->getShape(0)->setRestitution(1.005f);
	_baselineBody->getShape(0)->setFriction(0.0f);
	_baselineBody->getShape(0)->setDensity(1.0f);
	_baselineBody->setGravityEnable(false);
	_baseLine->setPhysicsBody(_baselineBody);
	} */

	_closeButon = Sprite::create("close.png");
	_closeButon->setPosition(Vec2(visibleSize.width - _closeButon->getContentSize().width / 2, visibleSize.height - _closeButon->getContentSize().height / 2));
	addChild(_closeButon);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	srand(time(NULL));
	initBlocks();
	auto dispath = Director::getInstance()->getEventDispatcher();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	dispath->addEventListenerWithSceneGraphPriority(contactListener, this);
	gameScoreLabel = Label::create("Score: 0", "fonts/2.ttf", 35);
	gameScoreLabel->setPosition(Vec2(0 + gameScoreLabel->getContentSize().width, visibleSize.height - SCORE_MARGIN));
	addChild(gameScoreLabel);

	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(35);
	auto menuItemPause = MenuItemFont::create("PAUSE", CC_CALLBACK_1(HelloWorld::onPause, this));
	auto menu = Menu::create(menuItemPause, NULL);
	addChild(menu);
	menu->setPosition(Vec2(0 + gameScoreLabel->getContentSize().width, visibleSize.height - SCORE_MARGIN * 2));


	/*auto winSize = Director::getInstance()->getWinSize();
	Vec2 vec[6] =
	{
	Vec2(winSize.width - 1, winSize.height - 1),
	Vec2(1, winSize.height - 1),
	Vec2(1, 100),
	Vec2(winSize.width / 2, 0),
	Vec2(winSize.width - 1, 100),
	Vec2(winSize.width - 1, winSize.height - 1),
	};
	auto wall = Node::create();
	//wall->setPhysicsBody(PhysicsBody::createEdgeChain(vec, 5, PhysicsMaterial(0.1f, 1.0f, 0.0f)));
	// 密度、反発、摩擦
	wall->setPhysicsBody(PhysicsBody::createEdgeChain(vec, 6, PhysicsMaterial(0.0f, 1.0f, 0.0f)));
	wall->setPosition(0, 0);
	addChild(wall);
	*/

	/*A.addChild(gameScoreLabel);
	if (A.isVisible()){
	cocos2d::log("Visiable");
	} */
	this->scheduleUpdate();
	toggleOfDebugDraw();
	Vect force = Vect(INIT_VECTOR_X, INIT_VECTOR_Y);
	_ball->getPhysicsBody()->applyImpulse(force);

}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	GAFAsset *ass = GAFAsset::create("GAF/gachaRareAnimation/gachaRareAnimation.gaf", nullptr);

	GAFObject *object = ass->createObject();
	object->setPosition(Vec2(0, visibleSize.height));
	object->setLooped(false);
	object->setAnimationFinishedPlayDelegate(CC_CALLBACK_1(HelloWorld::onAnimationFinishedPlayCallback, this));
	addChild(object, 1000);
	object->start();
}

void HelloWorld::winAnimationFinishedCallback(GAFObject * object)
{
	object->stop();
	object->setVisible(false);
	winGame();
}


