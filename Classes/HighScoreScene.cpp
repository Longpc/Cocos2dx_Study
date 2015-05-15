#include "HightScoreScene.h"


Scene* HighScore::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vect(0.0f, 0.0f));
	// 'layer' is an autorelease object
	auto layer = HighScore::create();
	//layer->setPhysicWorld(scene->getPhysicsWorld());
	// add layer as a child to scene
	scene->addChild(layer);
	auto infoLayer = InforLayer::create();
	scene->addChild(infoLayer);
	// return the scene
	return scene;
}


bool HighScore::init() {
	if (!Layer::init()) {
		return false;
	}
	auto size = Director::getInstance()->getVisibleSize();

	auto label = Text::create("HIGH SCORE", "fonts/2.ttf", 70);
	label->setPosition(Vec2(size.width / 2, size.height*4/5));
	addChild(label);

	auto name = Text::create("NAME", "fonts/2.ttf", 50);
	name->setPosition(Vec2(size.width*1/3, size.height * 3 / 5));
	addChild(name);

	auto scoreLabel = Text::create("SCORE", "fonts/2.ttf", 50);
	scoreLabel->setPosition(Vec2(size.width * 2 / 3, size.height * 3 / 5));
	addChild(scoreLabel);
	
	topNameView = Text::create("---", "fonts/2.ttf", 40);
	topNameView->setPosition(Vec2(size.width * 1 / 3, size.height * 1 / 2));
	addChild(topNameView);
	
	topScoreView = Text::create("---", "fonts/2.ttf", 40);
	topScoreView->setPosition(Vec2(size.width * 2 / 3, size.height * 1 / 2));
	addChild(topScoreView);

	
	
	auto retryButton = Button::create("Button/blueButton111x71.png", "Button/blueBrightButton111x71.png");
	retryButton->setTouchEnabled(true);
	retryButton->setTitleFontSize(28);
	retryButton->setTitleText("RETRY");
	retryButton->setPosition(Vec2(size.width / 2 - 70, size.height * 1 / 5));
	retryButton->addTouchEventListener(CC_CALLBACK_2(HighScore::retryClickListener, this));

	addChild(retryButton);

	auto backButton = Button::create("Button/redButton111x71.png","Button/redBrightButton111x71.png");
	backButton->setTouchEnabled(true);
	backButton->setTitleFontSize(28);
	backButton->setTitleText("EXIT");
	backButton->setPosition(Vec2(size.width / 2 + 70, size.height * 1 / 5));
	backButton->addTouchEventListener(CC_CALLBACK_2(HighScore::clickBackListener, this));

	addChild(backButton);

	
	string userName;
	int userScore;
	if (UserDefault::getInstance()->getStringForKey("NAME") != "") {
		userName = UserDefault::getInstance()->getStringForKey("NAME");
		userScore = UserDefault::getInstance()->getIntegerForKey("SCORE");
	}
	return true;
}
void HighScore::onEnterTransitionDidFinish() {
	
	/*auto test = new HttpRequest();
	test->setUrl("http://localhost/cocos2dx/test.php");
	HttpClient::getInstance()->send(test); */
	HighScore::httpRequest();


}

void HighScore::httpRequest() {
	auto http = new HttpRequest();
	http->setUrl("http://192.168.0.126/cocos2dx/checktop.php");
	http->setRequestType(HttpRequest::Type::GET);
	http->setResponseCallback(this, httpresponse_selector(HighScore::callback));
	HttpClient::getInstance()->send(http);


}
void HighScore::callback(HttpClient* sender, HttpResponse* response) {
	std::vector<char>* data = response->getResponseData();
	std::string result(data->begin(), data->end());
	cocos2d::log("%s", result.c_str());
	Json* json = Json_create(result.c_str());
	if (json->type == Json_Object) {
		int code = Json_getInt(json, "code", -1);
		std::string name = Json_getString(json, "Name", "");
		int score = Json_getInt(json, "Score",0);
		//cocos2d::log("code %d, \nMsg: %s \n %s", code, msg,md5Pass);

		if (code == 200) {
			if (UserDefault::getInstance()->getIntegerForKey("TOP") > score)
			{
				displayLocalData();
				setNewTopValue(UserDefault::getInstance()->getStringForKey("TOPNAME"), UserDefault::getInstance()->getIntegerForKey("TOPSCORE"));
			}
			else {
				topNameView->setString(name);
				topScoreView->setString(DataUtils::numberToString(score));
				
			}
			return;
		}
		else {
			cocos2d::log("Error when get data");
		}
	}
	else
	{
		cocos2d::log("Some error in JSON");
	}
	displayLocalData();
	
}
void HighScore::displayLocalData()
{
	string topName;
	int topScore;
	topName = UserDefault::getInstance()->getStringForKey("TOPNAME");
	topNameView->setString(topName);
	topScore = UserDefault::getInstance()->getIntegerForKey("TOPSCORE");
	std::stringstream ss;
	ss << topScore;
	topScoreView->setString(ss.str().c_str());
}

void HighScore::setNewTopValue(string name, int score)
{
	string severAddress = "http://192.168.0.126/cocos2dx/settop.php";
	HttpUtils::postTopData(severAddress, name, DataUtils::numberToString(score), CC_CALLBACK_2(HighScore::topCallback, this));
}
void HighScore::topCallback(HttpClient* sender, HttpResponse* response)
{
	std::vector<char>* data = response->getResponseData();
	std::string result(data->begin(), data->end());
	cocos2d::log("%s", result.c_str());
}

void HighScore::clickBackListener(Ref *pSender, Widget::TouchEventType type) {
	cocos2d::log("Click back");
	//removeFromParent();
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameOverScene::createScene(-1)));
		Director::getInstance()->resume();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}
void HighScore::retryClickListener(Ref *pSender, Widget::TouchEventType type) {
	cocos2d::log("Click back");
	//removeFromParent();
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:

		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		Director::getInstance()->replaceScene(TransitionFlipX::create(1, ModeSelect::createScene()));
		Director::getInstance()->resume();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

	
}
