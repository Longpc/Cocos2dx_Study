#include "ThumbLayer.h"
ThumbLayer * ThumbLayer::create(const Color4B& color) {
	ThumbLayer *layer = new ThumbLayer();
	if (layer && layer->initWithColor(color)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
bool ThumbLayer::initWithColor(const Color4B& color) {
	if (!LayerColor::initWithColor(color)) {
		return false;
	}
	this->setContentSize(Size(200, 200));
	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	text = Text::create("Name", "", 25);
	text->setPosition(Vec2(150, 150));
	addChild(text);

	/*auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PopLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(PopLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(PopLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	touchListener->setSwallowTouches(true); */

	return true;
}

bool ThumbLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

void ThumbLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void ThumbLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void ThumbLayer::setThumb(string filepath)
{
	if (getChildByTag(1)!=nullptr) { removeChildByTag(1); }
	auto sprite = Sprite::create(filepath);
	sprite->setPosition(Vec2(150, 150));
	sprite->setTag(1);
	addChild(sprite);
}

void ThumbLayer::setText(string name)
{
	text->setString(name);
}

void ThumbLayer::setTextSize(int size)
{
	text->setFontSize(size);
}

void ThumbLayer::setTColor(Color4B color)
{
	text->setTextColor(color);
}
