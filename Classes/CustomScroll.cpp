#include "CustomScroll.h"


Scene* CustomScroll::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
	auto layer = CustomScroll::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	auto infoLayer = InforLayer::create();
	scene->addChild(infoLayer);
	return scene;
}

bool CustomScroll::init()
{
	if (!Layer::init())
	{
		return false;
	}
	int off = 100;
	visibleSize = Director::getInstance()->getVisibleSize();
	pos1 = Vec2(visibleSize.width / 6 - off, visibleSize.height / 2+100);
	pos2 = Vec2(visibleSize.width / 3 - off, visibleSize.height / 2+50);
	pos3 = Vec2(visibleSize.width / 2 - off, visibleSize.height / 2);
	pos4 = Vec2(visibleSize.width * 2 / 3 - off, visibleSize.height / 2+50);
	pos5 = Vec2(visibleSize.width * 5 / 6 - off, visibleSize.height / 2+100);
	this->setAccelerometerEnabled(true);
	auto aListener = EventListenerAcceleration::create(CC_CALLBACK_2(CustomScroll::onAccleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(aListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(CustomScroll::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(CustomScroll::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(CustomScroll::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CustomScroll::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto back = Button::create("close.png", "close.png");
	back->setTouchEnabled(true);
	back->addTouchEventListener(CC_CALLBACK_2(CustomScroll::backToGameOverScreen, this));
	back->setPosition(Vec2(visibleSize.width - 50, visibleSize.height-50));
	addChild(back);

	auto button2 = Button::create("Button/redButton111x71.png", "Button/redBrightButton111x71.png");
	button2->setTouchEnabled(true);
	button2->setTitleText("Reset");
	button2->setTitleFontSize(20);
	button2->setPosition(Vec2(button2->getContentSize().width / 2, 100));
	button2->addTouchEventListener(CC_CALLBACK_2(CustomScroll::clickToReset,this));
	addChild(button2);

	auto button3 = Button::create("Button/redButton111x71.png", "Button/redBrightButton111x71.png");
	button3->setTouchEnabled(true);
	button3->setTitleText("Move");
	button3->setTitleFontSize(20);
	button3->setPosition(Vec2(button3->getContentSize().width / 2, 200));
	button3->addTouchEventListener(CC_CALLBACK_2(CustomScroll::clickMove1, this));
	addChild(button3);

	auto button4 = Button::create("Button/redButton111x71.png", "Button/redBrightButton111x71.png");
	button4->setTouchEnabled(true);
	button4->setTitleText("Scale");
	button4->setTitleFontSize(20);
	button4->setPosition(Vec2(button4->getContentSize().width / 2, 300));
	button4->addTouchEventListener(CC_CALLBACK_2(CustomScroll::clickScale1, this));
	addChild(button4);

	this->scheduleUpdate();

	return true;
}
void CustomScroll::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	LayerGradient *layer = LayerGradient::create(Color4B(210, 121, 255, 121), Color4B(255, 255, 255, 200));
	//layer->setAnchorPoint()
	//layer->setPosition()
	layer->setContentSize(Size(visibleSize.width * 2, 300));

	myScrollView = extension::ScrollView::create();
	myScrollView->setViewSize(Size(visibleSize.width * 2, 300));
	myScrollView->setContentOffset(myScrollView->maxContainerOffset());
	myScrollView->setContainer(layer);
	myScrollView->setDirection(extension::ScrollView::Direction::HORIZONTAL);
	myScrollView->updateInset();
	myScrollView->setPosition(Vec2(0,visibleSize.height-200));

	//addChild(myScrollView);

	baseSprite = Sprite::create("thumb.png");
	baseSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(baseSprite); 
	layer1 = ThumbLayer::create(Color4B::BLUE);
	layer2 = ThumbLayer::create(Color4B::RED);
	layer3 = ThumbLayer::create(Color4B::GREEN);
	layer4 = ThumbLayer::create(Color4B::GRAY);
	layer5 = ThumbLayer::create(Color4B::YELLOW);
	layer1->setPosition(pos1);
	layer2->setPosition(pos2);
	layer3->setPosition(pos3);
	layer4->setPosition(pos4);
	layer5->setPosition(pos5);
	addChild(layer1,1);
	addChild(layer2,2);
	addChild(layer3,3);
	addChild(layer4,2);
	addChild(layer5,1);
	
}
void CustomScroll::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();

}

bool CustomScroll::onTouchBegan(Touch* touch, Event* evnet) {
	auto location = touch->getLocation();
	beginPoint = location;
	return true;
}
void CustomScroll::onTouchEnded(Touch* touch, Event* event) {
	call1 = false;
	call2 = false;
}
void CustomScroll::onTouchMoved(Touch* touch, Event* event){
	Vec2 touchLocation = touch->getLocation();
	currentPoint = touchLocation;

	Vec2 direc = currentPoint - beginPoint;
	if (direc.length() > visibleSize.width / 3) {
		if (direc.x > 0 ) {
			//cocos2d::log("left to right");
			if (call1 == false) {
				toRightAnimation(baseSprite);
				call1 = true;
			}
		}
		else {
			//cocos2d::log("right to left");
			if (call2 == false) {
				rightToMid(baseSprite);
				call2 = true;
			}
		}
	}
}
void CustomScroll::update(float dt) {

}
void CustomScroll::onAccleration(Acceleration *pAccelerationValue, Event *event) {
	cocos2d::log("accs");

}
bool CustomScroll::onContactBegin(const PhysicsContact &contact) {
	cocos2d::log("contact");

	return true;
}


CustomScroll::CustomScroll() {
	cocos2d::log("Custom Scroll");

}
CustomScroll::~CustomScroll() {
	cocos2d::log("On CustomScroll Destruct");

}

void CustomScroll::backToGameOverScreen(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameOverScene::createScene(-1)));
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}

void CustomScroll::toRightAnimation(Sprite *sprite)
{
	CCLOG("Mid to right");
	float duration = 0.2f;
	float moveRation = 100;
	float scaleRadio = 2 / 3;
	Vec2 newPos = Vec2(/*sprite->getPositionX() + moveRation, sprite->getPositionY()*/100,0);
	auto move = MoveBy::create(duration,newPos);
	auto scaleAction = ScaleBy::create(duration,0.75 );
	auto rotate = RotateBy::create(duration, Vec3(0, 0, 50));

	sprite->runAction(Spawn::create(move, scaleAction,/*rotate,*/ nullptr));
}

void CustomScroll::toLeftAnimation(Sprite *sprite)
{

}

void CustomScroll::rightToMid(Sprite *sprite)
{
	CCLOG("right to mid");
	float duration = 0.2f;
	float moveRation = 100;
	float scaleRadio = 2 / 3;
	Vec2 newPos = Vec2(-100,0);
	auto move = MoveBy::create(duration, newPos);
	auto scale = ScaleBy::create(duration, 1/0.75);

	sprite->runAction(Spawn::create(move, scale, nullptr));
}

void CustomScroll::leftToMid(Sprite *sprite)
{

}

void CustomScroll::resetAll(Sprite *sprite)
{
	baseSprite->stopAllActions();
	sprite->setScale(1);
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	call1 = false;
	call2 = false;
}

void CustomScroll::clickToReset(Ref *pSEnder, Widget::TouchEventType type)
{
	
	resetAll(baseSprite);
}

void CustomScroll::move1(Sprite *sprite)
{
	sprite->runAction(MoveBy::create(1, Vec2(100,0)));
}

void CustomScroll::scale1(Sprite *sprite)
{
	sprite->runAction(ScaleBy::create(1, 0.5));
}

void CustomScroll::clickMove1(Ref *pSender, Widget::TouchEventType type)
{
	move1(baseSprite);
}

void CustomScroll::clickScale1(Ref *pSender, Widget::TouchEventType type)
{
	scale1(baseSprite);
}

