#include "TestFollow.h"

Scene* TestFollow::createScene()
{
	auto scene = Scene::create();
	auto layer = TestFollow::create();
	scene->addChild(layer);
	return scene;
}

void TestFollow::exitCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, GameOverScene::createScene(-1)));
}

void TestFollow::restartCallback(Ref *pSender)
{
	/*sprite->stopAllActions();
	sprite->removeAllChildrenWithCleanup(true);
	this->removeAllChildrenWithCleanup(true*/
	Director::getInstance()->replaceScene(/*TransitionShrinkGrow::create(0.5, */TestFollow::createScene()/*)*/);
}

void TestFollow::debugCallback(Ref *pSender)
{

}

void TestFollow::onEnter()
{
	BaseLayer::onEnter();

}

void TestFollow::onExit()
{
	BaseLayer::onExit();
	sprite->removeAllChildrenWithCleanup(true);
	this->removeAllChildrenWithCleanup(true);
}

bool TestFollow::init()
{
	if (!BaseLayer::init())
	{
		return false;
	}
	sprite = Sprite::create("follow.png");
	sprite->setPosition(Vec2(_visibleSize.width/2,_visibleSize.height/2));
	sprite->setAnchorPoint(Vec2::ZERO);
	addChild(sprite);
	ball = Sprite::create("ball.png");
	ball->setPosition(Vec2(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2));
	sprite->addChild(ball, 100);
	sprite->runAction(Follow::create(ball));

	auto touchListenner = EventListenerTouchOneByOne::create();
	touchListenner->onTouchBegan = CC_CALLBACK_2(TestFollow::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListenner, this);
	touchListenner->setEnabled(true);
	touchListenner->setSwallowTouches(true);

	captureScreen = Button::create();
	captureScreen->loadTextureNormal("Button/blueBrightButton111x71.png");
	captureScreen->setTouchEnabled(true);
	captureScreen->setTitleText("Capture");
	captureScreen->setTitleFontSize(25);
	captureScreen->addTouchEventListener(CC_CALLBACK_2(TestFollow::touchCapture, this));
	captureScreen->setPosition(Vec2(captureScreen->getContentSize().width / 2, 100));
	addChild(captureScreen, 101);
	
	return true;

}

bool TestFollow::onTouchBegan(Touch *touch, Event *unused_event)
{
	ball->runAction(MoveTo::create(0.5, touch->getLocation()));
	return true;
}

void TestFollow::touchCapture(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED: {

		utils::captureScreen(CC_CALLBACK_2(TestFollow::afterCaptured, this), "long.png");
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void TestFollow::afterCaptured(bool succeed, const string& outputFile)
{
	log(" capture file: %s", outputFile.c_str());
	if (succeed) {
		auto sp = Sprite::create(outputFile);
		addChild(sp, 199);
		sp->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
		sp->setScale(0.5);
	}
	else {
		log("Capture screen failed");
	}
}
