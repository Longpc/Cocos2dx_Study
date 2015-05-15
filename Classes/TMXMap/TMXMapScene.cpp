#include "TmxMapScene.h"

Scene* TMXMapScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, -1000));
	auto layer = TMXMapScene::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());

	auto mLayer = MenuLayer::create();
	mLayer->addPhysicWorld(scene->getPhysicsWorld());

	scene->addChild(layer,0);
	scene->addChild(mLayer, 1);

	return scene;
}

bool TMXMapScene::init()
{
	if (!BaseLayer::init()) {
		return false;
	}
	_menu->setVisible(false);
	return true;
}

void TMXMapScene::setPhysicWorld(PhysicsWorld* world)
{
	_myWorld = world;
}

void TMXMapScene::restartCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,TMXMapScene::createScene(),true));
}

void TMXMapScene::exitCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(GameOverScene::createScene(-1));
}

void TMXMapScene::debugCallback(Ref *pSender)
{
	if (_myWorld->getDebugDrawMask() == PhysicsWorld::DEBUGDRAW_ALL) {
		_myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	}
	else {
		_myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}

void TMXMapScene::nextCallback(Ref *pSender)
{
	
}

void TMXMapScene::onEnter()
{
	BaseLayer::onEnter();

	string file = "Test.tmx";
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());

	_myMap = TMXTiledMap::createWithXML(str->getCString(), "");
	


	//_myMap = TMXTiledMap::create("Test.tmx");
	if (_myMap == nullptr) return;

	_myLayer = _myMap->getLayer("Background");
	_blockLayer = _myMap->getLayer("block");
	_collectLayer = _myMap->getLayer("collectable");
	_blockLayer->setVisible(false);

	addChild(_myMap);
	scheduleUpdate();
	TMXObjectGroup *objGroup = _myMap->getObjectGroup("Object");
	if (objGroup == nullptr) {
		log("Object null");
		return;
	}
	
	ValueMap spawnPoint = objGroup->getObject("StartPoint");
	CCASSERT(!spawnPoint.empty(), "Start point not found");
	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	_myPlayer = Sprite::create("player.png");
	_myPlayer->setPosition(Vec2(x + _myMap->getTileSize().width / 2, y + _myMap->getTileSize().height / 2));
	
	addChild(_myPlayer);

	for (auto& ePoint : objGroup->getObjects())
	{
		log("%d",ePoint.getDescription().c_str());
		ValueMap& dict = ePoint.asValueMap();
		if (dict["enemy"].asInt() == 1) {
			x = dict["x"].asInt();
			y = dict["y"].asInt();
			addEnemyWithPos(Vec2(x, y));
		}
	}

	setViewPointCenter(_myPlayer->getPosition());
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TMXMapScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TMXMapScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TMXMapScene::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


}
void TMXMapScene::update(float dt)
{

}
bool TMXMapScene::onTouchBegan(Touch *touch, Event *unused_event)
{

	return true;
}

void TMXMapScene::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void TMXMapScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto actionTo1 = RotateTo::create(0, 0, 180);
	auto actionTo2 = RotateTo::create(0, 0, 0);
	auto touchLocation = touch->getLocation();

	touchLocation = this->convertToNodeSpace(touchLocation);

	auto playerPos = _myPlayer->getPosition();
	auto diff = touchLocation - playerPos;
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += _myMap->getTileSize().width / 2;
			_myPlayer->runAction(actionTo2);
		}
		else {
			playerPos.x -= _myMap->getTileSize().width / 2;
			_myPlayer->runAction(actionTo1);
		}
	}
	else {
		if (diff.y > 0) {
			playerPos.y += _myMap->getTileSize().height / 2;
		}
		else {
			playerPos.y -= _myMap->getTileSize().height / 2;
		}
	}

	if (playerPos.x <= (_myMap->getMapSize().width * _myMap->getMapSize().width) &&
		playerPos.y <= (_myMap->getMapSize().height * _myMap->getMapSize().height) &&
		playerPos.y >= 0 &&
		playerPos.x >= 0)
	{
		this->setPlayerPosition(playerPos);

	}

	this->setViewPointCenter(_myPlayer->getPosition());
}

void TMXMapScene::onNativeCallback(int tag, NativeAlert::ButtonType type)
{
	log("Alert callback");
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

void TMXMapScene::setViewPointCenter(Vec2 centerPos)
{
		int x = MAX(centerPos.x, _visibleSize.width / 2);
		int y = MAX(centerPos.y, _visibleSize.height / 2);

		x = MIN(x, (_myMap->getMapSize().width*this->_myMap->getTileSize().width) - _visibleSize.width / 2);
		y = MIN(y, (_myMap->getMapSize().height*_myMap->getTileSize().height) - _visibleSize.height / 2);

		Vec2 actualPos = Vec2(x, y);

		Vec2 centerOfView = _visibleSize / 2;
		auto viewPoint = centerOfView - actualPos;

		this->setPosition(viewPoint);


	
}

void TMXMapScene::setPlayerPosition(Vec2 pos)
{
	Vec2 title = titleCoordForPosition(pos);
	int tileGid = _blockLayer->getTileGIDAt(title);
	log("%d", tileGid);
	if (tileGid) {
		return;
		
	}
	tileGid = _collectLayer->getTileGIDAt(title);
	log("%d", tileGid);
	if (tileGid) {
		_collectLayer->removeTileAt(title);
		_itemNum++;
		//mLayer->numCollectedChanged(_itemNum);
		log("item num: %d", _itemNum);
	}
	_myPlayer->setPosition(pos);
}

void TMXMapScene::doSomethingHere()
{
	log("do something here");
}

cocos2d::Vec2 TMXMapScene::titleCoordForPosition(Vec2 location)
{
	int x = location.x / _myMap->getTileSize().width;
	int y = ((_myMap->getMapSize().height*_myMap->getTileSize().height - location.y) / _myMap->getTileSize().height);
	return Vec2(x, y);
}

void TMXMapScene::addEnemyWithPos(Vec2 pos)
{
	auto enemy = Sprite::create("fire2.png");
	enemy->setPosition(pos);
	enemy->setScale(1.5f);
	addChild(enemy);
	_allEnemies.push_back(enemy);
}

bool MenuLayer::init()
{
	if (!BaseLayer::init()) {
		return false;
	}
	label = Label::create("0", "fonts/2.ttf", 30);
	label->setTextColor(Color4B::BLACK);
	label->setPosition(Vec2(_visibleSize.width - 100, 100));
	addChild(label);

	return true;
}

void MenuLayer::restartCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, TMXMapScene::createScene(), true));
}

void MenuLayer::exitCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(GameOverScene::createScene(-1));
}

void MenuLayer::debugCallback(Ref *pSender)
{
	if (pWorld->getDebugDrawMask() == PhysicsWorld::DEBUGDRAW_ALL) {
		pWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	}
	else {
		pWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}

void MenuLayer::nextCallback(Ref *pSender)
{
	TMXMapScene::doSomethingHere();
}


void MenuLayer::addPhysicWorld(PhysicsWorld *world)
{
	pWorld = world;
}

void MenuLayer::numCollectedChanged(int num)
{

}
