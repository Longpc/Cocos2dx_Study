#include "ModeSelectScene.h"

Scene* ModeSelect::createScene() {
	auto scene = Scene::create();
	auto layer = ModeSelect::create();

	scene->addChild(layer);

	return scene;
}
ModeSelect* ModeSelect::create() {
	ModeSelect *layer = new ModeSelect();
	if (layer->init()) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
bool ModeSelect::init() {
	if (!Layer::init()) {
		return false;
	}
	gameLevel = UserDefault::getInstance()->getIntegerForKey(LEVEL);
	gameUIMode = UserDefault::getInstance()->getIntegerForKey(UIMODE);
	if (gameLevel == 0) {
		gameLevel = 4;
		gameUIMode = 1;
	}
	auto size = Director::getInstance()->getVisibleSize();
	Label* pageLabel = Label::create("Game Setting", "fonts/Amatic-Bold.ttf", 60);
	pageLabel->setPosition(Vec2(size.width / 2, size.height * 5 / 6));
	addChild(pageLabel);

	auto modeLabel = Label::create("Game Level", "fonts/2.ttf", 45);
	modeLabel->setPosition(Vec2(size.width / 4, size.height * 4 / 6));
	addChild(modeLabel);

	auto uiLabel = Label::create("UI Mode", "fonts/2.ttf", 35);
	uiLabel->setPosition(Vec2(size.width * 3 / 4, size.height * 4 / 6));
	addChild(uiLabel);

	modeEasy = CheckBox::create("checkbox/check_box_normal.png",
								"checkbox/check_box_normal_press.png",
								"checkbox/check_box_active.png",
								"checkbox/check_box_normal_disable.png",
								"checkbox/check_box_active_disable.png");
	modeEasy->setPosition(Vec2(size.width * 1 / 6, size.height * 9 / 18));
	modeEasy->addEventListener(CC_CALLBACK_2(ModeSelect::easyChooseListenr, this));
	if (gameLevel == 4)  {
		modeEasy->setSelected(true);
		modeEasy->setTouchEnabled(false);
	}
	addChild(modeEasy);


	modeNormal = CheckBox::create("checkbox/check_box_normal.png",
		"checkbox/check_box_normal_press.png",
		"checkbox/check_box_active.png",
		"checkbox/check_box_normal_disable.png",
		"checkbox/check_box_active_disable.png");
	modeNormal->setPosition(Vec2(size.width * 1 / 6, size.height * 7 / 18));
	modeNormal->addEventListener(CC_CALLBACK_2(ModeSelect::normalChooseListenr, this));
	if (gameLevel == 5) {
		modeNormal->setSelected(true);
		modeNormal->setTouchEnabled(false);
	}
	addChild(modeNormal);

	modeHard = CheckBox::create("checkbox/check_box_normal.png",
		"checkbox/check_box_normal_press.png",
		"checkbox/check_box_active.png",
		"checkbox/check_box_normal_disable.png",
		"checkbox/check_box_active_disable.png");
	modeHard->setPosition(Vec2(size.width * 1 / 6, size.height * 5 / 18));
	modeHard->addEventListener(CC_CALLBACK_2(ModeSelect::hardChooseListenr, this));
	if (gameLevel == 6) {
		modeHard->setSelected(true);
		modeHard->setTouchEnabled(false);
	}
	addChild(modeHard);

	fruitMode = CheckBox::create("checkbox/check_box_normal.png",
		"checkbox/check_box_normal_press.png",
		"checkbox/check_box_active.png",
		"checkbox/check_box_normal_disable.png",
		"checkbox/check_box_active_disable.png");
	fruitMode->setPosition(Vec2(size.width * 4 / 6, size.height * 8 / 18));
	fruitMode->addEventListener(CC_CALLBACK_2(ModeSelect::fruitChooseListenr, this));
	if (gameUIMode == 1) {
		fruitMode->setSelected(true);
		fruitMode->setTouchEnabled(false);
	}
	addChild(fruitMode);

	bearMode = CheckBox::create("checkbox/check_box_normal.png",
		"checkbox/check_box_normal_press.png",
		"checkbox/check_box_active.png",
		"checkbox/check_box_normal_disable.png",
		"checkbox/check_box_active_disable.png");
	bearMode->setPosition(Vec2(size.width * 4 / 6, size.height * 6 / 18));
	bearMode->addEventListener(CC_CALLBACK_2(ModeSelect::bearChooseListenr, this));
	if (gameUIMode == 2) {
		bearMode->setSelected(true);
		bearMode->setTouchEnabled(false);
	}
	addChild(bearMode);

	startButton = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	startButton->setTouchEnabled(true);
	startButton->setTitleFontSize(28);
	startButton->setTitleText("START");
	startButton->setPosition(Vec2(size.width / 2, size.height * 1 / 8));
	startButton->addTouchEventListener(CC_CALLBACK_2(ModeSelect::clickStart, this));
	addChild(startButton);

	auto easyLabel = Label::create("Easy", "fonts/2.ttf", 35);
	easyLabel->setPosition(Vec2(size.width / 4 + 10, size.height * 9 / 18));
	addChild(easyLabel);

	auto normalLabel = Label::create("Normal", "fonts/2.ttf", 35);
	normalLabel->setPosition(Vec2(size.width / 4 + 21, size.height * 7 / 18));
	addChild(normalLabel);

	auto hardLabel = Label::create("Hard", "fonts/2.ttf", 35);
	hardLabel->setPosition(Vec2(size.width / 4 + 10, size.height * 5 / 18));
	addChild(hardLabel);

	auto fruitLabel = Label::create("Fruit", "fonts/2.ttf", 35);
	fruitLabel->setPosition(Vec2(size.width *3/ 4 + 10, size.height * 8 / 18));
	addChild(fruitLabel);
	auto bearLabel = Label::create("Bear", "fonts/2.ttf", 35);
	bearLabel->setPosition(Vec2(size.width *3/ 4+ 10, size.height * 6 / 18));
	addChild(bearLabel);


	return true;
}
void ModeSelect::clickStart(Ref *pSender, Widget::TouchEventType type) {
	cocos2d::log("start");
	
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionZoomFlipX::create(1, SpriteSheetScene::createScene(gameLevel,gameUIMode)));
		break; 
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
void ModeSelect::easyChooseListenr(Ref* pSender, CheckBox::EventType type) {
	cocos2d::log("easy");
	modeEasy->setTouchEnabled(false);
	modeNormal->setSelected(false);
	modeNormal->setTouchEnabled(true);
	modeHard->setSelected(false);
	modeHard->setTouchEnabled(true);
	gameLevel = 4;
}
void ModeSelect::normalChooseListenr(Ref* pSender, CheckBox::EventType type){
	cocos2d::log("normal");
	gameLevel = 5;
	modeNormal->setTouchEnabled(false);
	modeEasy->setSelected(false);
	modeEasy->setTouchEnabled(true);
	modeHard->setSelected(false);
	modeHard->setTouchEnabled(true);
}
void ModeSelect::hardChooseListenr(Ref* pSender, CheckBox::EventType type){
	cocos2d::log("hard");
	modeHard->setTouchEnabled(false);
	modeEasy->setSelected(false);
	modeEasy->setTouchEnabled(true);
	modeNormal->setSelected(false);
	modeNormal->setTouchEnabled(true);
	gameLevel = 6;
}
void ModeSelect::fruitChooseListenr(Ref* pSender, CheckBox::EventType type){
	cocos2d::log("fruit");
	gameUIMode = 1;
	fruitMode->setTouchEnabled(false);
	bearMode->setSelected(false);
	bearMode->setTouchEnabled(true);
}
void ModeSelect::bearChooseListenr(Ref* pSender, CheckBox::EventType type){
	cocos2d::log("bear");
	gameUIMode = 2;
	bearMode->setTouchEnabled(false);
	fruitMode->setSelected(false);
	fruitMode->setTouchEnabled(true);
}
/*void ModeSelect::retryClickListener(Ref *pSender, Widget::TouchEventType type){

} */