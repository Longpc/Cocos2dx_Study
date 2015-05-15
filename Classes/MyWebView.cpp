#include "MyWebView.h"



Scene* MyWeb::createScene()
{
	auto scene = Scene::create();
	auto layer = MyWeb::create();
	scene->addChild(layer);
	return scene;
}

bool MyWeb::init()
{
	if (!Layer::init()) {
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	auto back = Button::create("close.png", "close.png");
	back->setTouchEnabled(true);
	back->setPosition(Vec2(visibleSize.width - 100, visibleSize.height - 100));
	back->addTouchEventListener(CC_CALLBACK_2(MyWeb::clickBack, this));
	addChild(back,100);
	auto sp = Sprite::create("test.png");
	sp->setPosition(visibleSize / 2);
	addChild(sp);

	test = ParticleSystemQuad::create("shape.plist");
	test->setPosition(visibleSize / 2);
	addChild(test, 1000);


	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MyWeb::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	
	return true;
}

void MyWeb::clickBack(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionFadeDown::create(1, GameOverScene::createScene(-1)));
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void MyWeb::testTouchEvent(Touch *touch, Event* event)
{
	
}

void MyWeb::onEnter()
{
	Layer::onEnter();
}

bool MyWeb::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto pos = convertToWorldSpace(touch->getLocation());
	auto *buff = malloc(sizeof(Color4B));
	
	glReadPixels(pos.x, pos.y,1,1, GL_RGBA, GL_UNSIGNED_BYTE, buff);
	auto a = (int)buff;
	log("%d,buff: ", buff);
	test->setPosition(pos);

	Color4F co = Color4F::BLACK;
	unsigned int b = (unsigned int)buff;
	co.r = ((b & 0xFF0000) >>16)/255;
	co.g = ((b & 0x00FF00) >> 8) / 255;
	co.b = ((b & 0x0000FF) >> 0) / 255;

	test->setStartColor(Color4F::RED);
	return true;
}
