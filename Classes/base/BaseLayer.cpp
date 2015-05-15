#include "BaseLayer.h"

void BaseLayer::onEnter()
{
	Layer::onEnter();
	cocos2d::log("base Layer onEnter");
}

void BaseLayer::onExit()
{
	Layer::onExit();
	cocos2d::log("base layer onExit");
}

void BaseLayer::exitCallback(Ref *pSender)
{
	log("on click exit");
}

void BaseLayer::restartCallback(Ref *pSender)
{
	log("restart");
}

bool BaseLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	_visibleSize = Director::getInstance()->getVisibleSize();
	_winSize = Director::getInstance()->getWinSize();
	_orginSize = Director::getInstance()->getVisibleOrigin();

	_item1 = MenuItemImage::create("close.png", "close1.png", CC_CALLBACK_1(BaseLayer::exitCallback, this));
	_item2 = MenuItemImage::create("restart.png", "restart1.png", CC_CALLBACK_1(BaseLayer::restartCallback, this));
	_item3 = MenuItemImage::create("debug.png", "debug1.png", CC_CALLBACK_1(BaseLayer::debugCallback, this));
	_item4 = MenuItemImage::create("hide.png", "hide.png", CC_CALLBACK_1(BaseLayer::nextCallback, this));

	_menu = Menu::create(_item1, _item2,_item3,_item4, nullptr);
	_item1->setPosition(Vec2(_visibleSize.width - 50, _visibleSize.height - 50));
	_item2->setPosition(Vec2(_visibleSize.width - 120, _visibleSize.height - 50));
	_item3->setPosition(Vec2(_visibleSize.width - 190, _visibleSize.height - 50));
	_item4->setPosition(Vec2(_visibleSize.width - 260, _visibleSize.height - 50));
	addChild(_menu, 9999);
	_menu->setPosition(Vec2::ZERO);

	_text1 = TextField::create("", "", 30);
	_text1->setTextColor(Color4B::RED);
	_text1->setPosition(Vec2(_visibleSize.width * 2 / 3, _visibleSize.height * 1 / 3));
	addChild(_text1, 1000);
	_text2 = TextField::create("", "", 30);
	_text2->setTextColor(Color4B::YELLOW);
	_text2->setPosition(Vec2(_visibleSize.width * 2 / 3, _visibleSize.height * 2 / 3));
	addChild(_text2, 1000);

	return true;
}

void BaseLayer::debugCallback(Ref *pSender)
{
}

void BaseLayer::closeCaptureCallback(Ref *pSender, Widget::TouchEventType type)
{

}

void BaseLayer::nextCallback(Ref *pSender)
{

}
