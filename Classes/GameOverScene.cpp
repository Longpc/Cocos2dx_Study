#include "GameOverScene.h"
#include <vector>
USING_NS_CC;
Scene* GameOverScene::createScene(int score) {
	auto scene = cocos2d::Scene::create();
	auto layer = GameOverScene::create(score);
	//auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}
GameOverScene* GameOverScene::create(int score) {
	GameOverScene *layer = new GameOverScene();
	if (layer->init(score)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
bool GameOverScene::init(int score) {
	if (!Layer::init()) {
		return false;
	}
	size = Director::getInstance()->getWinSize();
	auto back = LayerGradient::create(Color4B(186, 226, 210, 200), Color4B(34, 45, 42, 200));
	addChild(back);

	std::stringstream text;
	text << "Score: " << score << std::endl;
	cocos2d::log("%s", text.str().c_str());
	string str;
	if (score >= 0) {
		str = text.str().c_str();
	}
	else {
		str = "Hello";
	}
	string gameName;
	/*// define supported target platform macro which CC uses.
	#define CC_PLATFORM_UNKNOWN            0
	#define CC_PLATFORM_IOS                1
	#define CC_PLATFORM_ANDROID            2
	#define CC_PLATFORM_WIN32              3
	#define CC_PLATFORM_MARMALADE          4
	#define CC_PLATFORM_LINUX              5
	#define CC_PLATFORM_BADA               6
	#define CC_PLATFORM_BLACKBERRY         7
	#define CC_PLATFORM_MAC                8
	#define CC_PLATFORM_NACL               9
	#define CC_PLATFORM_EMSCRIPTEN        10
	#define CC_PLATFORM_TIZEN             11
	#define CC_PLATFORM_QT5               12
	#define CC_PLATFORM_WP8               13
	#define CC_PLATFORM_WINRT             14
	*/
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) {
		gameName = "BLOCK\nBREAKER";
	}
	else {
		gameName = "BLOCK\nBREAKER";
	}
	auto gameLabel = Label::create(gameName, "fonts/1.ttf", 70);
	gameLabel->setPosition(Vec2(size.width / 2, size.height - END_BUTTON_MARGIN_Y));
	addChild(gameLabel);
	
	gameScoreView = Label::create(str, "fonts/2.ttf", 50);

	playButton = Sprite::create("replay.png");

	exitButton = Sprite::create("exit.png");

	testBodyParser = Label::create("TEST BODY", "fonts/2.ttf", 30);
	testBodyParser->setPosition(Vec2(size.width/2, 300));

	testSpriteSheet = Label::create("SPRITE SHEET", "fonts/2.ttf", 30);
	testSpriteSheet->setPosition(Vec2(size.width/2, testBodyParser->getPositionY() - testSpriteSheet->getContentSize().height*2));
	
	

	gameScoreView->setPosition(Vec2(size.width / 2, size.height/2+SCORE_MARGIN));
	playButton->setPosition(Vec2(size.width/2 - END_BUTTON_MARGIN_X, size.height / 2 - END_BUTTON_MARGIN_Y));
	exitButton->setPosition(Vec2(size.width/2 + END_BUTTON_MARGIN_X, size.height / 2 - END_BUTTON_MARGIN_Y));
	
	addChild(gameScoreView);
	addChild(playButton);
	addChild(exitButton);
	addChild(testBodyParser);
	addChild(testSpriteSheet);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameOverScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameOverScene::onTouchEnded, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameOverScene::onTouchMoved, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(GameOverScene::onTouchCancelled, this);
	touchListener->setEnabled(true);
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	

	auto button = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button->setTouchEnabled(true);
	button->setTitleFontSize(30);
	button->setTitleText("BOX2D");
	button->setPosition(Vec2(size.width - button->getContentSize().width/2, 200));
	button->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchBox2D, this));
	addChild(button);

	auto button2 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button2->setTouchEnabled(true);
	button2->setTitleFontSize(30);
	button2->setTitleText("Chip");
	button2->setPosition(Vec2(size.width - button->getContentSize().width/2, 100));
	button2->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchChip, this));
	addChild(button2);

	auto button3 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button3->setTouchEnabled(true);
	button3->setTitleFontSize(30);
	button3->setTitleText("Join");
	button3->setPosition(Vec2(size.width - button->getContentSize().width / 2, 300));
	button3->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchJoint, this));
	addChild(button3);

	auto button4 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button4->setTouchEnabled(true);
	button4->setTitleFontSize(30);
	button4->setTitleText("NewUI");
	button4->setPosition(Vec2(size.width - button->getContentSize().width / 2, 400));
	button4->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchNewUI, this));
	addChild(button4);
	auto button5 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button5->setTouchEnabled(true);
	button5->setTitleFontSize(30);
	button5->setTitleText("Particle");
	button5->setPosition(Vec2(size.width - button->getContentSize().width / 2, 500));
	button5->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchParticle, this));
	addChild(button5);
	auto button6 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button6->setTouchEnabled(true);
	button6->setTitleFontSize(30);
	button6->setTitleText("Custom Scroll");
	button6->setPosition(Vec2(button6->getContentSize().width / 2, 100));
	button6->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchCustomScroll, this));
	addChild(button6);

	auto button7 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button7->setTouchEnabled(true);
	button7->setTitleFontSize(30);
	button7->setTitleText("JUMP");
	button7->setPosition(Vec2(button7->getContentSize().width / 2, 200));
	button7->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchJumpGame, this));
	addChild(button7);
	auto button8 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button8->setTouchEnabled(true);
	button8->setTitleFontSize(30);
	button8->setTitleText("WEBVIEW");
	button8->setPosition(Vec2(button8->getContentSize().width / 2, 300));
	button8->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchWebView, this));
	addChild(button8);
	auto button9 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button9->setTouchEnabled(true);
	button9->setTitleFontSize(30);
	button9->setTitleText("TOUCHES");
	button9->setPosition(Vec2(button9->getContentSize().width / 2, 400));
	button9->addTouchEventListener(CC_CALLBACK_2(GameOverScene::tochMultiTouch, this));
	addChild(button9);
	auto button10 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button10->setTouchEnabled(true);
	button10->setTitleFontSize(30);
	button10->setTitleText("MP3");
	button10->setPosition(Vec2(button10->getContentSize().width / 2, 500));
	button10->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchMp3Player, this));
	addChild(button10);

	auto button11 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button11->setTouchEnabled(true);
	button11->setTitleFontSize(25);
	button11->setTitleText("FOLLOW");
	button11->setPosition(Vec2(size.width / 2 - 70, 100));
	button11->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchTestFollow, this));
	addChild(button11);

	auto button12 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button12->setTouchEnabled(true);
	button12->setTitleFontSize(25);
	button12->setTitleText("ROTATE");
	button12->setPosition(Vec2(size.width / 2 - 70, 200));
	button12->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchRotate, this));
	addChild(button12);

	auto button13 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button13->setTouchEnabled(true);
	button13->setTitleFontSize(25);
	button13->setTitleText("TMX Map");
	button13->setPosition(Vec2(size.width / 2 + 70, 100));
	button13->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchTMXTileMap, this));
	addChild(button13);

	auto button14 = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	button14->setTouchEnabled(true);
	button14->setTitleFontSize(25);
	button14->setTitleText("GAF test");
	button14->setPosition(Vec2(size.width / 2 + 70, 200));
	button14->addTouchEventListener(CC_CALLBACK_2(GameOverScene::touchGAFTest, this));
	addChild(button14);
	/*sqlite3 *pdb = NULL;
	string path = CCFileUtils::getInstance()->getWritablePath() + "db.db3";
	string sql;
	int result;
	result = sqlite3_open(path.c_str(), &pdb);
	if (result != SQLITE_OK) //0
	{
		cocos2d::log("Open db failed, CODE %d", result);
	}
	result = sqlite3_exec(pdb, "create table topscore (ID INTEGER PRIMARY KEY autoincrement, name text,score integer)", NULL, NULL, NULL);
	if (result != SQLITE_OK)
	{
		cocos2d::log("Create table failed %d",result);
	}
	sql = "INSERT INTO topscore(name,score) values('LONG',100000)";
	result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (result != SQLITE_OK)
	{
		cocos2d::log("Insert table failed %d", result);
	}

	char **re;
	int r, c;
	sqlite3_get_table(pdb, "select * from topscore", &re, &r, &c, NULL);
	cocos2d::log("row is %d,column is %d", r, c);
	cocos2d::log("%s", re);
	sqlite3_close(pdb);
	*/
	vector<string> field = { "name", "score" };
	vector<string> value = { "Long", "2342" };
	string tableName = "topscore";
	sqlite3 *test2 = SqlUtil::openData("db.db3");

	vector<string> create = { "name varchar(255)","score varchar(50)" };

	auto res = SqlUtil::createTable(test2, tableName, "ID", "INTEGER", create);
	cocos2d::log("create res code %d", res);


	int resultValue = SqlUtil::insertRow(test2, tableName, field, value);
	//SqlUtil::deleteRow(test2, "topscore", "name", "LONG",true);
	vector<string> a = SqlUtil::runQuery(test2, "select * from topscore");
	/*for (auto & item :a)
	{
		cocos2d::log("%s", item.c_str());
	}*/
	cocos2d::log("Result code: %d", resultValue);
	SqlUtil::closeSQL(test2); 

	return true;
}
void GameOverScene::touchBox2D(Ref *pSender, Widget::TouchEventType type) {
	auto scene = TestBox2D::createScene();
	Director::getInstance()->replaceScene(TransitionJumpZoom::create(2, scene));
}
void GameOverScene::touchChip(Ref *pSender, Widget::TouchEventType type) {
	auto scene = TestChipmurk::createScene();
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
}
bool GameOverScene::onTouchBegan(Touch* touch, Event* event) {
	cocos2d::log("TOuch begin");
	Vec2 point = touch->getLocation();
	Rect rect = playButton->getBoundingBox();
	if (rect.containsPoint(point)) {
		playButton->setScale(1.1f);
		//replayGame();
		selectFlg = REPLAY;
		return true;
	}
	rect = exitButton->getBoundingBox();
	if (rect.containsPoint(point))
	{
		exitButton->setScale(1.1f);
		//exitGame();
		selectFlg = EXIT;
		return true;
	}
	rect = testBodyParser->getBoundingBox();
	if (rect.containsPoint(point)) {
		auto scene = BodyTestScene::createScene();
		Director::getInstance()->replaceScene(TransitionJumpZoom::create(2,scene));
		return true;
	}
	rect = testSpriteSheet->getBoundingBox();
	if (rect.containsPoint(point)) {
		auto scene = ModeSelect::createScene();
		Director::getInstance()->replaceScene(TransitionZoomFlipX::create(1,scene));
		return true;
	}
	if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) {
		JNICall::getWriteablePathJNI();
		JNICall::simpleLogJNI();
		if (JNICall::isVibrateSupported())
		{
			cocos2d::log("true");
		}else {
			cocos2d::log("false");
		}
		JNICall::makeVibrate(1000);
		JNICall::checkDeviceInfo();
	}
	return false;
}
void GameOverScene::pSomthing() {
	cocos2d::log("Something is Running");
}
void GameOverScene::onTouchEnded(Touch* touch, Event* event)
{
	//cocos2d::log("touch ended");
	playButton->setScale(1.0f);
	exitButton->setScale(1.0f);
	if (selectFlg == REPLAY) {
		replayGame();
		return;
	}
	if (selectFlg == EXIT) {
		if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		{
			NativeAlert::showWithCallback("Alert", "Do you want to exit game?", "No", "YES", "", 112, CC_CALLBACK_2(GameOverScene::onNativeButonCallback, this));
		}
		else {
			exitGame();
		}
		return;
	}
}

