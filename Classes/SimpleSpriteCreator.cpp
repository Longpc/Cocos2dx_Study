#include "SimpleSpriteCreator.h"

SimpleSpriteCreator::SimpleSpriteCreator() {

}
SimpleSpriteCreator::~SimpleSpriteCreator() {

}
Rect SimpleSpriteCreator::getRect() {
	auto s = getTexture()->getContentSize();
	return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}
SimpleSpriteCreator* SimpleSpriteCreator::createWithTexture(Texture2D* aText) {
	SimpleSpriteCreator* simpleSprite = new SimpleSpriteCreator();
	simpleSprite->initWithTexture(aText);
	simpleSprite->autorelease();

	return simpleSprite;
}
bool SimpleSpriteCreator::initWithTexture(Texture2D* aTex) {
	return Sprite::initWithTexture(aTex);
}
SimpleSpriteCreator* SimpleSpriteCreator::createWithImage(std::string filepath) {
	SimpleSpriteCreator* simpleSprite = new SimpleSpriteCreator();
	if (simpleSprite->initWithFile(filepath)) {
		simpleSprite->autorelease();
		return simpleSprite;
	}
	CC_SAFE_DELETE(simpleSprite);
	return NULL;
}
void SimpleSpriteCreator::onEnter() {
	Sprite::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(SimpleSpriteCreator::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SimpleSpriteCreator::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SimpleSpriteCreator::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void SimpleSpriteCreator::onExit() {
	Sprite::onExit();
}
bool SimpleSpriteCreator::containsTouchLocation(Touch* touch) {
	return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}
bool SimpleSpriteCreator::onTouchBegan(Touch* touch, Event* event) {
	if (!containsTouchLocation(touch)) return false;
	//this->runAction(FlipX::create(true));
	return true;
}
void SimpleSpriteCreator::onTouchMoved(Touch* touch, Event* event) {
	auto point = touch->getLocation();
	//this->setPosition(point);
	//if (this->getPhysicsBody() != nullptr) {
	//	this->getPhysicsBody()->setVelocity(Vect(0, 0)); //OK
	//}
}
void SimpleSpriteCreator::onTouchEnded(Touch* touch, Event* event){
	if (_touchEvent) {
		_touchEvent(touch,event);
	}
}

void SimpleSpriteCreator::addTouchEvent(MyTouchEvent touch)
{
	_touchEvent = touch;
}
