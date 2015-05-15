#include "SpriteSheetScene.h"

Scene* SpriteSheetScene::createScene(int mode,int ui) {
	auto scene = cocos2d::Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_CONTACT);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, -100.0f));
	auto layer = SpriteSheetScene::create(mode,ui);
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}
SpriteSheetScene* SpriteSheetScene::create(int mode, int ui) {
	SpriteSheetScene *layer = new SpriteSheetScene();
	if (layer->init(mode,ui)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
bool SpriteSheetScene::init(int mode, int ui) {
	if (!Layer::init()) {
		return false;
	}
	gameLevel = mode;
	gameUIMode = ui;
	UserDefault::getInstance()->setIntegerForKey(LEVEL, mode);
	UserDefault::getInstance()->setIntegerForKey(UIMODE, ui);
	srand(time(NULL));
	size1 = Director::getInstance()->getWinSize();
	_backButton = Sprite::create("pause.png");
	_backButton->setPosition(Vec2(size1.width - _backButton->getContentSize().width, size1.height - _backButton->getContentSize().height / 2));
	addChild(_backButton);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(SpriteSheetScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SpriteSheetScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SpriteSheetScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(SpriteSheetScene::onTouchCancelled, this);
	touchListener->setEnabled(true);
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	///ADD Label
	scoreView = Label::create("Score: 0", "fonts/2.ttf", 40);
	scoreView->setTextColor(Color4B(236, 183, 42, 200));
	addChild(scoreView, -1);
	scoreView->setPosition(Vec2(scoreView->getContentSize().width, size1.height - scoreView->getContentSize().height));
	
	getScoreView = Label::create("+100", "fonts/2.ttf", 60);
	getScoreView->setVisible(false);
	getScoreView->setTextColor(Color4B(212, 232, 11, 255));
	addChild(getScoreView, 3);
	//getScoreView->setPosition(scoreView->getPosition().x + 75, scoreView->getPosition().y - getScoreView->getContentSize().height / 2);
	
	comboView = Label::create("0", "fonts/2.ttf", 50);
	comboView->setTextColor(Color4B(255, 45, 87, 180));
	addChild(comboView, -1);
	comboView->setPosition(Vec2(size1.width / 2, size1.height - comboView->getContentSize().height));
	
	timeSlider = Slider::create();
	timeSlider->loadBarTexture("Button/bar_background.png");
	timeSlider->loadSlidBallTextures("Button/star.png", "Button/star.png", "");
	timeSlider->loadProgressBarTexture("Button/remain.png");
	timeSlider->setPercent(100);
	timeSlider->setScale9Enabled(true);
	timeSlider->setTouchEnabled(false);
	timeSlider->setCapInsets(Rect(0, 0, 0, 0));
	timeSlider->setContentSize(Size(250.0f, 19));
	timeSlider->setPosition(Vec2(size1.width / 2, size1.height - comboView->getContentSize().height - timeSlider->getContentSize().height*3));
	addChild(timeSlider, 1);
	timeSlider->setScale(size1.width*0.5 / timeSlider->getContentSize().width);

	timeView = Label::create("60", "fonts/2.ttf", 50);
	timeView->setPosition(Vec2(timeSlider->getPosition().x + (timeSlider->getContentSize().width / 2)*timeSlider->getScaleX() + 50, timeSlider->getPosition().y));
	addChild(timeView, -1);

	///SPRITE SHEET ANIMATION TEST///
	auto edbody = PhysicsBody::createEdgeBox(size1, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(size1.width / 2, size1.height / 2));
	edgeNode->setPhysicsBody(edbody);
	this->addChild(edgeNode);

	magicMouse = FlowerMouse::create(Size(100, 100), "Flower");
	magicMouse->setPosition(Vec2(-200, -200));
	addChild(magicMouse, 100);


	/*

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("AnimBear.plist");
	auto ss = SpriteBatchNode::create("AnimBear.png");
	this->addChild(ss);
	Vector<SpriteFrame*> af(8);
	char name[30] = { 0 };
	for (int i = 1; i < 9; i++)
	{
		sprintf(name, "bear%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		af.pushBack(frame);
	}
	Animation *animation = Animation::createWithSpriteFrames(af,0.2f);
	_ballMan = Sprite::createWithSpriteFrameName("bear1.png");
	_ballMan->setPosition(Vec2(size.width / 2, size.height / 2));
	walkAction = RepeatForever::create(Animate::create(animation));
	walkAction->retain();
	ss->addChild(_ballMan);
	_ballMan->runAction(walkAction);
	auto body = PhysicsBody::createBox(_ballMan->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	//body->setDynamic(false);
	body->setContactTestBitmask(CONTACT_TEST_BITMASK);
	_ballMan->setPhysicsBody(body);
	SimpleSpriteCreator* sprite1 = SimpleSpriteCreator::createWithImage("ball.png");
	addChild(sprite1);
	auto bd1 = PhysicsBody::createCircle(sprite1->getContentSize().width/2, PHYSICSBODY_MATERIAL_DEFAULT);
	bd1->setContactTestBitmask(CONTACT_TEST_BITMASK);
	sprite1->setPhysicsBody(bd1);
	sprite1->setPosition(Vec2(200, 400));
	SimpleSpriteCreator* sprite2 = SimpleSpriteCreator::createWithImage("replay.png");
	addChild(sprite2);
	auto bd2 = PhysicsBody::createCircle(sprite2->getContentSize().width/2, PHYSICSBODY_MATERIAL_DEFAULT);
	bd2->setContactTestBitmask(CONTACT_TEST_BITMASK);
	sprite2->setPhysicsBody(bd2);
	sprite2->setPosition(Vec2(200, 200));
	onGavity = Label::create("Gavity OFF","fonts/3.ttf",50);
	onDynamic = Label::create("Dynamic ON", "fonts/3.ttf", 50);
	onDebugDraw = Label::create("Draw ON", "fonts/3.ttf", 50);
	onClean = Label::create("CLEAN", "fonts/3.ttf", 50);
	onGavity->setPosition(Vec2(size.width - onGavity->getContentSize().width / 2,200));
	onDynamic->setPosition(Vec2(size.width - onDynamic->getContentSize().width / 2, 100));
	onDebugDraw->setPosition(Vec2(size.width - onDebugDraw->getContentSize().width / 2, 300));
	onClean->setPosition(Vec2(size.width - onClean->getContentSize().width / 2, 400));
	addChild(onGavity);
	addChild(onDynamic);
	addChild(onDebugDraw);
	addChild(onClean); */
	
	_posaray = new std::vector<Vec2*>();
	_fingerPos = nullptr;
	return true;
}
void SpriteSheetScene::update(float dt) {
	auto screenSize = Director::getInstance()->getWinSize();
	if (allSprite.size()<30)
	{
		auto sprite = randomSprite();
		//sprite->setTag(TAG_CLEAN);
		allSprite.push_back(sprite);
		addChild(allSprite[allSprite.size() - 1]);
		allSprite[allSprite.size() - 1]->setPosition(Vec2(100 + rand() % (int(screenSize.width - 250)), screenSize.height - 200));
	}
	std::stringstream text;
	text << "Score: " << gameScore << std::endl;
	string str = text.str().c_str();
	scoreView->setString(str);
	///Time update

	time(&timer);
	int seconds = ceil(difftime(mktime(&day), timer));
	std::stringstream time;
	
	//if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32) {
		if (seconds != oldSecond) {
			remaintime--;
			percent = round((remaintime * 100)/60);
			cocos2d::log("%d --- %d", percent,remaintime);
			oldSecond = seconds;
		}
	//}
	//else {
	//	remaintime = seconds;
	//}
	if (remaintime == 0) {
		PopLayer1 *pop = PopLayer1::create(Color4B(0, 0, 0, 180),gameScore);
		getParent()->addChild(pop);
		Director::getInstance()->pause();
	}
	time << remaintime << std::endl;
	timeView->setString(time.str().c_str());
	timeSlider->setPercent/*cocos2d::log*/(/*"%d",*/percent);
	
	if (percent == 25) {
		timeSlider->loadSlidBallTextureNormal("Button/boom.png");
		timeSlider->loadProgressBarTexture("Button/remain2.png");
	}

	if (_fingerPos != nullptr) {
		_posaray->push_back(_fingerPos);
	}

	/*DrawLine* node = DrawLine::create(_posaray);
	addChild(node, 100);
	_posaray->clear(); */
}


void SpriteSheetScene::onEnterTransitionDidFinish() {
	time(&timer);
	timeinfo = localtime(&timer);
	day.tm_year = timeinfo->tm_year;
	day.tm_mon = timeinfo->tm_mon;
	day.tm_mday = timeinfo->tm_mday;
	day.tm_hour = timeinfo->tm_hour;
	day.tm_min = timeinfo->tm_min + 1;
	day.tm_sec = timeinfo->tm_sec;
	this->scheduleUpdate();
}
Sprite* SpriteSheetScene::randomSprite() {

	cocos2d::Sprite* temp = cocos2d::Sprite::create();
	PhysicsBody *body;
	char imagePath[20] = { 0 };
	char bodyPath[30] = { 0 };
	char bodyName[10] = { 0 };
	char nameStr[10] = { 0 };
	int type = rand() % gameLevel + 1;

	sprintf(imagePath, "image/%d/%d.png", gameUIMode,type);
	sprintf(bodyPath, "image/%d/body/%d.json", gameUIMode, type);
	sprintf(nameStr, "name%d",type);
	sprintf(bodyName, "%d", type);
	temp = /*SimpleSpriteCreator::createWithImage*/Sprite::create(imagePath);
	temp->setName(nameStr);
	MyBodyParser::getInstance()->parseJsonFile(bodyPath);
	body = MyBodyParser::getInstance()->bodyFormJson(temp, bodyName);
	body->setContactTestBitmask(CONTACT_TEST_BITMASK);
	temp->setPhysicsBody(body);
	temp->getPhysicsBody()->setGravityEnable(true);
	temp->getPhysicsBody()->getShape(0)->setDensity(10.0f);
	temp->setTag(SPRITE_TAG::NOR);
	return temp;

}
bool SpriteSheetScene::onTouchBegan(Touch* touch, Event* event) {
	cocos2d::log("TOuch begin");
	Vec2 point = touch->getLocation();
	magicMouse->setPosition(point - Vec2(magicMouse->getContentSize().width / 2, magicMouse->getContentSize().height / 2));

	Rect rec = _backButton->getBoundingBox();

	if (rec.containsPoint(point)) {
		/*auto scene = GameOverScene::createScene(-1);
		Director::getInstance()->replaceScene(TransitionFlipAngular::create(2,scene));*/
		PopLayer *pop = PopLayer::create(Color4B(25, 25, 25, 150), 2);
		getParent()->addChild(pop);
		Director::getInstance()->pause();
		return false;
	}
	/*rec = onGavity->getBoundingBox();
	if (rec.containsPoint(point)) {
		if (_myWorld->getGravity().isZero()) {
			_myWorld->setGravity(Vect(0.0f, -100.0f));
			onGavity->setString("Gavity ON");
		}
		else {
			_myWorld->setGravity(Vect(0.0f, 0.0f));
			onGavity->setString("Gavity OFF");
			auto allbody = _myWorld->getAllBodies();
			for (auto bd : allbody) {
				bd->setVelocity(Vect(0,0));
			}
		}
		return false;
	}
	rec = onDynamic->getBoundingBox();
	if (rec.containsPoint(point)) {
		if (_ballMan->getPhysicsBody()->isDynamic()) {
			_ballMan->getPhysicsBody()->setDynamic(false);
			onDynamic->setString("Dynamic OFF");
		}
		else {
			_ballMan->getPhysicsBody()->setDynamic(true);
			onDynamic->setString("Dynamic ON");
		}
		return false;
	}
	if (onDebugDraw->getBoundingBox().containsPoint(point)) {
		if (_myWorld->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE) {
			_myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
			onDebugDraw->setString("Draw OFF");
		}
		else {
			_myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
			onDebugDraw->setString("Draw ON");
		}
		return false;
	}
	if (onClean->getBoundingBox().containsPoint(point)) {
		while (getChildByTag(TAG_CLEAN) != nullptr){
			removeChildByTag(TAG_CLEAN);
		}
		return false;
	}*/
	//cocos2d::log("%d", _ballMan->getNumberOfRunningActions());
	prePoint = point;
	//allPoint.push_back(prePoint);
	return true;
}
void SpriteSheetScene::onTouchEnded(Touch* touch, Event* event)
{
	Vec2 point = touch->getLocation();
	//allPoint.push_back(point);
	
	/*if (_ballMan->getNumberOfRunningActions() < 2) {
		float vecloc = 200;
		
		auto cur = _ballMan->getPosition();
		if ((point.x > cur.x)) {
			_ballMan->setFlippedX(true);
		}
		if ((point.x < cur.x)) {
			_ballMan->setFlippedX(false);
		}
		auto distance = sqrt(pow(point.x - cur.x, 2) + pow(point.y - cur.y, 2));
		auto time = distance / vecloc;

		auto moveBear = MoveTo::create(time, point);
		_ballMan->runAction(moveBear);
	} */
	if (touchedSpritesIndex.size() > 0) {
		missName = touchedSpritesIndex[0]->getName();
		for (int i = 0; i < touchedSpritesIndex.size(); i++)
		{
			if (touchedSpritesIndex[i]->getName() == missName && onbreak == false) {
				//touchedSpritesIndex[i]->runAction(TintTo::create(1, 12, 2555, 41));
				touchedSpritesIndex[i]->setTag(SPRITE_TAG::DELETE);
				maxCombo++;
			}
			else {
				onbreak = true;
				//touchedSpritesIndex[i]->runAction(TintTo::create(0., 255, 255, 255));
				touchedSpritesIndex[i]->setTag(SPRITE_TAG::NOR);
				touchedSpritesIndex[i]->setScale(1);
			}
		}
		/*while (touchedSpritesIndex.size()>0)
		{
			touchedSpritesIndex.pop_back();
		} */
		touchedSpritesIndex.clear();
		for (int i = 0; i < allSprite.size();i++) {
			if (allSprite[i]->getTag() == SPRITE_TAG::DELETE) {
				removeChild(allSprite[i]);
				allSprite.erase(allSprite.begin() + i);
				i -= 1;
			}
			else {
				allSprite[i]->runAction(TintTo::create(0.1f, 255, 255, 255));
			}
		}
		onbreak = false;
		if (maxCombo > 1) {
			int multi = 1;
			if (maxCombo < 3) {
				multi = 1;
			}
			else if(maxCombo < 6) {
				multi = 2;
			}
			else if (maxCombo < 8) {
				multi = 3;
			}
			else if (maxCombo < 10) {
				multi = 4;
			}
			else {
				multi = 5;
			}
			gameScore = gameScore + maxCombo*multi*(gameLevel-3);
			comboView->setScale(1.0f);
			auto scale = ScaleBy::create(0.3, 1.5f);
			comboView->runAction(Sequence::create(scale, scale->reverse(), nullptr));
			std::stringstream text;
			text << "" << maxCombo << std::endl;
			string str = text.str().c_str();
			comboView->setString(str);
			getScoreView->setPosition(point);
			getScoreView->setVisible(true);
			getScoreView->setString(numberToString("+", maxCombo*multi*(gameLevel - 3)));
			getScoreView->runAction(Sequence::create(FadeOut::create(0.6f),CallFunc::create(this,callfunc_selector(SpriteSheetScene::resetOpa)),nullptr));
		}
		maxCombo = 0;
	}
	while (getChildByTag(SPRITE_TAG::CUSOR) != nullptr)
	{
		removeChildByTag(SPRITE_TAG::CUSOR);
	}
}
string SpriteSheetScene::numberToString(string temp, int number) {
	std::stringstream text;
	text << temp << number;
	return text.str().c_str();
}
void SpriteSheetScene::resetOpa() {
	getScoreView->setOpacity(255);
	getScoreView->setVisible(false);
}
void SpriteSheetScene::onTouchMoved(Touch* touch, Event* event)
{
	//cocos2d::log("touch moved");
	getTouchedSprite(prePoint);
	auto poit = touch->getLocation();
	magicMouse->setPosition(poit - Vec2(magicMouse->getContentSize().width / 2, magicMouse->getContentSize().height / 2));
	if ((poit - prePoint).getLength() > 10) {
		//allPoint.push_back(poit);
		_fingerPos = new Vec2(poit);
		//createCusor(poit);
		prePoint = poit;
	}
	else {
		_fingerPos = nullptr;
	}
	
}
void SpriteSheetScene::getTouchedSprite(Vec2 point) {
	for(int index = 0; index < allSprite.size();index++)
	{
		if (checkCondition(allSprite[index],point) == true && allSprite[index]->getTag() != SPRITE_TAG::ADD) {
			allSprite[index]->setTag(SPRITE_TAG::ADD);
			allSprite[index]->runAction(TintBy::create(0.1f, 45, 45, 45));
			touchedSpritesIndex.push_back(allSprite[index]);
		}
		else {
			//cocos2d::log("ELSE");
		}
	}

}
bool SpriteSheetScene::checkCondition(Sprite* sprite, Vec2 point) {
	if (sprite == nullptr) return false;
	Vec2 po = sprite->getPosition();
	Vec2 distance = po - point;
	if (distance.getLength() < allSprite[0]->getContentSize().width/2-15) {
		//cocos2d::log("True");
		return true;
	}
	return false;
}
void SpriteSheetScene::onTouchCancelled(Touch* touch, Event* event)
{
	//cocos2d::log("touch cancelled");

}
SpriteSheetScene::SpriteSheetScene()
{
}

SpriteSheetScene::~SpriteSheetScene()
{
}

void SpriteSheetScene::createCusor(Vec2 point)
{
	auto m_emitter = ParticleSnow::createWithTotalParticles(30);
	m_emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("node1.png"));
	m_emitter->setDuration(-1);
	m_emitter->setGravity(Vec2(0, 0));
	/*m_emitter->setAngle(90); //xoay
	m_emitter->setAngleVar(360);
	*/m_emitter->setPosition(point);
	//m_emitter->setPosVar(point);
	m_emitter->setLife(3);
	m_emitter->setLifeVar(1);
	m_emitter->setSpeed(30);
	m_emitter->setSpeedVar(2);
	/*m_emitter->setStartSpin(30);
	m_emitter->setStartSpinVar(60);
	m_emitter->setEndSpin(60);
	m_emitter->setEndSpinVar(60);*/
	m_emitter->setStartColor(Color4F(255, 255, 255, 1));
	m_emitter->setStartColorVar(Color4F(0, 0, 0, 0));
	m_emitter->setEndColor(Color4F(255, 255, 255, 1));
	m_emitter->setEndColorVar(Color4F(255, 255, 255, 255));
	/*m_emitter->setStartSize(30);
	m_emitter->setStartSizeVar(0);
	m_emitter->setEndSize(20.0f);
	m_emitter->setEndSizeVar(0);*/
	m_emitter->setAutoRemoveOnFinish(true);
	m_emitter->setContentSize(Size(30, 30));
	m_emitter->setEmissionRate(m_emitter->getTotalParticles() / m_emitter->getLife());
	m_emitter->setTag(SPRITE_TAG::CUSOR);
	m_emitter->setScale(0.5);
	addChild(m_emitter);
}
