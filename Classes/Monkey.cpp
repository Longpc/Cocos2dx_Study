#include "Monkey.h"
Monkey* Monkey::create()
{
	Monkey *monkey = new Monkey();
	monkey->initWithFile("node.png");
	monkey->autorelease();
	return monkey;
}

void Monkey::onEnter()
{
	Sprite::onEnter();
	this->setContentSize(Size(80, 80));
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jump/monkey/monkey.plist");
	auto ss = SpriteBatchNode::create("Jump/monkey/monkey.png");
	this->addChild(ss);
	Vector<SpriteFrame*> af(7);
	char name[30] = { 0 };
	for (int i = 0; i < 7; i++)
	{
		sprintf(name, "%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		af.pushBack(frame);
	}
	auto a = Sprite::createWithSpriteFrameName("0.png");
	a->setPosition(Vec2(40, 40));
	ss->addChild(a);
	Animation *animation = Animation::createWithSpriteFrames(af, 0.3f);
	auto walkAction = Repeat::create(Animate::create(animation),1);
	walkAction->retain();
	a->runAction(walkAction);
	
}

Monkey::Monkey(void)
{

}

Monkey::~Monkey(void)
{

}



