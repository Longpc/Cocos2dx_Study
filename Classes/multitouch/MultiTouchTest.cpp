#include "MultiTouchTest.h"

void MultiTouchTest::onEnter()
{
	BaseLayer::onEnter();
	srand(time(NULL));
	this->scheduleUpdate();
}

void MultiTouchTest::onExit()
{
	BaseLayer::onExit();
}

void MultiTouchTest::exitCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionFadeBL::create(1, GameOverScene::createScene(-1)));
}

void MultiTouchTest::restartCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5, MultiTouchTest::createScene()));
}

Scene* MultiTouchTest::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));
	auto layer = MultiTouchTest::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}
bool MultiTouchTest::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}
	unit = FlowerMouse::create(Size(1, 1), "Flower");
	unit->setPhysicsBody(PhysicsBody::createCircle(10, PhysicsMaterial(1, 0, 1)));
	unit->getPhysicsBody()->setContactTestBitmask(0x10);
	unit->getPhysicsBody()->setRotationEnable(false);
	//unit->getPhysicsBody()->setDynamic(false);
	unit->setTag(1);
	//unit->setVisible(false);
	attackUnit = Node::create();
	auto sun = ParticleSun::create();
	sun->retain();
	sun->setPosition(Vec2::ZERO);
	sun->setTexture(Director::getInstance()->getTextureCache()->addImage("particle/fire.png"));
	attackUnit->addChild(sun);

	attackUnit->setPhysicsBody(PhysicsBody::createCircle(10, PhysicsMaterial(1, 0, 1)));
	attackUnit->getPhysicsBody()->setContactTestBitmask(0x01);
	attackUnit->getPhysicsBody()->setRotationEnable(false);
	//attackUnit->getPhysicsBody()->setDynamic(false);
	attackUnit->setTag(2);
	addChild(attackUnit, 99);
	//attackUnit->setVisible(false);
	addChild(unit, 100);
	
	unit->setPosition(_text1->getPosition());
	attackUnit->setPosition(_text2->getPosition());

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = CC_CALLBACK_2(MultiTouchTest::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(MultiTouchTest::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(MultiTouchTest::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_text2->setRotation(90);
	_text1->setRotation(90);

	auto node = Node::create();
	node->setPhysicsBody(PhysicsBody::createEdgeBox(_visibleSize, PhysicsMaterial(1, 0, 1)));
	node->setPosition(Vec2(_visibleSize.width/2,_visibleSize.height/2));
	addChild(node);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MultiTouchTest::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);


	_client = SocketIO::connect("ws://192.168.0.126:8080/", *this);
	CCASSERT(_client, "CAN NOT CREATE SOCKETIO");
	_client->on("hello", CC_CALLBACK_2(MultiTouchTest::checkEnemy, this));
	return true;
}

void MultiTouchTest::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	for (auto &item : touches)
	{
		auto touch = item;
		auto location = touch->getLocation();
		if (location.y < _visibleSize.height / 2) {
			//unit->setPosition(location);
			//unit->setVisible(true);
			beginTouchRight = location;
		}
		else {
			//attackUnit->setPosition(location);
			//attackUnit->setVisible(true);
			beginTouchLeft = location;
		}
	}
}

void MultiTouchTest::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
	for (auto &item : touches)
	{
		auto touch = item;
		auto location = touch->getLocation();
		//if (location.y < _visibleSize.height / 2) {
			//unit->setPosition(location);
			//unit->setVisible(true);
			auto reg = location - beginTouchRight;
			if (reg.length() < minLength) return;
			_text1->setString(DataUtils::numberToString(DataUtils::radianToDegree(reg.getAngle())));
			unit->getPhysicsBody()->setVelocity(Vect(limitSpeed*cos(reg.getAngle()),limitSpeed*sin(reg.getAngle())));
			beginTouchRight = location;
		/*}
		else {
			//attackUnit->setPosition(location);
			//attackUnit->setVisible(true);
			auto regL = location - beginTouchLeft;
			if (regL.length() < minLength) return;
			_text2->setString(DataUtils::numberToString(DataUtils::radianToDegree(regL.getAngle())));
			attackUnit->getPhysicsBody()->setVelocity(Vect(limitSpeed*cos(regL.getAngle()), limitSpeed*sin(regL.getAngle())));
			beginTouchLeft = location;
		}*/
	}
}

void MultiTouchTest::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	for (auto &item :touches)
	{
		for (auto &item : touches)
		{
			auto touch = item;
			auto location = touch->getLocation();
			//if (location.y < _visibleSize.height / 2) {
				//unit->setPosition(location);
				//unit->setVisible(true);
				auto reg = location - beginTouchRight;
				_text1->setString("");
				unit->getPhysicsBody()->setVelocity(Vect(0, 0));
		/*	}
			else {
				//attackUnit->setPosition(location);
				//attackUnit->setVisible(true);
				auto regL = location - beginTouchLeft;
				_text2->setString("");
				attackUnit->getPhysicsBody()->setVelocity(Vect(0, 0));
			}*/
		}
	}
}

void MultiTouchTest::moveUnit()
{

}

void MultiTouchTest::actionUnit()
{

}

void MultiTouchTest::debugCallback(Ref *pSender)
{
	if (myWorld->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE) {
		myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	}
	else {
		myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}

void MultiTouchTest::createMoveData()
{
	auto pos = unit->getPosition();
	if (pos != _savePos)
	{
		_savePos = pos;
		string data;
		data.append("[{\"value\":{\"pos\":{\"x\": \"").append(DataUtils::numberToString(pos.x)).append("\",\"y\":\"").append(DataUtils::numberToString(pos.y)).append("\"}}}]");
		_client->emit("hello", data.c_str());
	}
}
void MultiTouchTest::checkEnemy(SIOClient* client, const std::string& data)
{
	log("event");
	if (attackUnit) {
		rapidjson::Document doc;
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("Error JSON: %s", doc.GetParseError());
			return;
		}
		if (doc.HasMember("args")) {
			rapidjson::Value &val = doc["args"];
			attackUnit->setPosition(DataUtils::stringToFloat(val[rapidjson::SizeType(0)]["value"]["pos"]["x"].GetString()), DataUtils::stringToFloat(val[rapidjson::SizeType(0)]["value"]["pos"]["y"].GetString()));
		}
	}
}
bool MultiTouchTest::onContactBegin(const PhysicsContact &contact)
{ 
	cocos2d::log("contact");
	//auto explo = FlowerMouse::create(Size(1, 1), "bom");
	//explo->setPosition(unit->getPosition());
	//addChild(explo, 900);
	auto p = contact.getContactData()->points;
	createParticleEffect(p[0]);
	return true;
}

void MultiTouchTest::update(float delta)
{
	createMoveData();
}

void MultiTouchTest::createParticleEffect(Vec2 pos)
{
	string _filename = "explo";
	string filename = "Particles/" + _filename + ".plist";
	auto _emitter = ParticleSystemQuad::create(filename);
	/*_emitter->setDuration(0.5);
	_emitter->setLife(0.2f);
	_emitter->setLifeVar(5.3);
	_emitter->setEmissionRate(528);
	_emitter->setAngle(135);
	_emitter->setAngleVar(180);
	_emitter->setSpeed(732);*/
	addChild(_emitter, 10);
	_emitter->setPosition(pos);
}

void MultiTouchTest::onConnect(SIOClient* client)
{

}

void MultiTouchTest::onMessage(SIOClient* client, const std::string& data)
{

}

void MultiTouchTest::onClose(SIOClient* client)
{

}

void MultiTouchTest::onError(SIOClient* client, const std::string& data)
{

}