void GameOverScene::onTouchMoved(Touch* touch, Event* event)
{
	//cocos2d::log("touch moved");
}

void GameOverScene::onTouchCancelled(Touch* touch, Event* event)
{
	//cocos2d::log("touch cancelled");
}
void GameOverScene::replayGame() {
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5,scene,Color3B(0,255,255)));
}
void GameOverScene::exitGame() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
GameOverScene::GameOverScene() {

}
GameOverScene::~GameOverScene() {

}

void GameOverScene::touchJoint(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		auto scene = TestJoint::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(0, 255, 255)));
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}

void GameOverScene::touchNewUI(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		auto scene = TestNewGUI::createScene();
		Director::getInstance()->replaceScene(TransitionZoomFlipY::create(1, scene));
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}

void GameOverScene::touchParticle(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		auto scene = ParticleSystemTest::createScene();
		Director::getInstance()->replaceScene(TransitionFadeDown::create(1, scene));
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}

void GameOverScene::touchCustomScroll(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionFade::create(1, CustomScroll::createScene()));
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameOverScene::touchJumpGame(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionFade::create(1, JumpGame::createScene()));
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameOverScene::touchWebView(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionFade::create(1, MyWeb::createScene()));
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameOverScene::tochMultiTouch(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionFadeDown::create(1, MultiTouchTest::createScene()));
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameOverScene::touchMp3Player(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, MyPlayer::createScene()));
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameOverScene::touchTestFollow(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionFadeDown::create(1, TestFollow::createScene()));
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameOverScene::touchRotate(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		Director::getInstance()->replaceScene(TransitionFadeDown::create(0.5, RotateWithVeloc::createScene()));
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameOverScene::touchTMXTileMap(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		Director::getInstance()->replaceScene(TMXMapScene::createScene());
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void GameOverScene::onNativeButonCallback(int tag, NativeAlert::ButtonType type)
{
	switch (type)
	{
	case cocos2d::NativeAlert::ButtonType::CANCEL:
		break;
	case cocos2d::NativeAlert::ButtonType::OTHER:
		break;
	case cocos2d::NativeAlert::ButtonType::RETURN:
	{
		exitGame();
		break;
	}
	default:
		break;
	}
}

void GameOverScene::touchGAFTest(Ref *pSender, Widget::TouchEventType type)
{
	Director::getInstance()->replaceScene(GAFTest::createScene());
}
