
#include "PopLayer1.h"



PopLayer1* PopLayer1::create(const Color4B& color,int score)
{
    PopLayer1 *pRet = new PopLayer1();
    if(pRet && pRet->initWithColor(color,score))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool PopLayer1::initWithColor(const Color4B& color,int score)
{
    if (!LayerColor::initWithColor(color)) {
        return false;
    }
	userScore = score;
	topScore = UserDefault::getInstance()->getIntegerForKey("TOPSCORE");
	cocos2d::log("TOP SCORE: %d", topScore);
    Size winSize = Director::getInstance()->getWinSize();
    Point menuPos = Point(winSize.width / 2, winSize.height / 2 - 200);
	Point scorePos = Point(winSize.width / 2, winSize.height / 2 + 200);
	Point nameIputPos = Point(winSize.width / 2, winSize.height / 2);

	std::stringstream scoreText;
	scoreText << "SCORE: " << userScore;

	auto scoreView = Label::create(scoreText.str().c_str(), "fonts/2.ttf", 80);
	addChild(scoreView,1);
	scoreView->setTextColor(Color4B(255, 45, 87, 180));
	scoreView->setPosition(scorePos);
	
	auto top = Sprite::create("top2.png");
	top->setPosition(Vec2(winSize.width / 2 + scoreView->getContentSize().width *3/ 4, scorePos.y + top->getContentSize().height));
	if (userScore > topScore) {
		addChild(top, 2);
	}

	nameInput = TextField::create("Input your name here!", "fonts/2.ttf", 50);
	nameInput->ignoreContentAdaptWithSize(false);
	nameInput->setContentSize(Size(240, 160));
	nameInput->setMaxLengthEnabled(true);
	nameInput->setMaxLength(20);
	nameInput->setDeleteBackward(true);
	nameInput->setAttachWithIME(true);
	nameInput->setTextHorizontalAlignment(TextHAlignment::CENTER);
	nameInput->setTextVerticalAlignment(TextVAlignment::CENTER);
	nameInput->setPosition(nameIputPos);
	nameInput->addEventListener(CC_CALLBACK_2(PopLayer1::textFieldEvent, this));
	addChild(nameInput);

	/*saveButton = Button::create("Button/blueButton181x71.png", "Button/blueBrightButton181x71.png");
	saveButton->setTouchEnabled(true);
	//saveButton->loadTextureNormal("Button/blueButton181x71.png");
	//saveButton->loadTexturePressed("Button/blueBrightButton181x71");
	saveButton->setTitleText("SAVE");
	saveButton->setTitleFontSize(30);
	saveButton->setTitleColor(Color3B(241, 214, 231));
	saveButton->setPosition(Vec2(nameIputPos.x + nameInput->getContentSize().width + 50,nameIputPos.y));
	saveButton->addTouchEventListener(CC_CALLBACK_2(PopLayer1::savename, this));

	addChild(saveButton); */


    MenuItemFont::setFontName("fonts/2.ttf");
    MenuItemFont::setFontSize(70);

	auto hightScore = MenuItemFont::create("HIGH SCORE", CC_CALLBACK_1(PopLayer1::onHighScore, this));
    auto menuItemRestart = MenuItemFont::create("TRY AGAIN", CC_CALLBACK_1(PopLayer1::onRestart, this));
    auto menuItemExit = MenuItemFont::create("EXIT", CC_CALLBACK_1(PopLayer1::onExit, this));
    
    
    auto menu = Menu::create(hightScore, menuItemRestart, menuItemExit, NULL);
    menu->alignItemsVertically();
    addChild(menu);
    menu->setPosition(menuPos);
    
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PopLayer1::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PopLayer1::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PopLayer1::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    touchListener->setSwallowTouches(true);
    
	//this->scheduleUpdate();
    return true;
}
void PopLayer1::update(float dt) {
	cocos2d::log("%d", nameInput->getStringLength());
}
void PopLayer1::savename(Ref *pSender, Widget::TouchEventType type) {
	cocos2d::log("SAVE");
	UserDefault::getInstance()->setStringForKey("NAME", nameInput->getString());
	UserDefault::getInstance()->setIntegerForKey("SCORE", userScore);
	if (userScore > topScore) {
		UserDefault::getInstance()->setIntegerForKey("TOP", 1);
		UserDefault::getInstance()->setStringForKey("TOPNAME", nameInput->getString());
		UserDefault::getInstance()->setIntegerForKey("TOPSCORE", userScore);
	}

}
void PopLayer1::onExitTransitionDidStart() {
	cocos2d::log("EXIT");
	UserDefault::getInstance()->setStringForKey("NAME", nameInput->getString());
	UserDefault::getInstance()->setIntegerForKey("SCORE", userScore);
	if (userScore > topScore) {
		UserDefault::getInstance()->setIntegerForKey("TOP", 1);
		UserDefault::getInstance()->setStringForKey("TOPNAME", nameInput->getString());
		UserDefault::getInstance()->setIntegerForKey("TOPSCORE", userScore);
	}
}
void PopLayer1::textFieldEvent(Ref *pSender, TextField::EventType type) {
	switch (type)
	{
	case TextField::EventType::ATTACH_WITH_IME:
	{
		cocos2d::log("attack with IME");
	}
	break;

	case TextField::EventType::DETACH_WITH_IME:
	{
		cocos2d::log("detack with IME");
	}
	break;

	case TextField::EventType::INSERT_TEXT:
		if (nameInput->getStringLength() > MAX_TEXT_LENGTH) {
			return;
		}
		cocos2d::log("input");
		break;

	case TextField::EventType::DELETE_BACKWARD:
		cocos2d::log("DElete");
		break;

	default:
		break;
	}
}
void PopLayer1::onHighScore(Ref* pSender) {
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, HighScore::createScene()));
	Director::getInstance()->resume();
}
void PopLayer1::onRestart(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFlipX::create(1, ModeSelect::createScene()));
    Director::getInstance()->resume();
}

void PopLayer1::onExit(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


bool PopLayer1::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void PopLayer1::onTouchMoved(Touch* touch, Event* event)
{
}

void PopLayer1::onTouchEnded(Touch* touch, Event* event)
{
}
