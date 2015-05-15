
#include "PopLayer.h"



PopLayer* PopLayer::create(const Color4B& color,int offset)
{
    PopLayer *pRet = new PopLayer();
    if(pRet && pRet->initWithColor(color,offset))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool PopLayer::initWithColor(const Color4B& color,int offset)
{
    if (!LayerColor::initWithColor(color)) {
        return false;
    }
	_offset = offset;
    Size winSize = Director::getInstance()->getWinSize();
    Point centerPos = Point(winSize.width / 2, winSize.height / 2);
    
    MenuItemFont::setFontName("fonts/DroidSans.ttf");
    MenuItemFont::setFontSize(80);
    
    auto menuItemContinue = MenuItemFont::create("CONTINUE", CC_CALLBACK_1(PopLayer::onContinue, this));
    auto menuItemRestart = MenuItemFont::create("RESTART", CC_CALLBACK_1(PopLayer::onRestart, this));
    auto menuItemExit = MenuItemFont::create("EXIT", CC_CALLBACK_1(PopLayer::onExit, this));
    
    
    auto menu = Menu::create(menuItemContinue, menuItemRestart, menuItemExit, NULL);
    menu->alignItemsVertically();
    addChild(menu);
    menu->setPosition(centerPos);
    
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PopLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PopLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PopLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    touchListener->setSwallowTouches(true);
    
    return true;
}

void PopLayer::onRestart(Ref* pSender)
{
	if (_offset == 1) {
		Director::getInstance()->replaceScene(TransitionFlipX::create(2,HelloWorld::createScene()));
	}
	else {
		auto gameLevel = UserDefault::getInstance()->getIntegerForKey(LEVEL);
		auto gameUIMode = UserDefault::getInstance()->getIntegerForKey(UIMODE);
		Director::getInstance()->replaceScene(TransitionFlipX::create(2, SpriteSheetScene::createScene(gameLevel,gameUIMode)));
	}
    
    Director::getInstance()->resume();
}

void PopLayer::onExit(Ref* pSender)
{
/*#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif */
	auto scene = GameOverScene::createScene(-1);
	Director::getInstance()->replaceScene(TransitionFlipAngular::create(1,scene));
	Director::getInstance()->resume();
}

void PopLayer::onContinue(Ref* pSender)
{
    removeFromParent();
    Director::getInstance()->resume();
}

bool PopLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

void PopLayer::onTouchMoved(Touch* touch, Event* event)
{
}

void PopLayer::onTouchEnded(Touch* touch, Event* event)
{
}