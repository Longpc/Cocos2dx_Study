#include "TestNewGUI.h"

Scene* TestNewGUI::createScene() {
	auto scene = Scene::create();
	auto layer = TestNewGUI::create();
	scene->addChild(layer);
	return scene;
}

bool TestNewGUI::init() {
	if (!Layer::init()) {
		return false;
	}
	screenSize = Director::getInstance()->getWinSize();
	testButton = Button::create("Button/blueButton181x71.png","Button/blueBrightBUtton181x71.png");
	testButton->setTouchEnabled(true);
	//testButton->loadTextureNormal("Button/blueButton181x71.png");
	//testButton->loadTexturePressed("Button/blueBrightButton181x71");
	testButton->setTitleText("CLICK ME");
	testButton->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2 + 100));
	testButton->addTouchEventListener(CC_CALLBACK_2(TestNewGUI::touchEvent,this));
	
	//addChild(testButton);
	
	slider = Slider::create();
	slider->loadBarTexture("Button/slider_bar.png");
	slider->loadSlidBallTextures("Button/slider_bar_button.png", "Button/slider_bar_button.png", "");
	slider->loadProgressBarTexture("Button/process.png");
	slider->setScale9Enabled(true);
	slider->setCapInsets(Rect(0, 0, 0, 0));
	slider->setContentSize(Size(250.0f, 19));
	slider->setPosition(Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f - 100 + slider->getContentSize().height * 3.0f));
	slider->addEventListener(CC_CALLBACK_2(TestNewGUI::sliderEvent, this));
	
	//this->addChild(slider); 

	textView = Text::create("This is text define by Text New UI", "fonts/2.ttf", 40);
	textView->setColor(Color3B(212, 232, 11));
	textView->setPosition(Vec2(300, 100));
	//addChild(textView);

	this->scheduleUpdate();

	layer = LayerGradient::create(Color4B(255,248,230,255),Color4B(255,250,250,255));
	layer->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	layer->setPosition(Vec2(0,-screenSize.height));
	layer->setContentSize(Size(screenSize.width, screenSize.height * 2));

	layer->addChild(testButton);
	layer->addChild(slider);
	layer->addChild(textView);

	scroll = cocos2d::extension::ScrollView::create();
	scroll->setViewSize(Size(screenSize.width,screenSize.height));
	scroll->setPosition(Vec2::ZERO);
	scroll->setAnchorPoint(Vec2::ZERO);
	scroll->setContentOffset(scroll->minContainerOffset());
	scroll->setDirection(extension::ScrollView::Direction::BOTH);
	scroll->setContainer(layer);
	scroll->updateInset();

	scroll->setVisible(true);
	addChild(scroll);
	

	button2 = Button::create("Button/redButton111x71.png", "Button/redBrightButton111x71.png");
	button2->setTouchEnabled(true);
	button2->setTitleText("testHttp");
	button2->setAnchorPoint(Vec2::ZERO);
	button2->setPosition(Vec2(0, 0));
	button2->addTouchEventListener(CC_CALLBACK_2(TestNewGUI::touchButton2, this));
	layer->addChild(button2);
	auto layerSize = layer->getContentSize();

	formLabel = TextField::create("LOGIN FORM", "", 50);
	formLabel->setEnabled(false);
	formLabel->setContentSize(Size(400, 70));
	formLabel->setBrightStyle(Widget::BrightStyle::HIGHLIGHT);
	formLabel->setTextHorizontalAlignment(TextHAlignment::CENTER);
	formLabel->setTextVerticalAlignment(TextVAlignment::CENTER);
	formLabel->setColor(Color3B::GREEN);
	formLabel->setPosition(Vec2(layerSize.width / 2, layerSize.height - 100));
	layer->addChild(formLabel);

	userInput = ui::EditBox::create(Size(400, 70), ui::Scale9Sprite::create("background.png"), NULL);
	userInput->setFontColor(Color3B::GREEN);
	userInput->setPlaceHolder("user name");
	userInput->setMaxLength(30);
	userInput->setFontSize(30);
	userInput->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	userInput->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	userInput->setInputFlag(ui::EditBox::InputFlag::SENSITIVE);
	userInput->retain();
	userInput->setPosition(Vec2(layerSize.width / 2, formLabel->getPositionY() - 100));
	layer->addChild(userInput);

	passwordInput = ui::EditBox::create(Size(400, 70), ui::Scale9Sprite::create("background.png"), NULL);
	passwordInput->setFontColor(Color3B::GREEN);
	passwordInput->setPlaceHolder("********");
	passwordInput->setMaxLength(30);
	passwordInput->setFontSize(30);
	passwordInput->setInputMode(ui::EditBox::InputMode::ANY);
	passwordInput->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	passwordInput->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	passwordInput->retain();
	passwordInput->setPosition(Vec2(layerSize.width / 2, userInput->getPositionY() - 100));
	layer->addChild(passwordInput);
	
	submitButton = Button::create("Button/normal.png","Button/clicked.png");
	submitButton->setTouchEnabled(true);
	submitButton->setTitleFontSize(30);
	submitButton->setTitleColor(Color3B::MAGENTA);
	submitButton->setTitleText("LOGIN");
	submitButton->setPosition(Vec2(passwordInput->getPositionX() - passwordInput->getContentSize().width/2 +submitButton->getContentSize().width/2, passwordInput->getPositionY() - 100));
	submitButton->addTouchEventListener(CC_CALLBACK_2(TestNewGUI::clickLogin, this));
	layer->addChild(submitButton);

	cancelButton = Button::create("Button/normal.png", "Button/clicked.png");
	cancelButton->setTouchEnabled(true);
	cancelButton->setTitleFontSize(30);
	cancelButton->setTitleColor(Color3B::ORANGE);
	cancelButton->setTitleText("CANCEL");
	cancelButton->setPosition(Vec2(passwordInput->getPositionX() +passwordInput->getContentSize().width/2 - cancelButton->getContentSize().width/2, passwordInput->getPositionY() - 100));
	cancelButton->addTouchEventListener(CC_CALLBACK_2(TestNewGUI::clickCancel, this));
	layer->addChild(cancelButton);
	
	actionInfo = Text::create("", "", 25);
	actionInfo->setTextColor(Color4B::RED);
	actionInfo->setTextHorizontalAlignment(TextHAlignment::CENTER);
	actionInfo->setPosition(passwordInput->getPosition() - Vec2(0,200));
	layer->addChild(actionInfo);

	DrawNode* node = DrawNode::create();
	node->drawSegment(Vec2::ZERO, screenSize, 10, Color4F::GREEN);
	layer->addChild(node,-1);

	_textFieldAction = RepeatForever::create(Sequence::create(FadeOut::create(0.5), FadeIn::create(0.5), nullptr));
	_textFieldAction->retain();
	_action = false;
	_textField = TextFieldTTF::textFieldWithPlaceHolder("click here to input","",30);
	layer->addChild(_textField);
	_textField->setPosition(Vec2(layer->getContentSize().width / 2, cancelButton->getPositionY() - 300));
	_textField->setDelegate(this);

	auto label = TextField::create("", "fonts/japan1.ttf", 70);
	label->setPlaceHolder("input name here");
	label->setContentSize(Size(layer->getContentSize().width, 100));
	label->setTextHorizontalAlignment(TextHAlignment::CENTER);
	label->setTextColor(Color4B::BLACK);
	label->setPosition(Vec2(layer->getContentSize().width / 2, _textField->getPositionY() - 200));
	label->addEventListener(CC_CALLBACK_2(TestNewGUI::textFieldEvent, this));
	layer->addChild(label);
	label->setTag(777);


	return true;
}
void TestNewGUI::touchEvent(Ref *pSender, Widget::TouchEventType type) {
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		cocos2d::log("touched");
		//testButton
		slider->setPercent(50);
		TextField *a;
		a = (TextField*)layer->getChildByTag(777);
		if (a->getStringLength() > 0) {
			JNICall::makeCallWithNumberJNI(a->getString().c_str());
		}

	}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}
void TestNewGUI::touchButton2(Ref *pSender, Widget::TouchEventType type) {
	cocos2d::log("TOUCH BUTTON ");
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;

	case cocos2d::ui::Widget::TouchEventType::ENDED:
		TestNewGUI::sendRequest();
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
void TestNewGUI::sendRequest() {
	auto request = new HttpRequest();
	//request->setUrl("http://192.168.0.126/cocos2dx/ball.png");
	request->setUrl("http://192.168.0.126/cocos2dx/test.txt");
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(this,httpresponse_selector(TestNewGUI::callback));
	auto client = HttpClient::getInstance();
	client->enableCookies(NULL);
	client->send(request);
}

void TestNewGUI::callback(HttpClient* client, HttpResponse* response) {
	log("responseCode:%ld %s", response->getResponseCode(), response->getHttpRequest()->getUrl());
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (response->getResponseCode() == 200)
	{
		auto fileUtils = FileUtils::getInstance();
		std::string filepath = fileUtils->getWritablePath() + "text.txt";
		std::vector<char> *resData = response->getResponseData();
		FILE *fp = fopen(filepath.c_str(), "w");
		if (!fp) {
			log("can not create file %s", filepath.c_str());
			return;
		}
		fwrite(resData->data(), 1, resData->size(), fp);
		fclose(fp);
		log("save file into %s", filepath.c_str());
	}
	else {
		
	}
	
	/*d::string filename = fileUtils->getWritablePath() + "hoge.png";
	log("path: %s", fileUtils->getWritablePath());
	if (fileUtils->isFileExist(filename)) {

		auto sprite = Sprite::create(filename.c_str());
		sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(sprite, 0);

	}
	else if (response->isSucceed()) {

		std::vector<char>* buffer = response->getResponseData();
		auto* img = new Image();
		img->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size());
		img->saveToFile(filename.c_str());
		auto* texture = new Texture2D();
		texture->initWithImage(img);
		auto sprite = Sprite::createWithTexture(texture);
		auto sprite2 = Sprite::create(filename.c_str());
		sprite2->setPosition(Vec2(200, 200));
		scroll->addChild(sprite2);
		sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(sprite, 0);

	} */

}
void TestNewGUI::sliderEvent(Ref *pSender, Slider::EventType type) {
	cocos2d::log("on Slide");
	auto pacent = slider->getPercent();
	std::stringstream text;
	text << pacent;
	textView->setString(text.str().c_str());
	JNICall::setVolume(pacent);
}
void TestNewGUI::update(float dt) {
	/*auto pacent = slider->getPercent();
	std::stringstream text;
	text << pacent;
	textView->setText(text.str().c_str()); */
}
void TestNewGUI::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
}
void TestNewGUI::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
}

void TestNewGUI::clickCancel(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		this->checkInputedValues(2);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void TestNewGUI::clickLogin(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		this->checkInputedValues(1);
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
void TestNewGUI::checkInputedValues(int offset)
{
	
	const char *name = userInput->getText();
	const char  *password = passwordInput->getText();
	//cocos2d::log("%s\n %s", name, password);
	if (strlen(name) == 0 || strlen(password) == 0)
	{
		//display error
		return;
	}
	auto scene = LoadingLayer::createScene();
	this->getParent()->addChild(scene);
	if (offset == 1) {
		authWithServer(name, password);
		return;
	}
	if (offset == 2) {
		sigupWithServer(name, password);
	}
}

void TestNewGUI::authWithServer(string username, string password)
{
	/*char *serverURL = "http://192.168.0.126/cocos2dx/auth.php";
	auto httpRequest = new HttpRequest();
	httpRequest->setUrl(serverURL);
	httpRequest->setRequestType(HttpRequest::Type::POST);
	httpRequest->setResponseCallback(CC_CALLBACK_2(TestNewGUI::authenCallback, this));
	httpRequest->setTag("login");
	auto text = "name=" + username + "&pass=" + password;
	cocos2d::log("%s", text);
	const char* buffer = text.c_str();
	cocos2d::log("%s", buffer);
	httpRequest->setRequestData(buffer,strlen(buffer));

	auto client = HttpClient::getInstance();
	client->enableCookies(nullptr);
	client->send(httpRequest); */
	string severAddress = "http://192.168.0.126/cocos2dx/auth.php";
	HttpUtils::postToServer(severAddress,username, password, CC_CALLBACK_2(TestNewGUI::authenCallback, this));
}
void TestNewGUI::sigupWithServer(string username, string password)
{
	string severAddress = "http://192.168.0.126/cocos2dx/sigup.php";
	HttpUtils::postToServer(severAddress, username, password, CC_CALLBACK_2(TestNewGUI::authenCallback, this));
}

void TestNewGUI::authenCallback(HttpClient* client, HttpResponse* response)
{
	if (response->getResponseCode() != 200) {
		log("connect failed");
		return;
	}
	std::vector<char>* data = response->getResponseData();
	std::string result(data->begin(), data->end());
	cocos2d::log("Result JSON: %s",result.c_str());

	Json* json = Json_create(result.c_str());
	if (json == nullptr) return;
	if (json->type == Json_Object) {
		int code = Json_getInt(json, "code",-1);
		std::string msg = Json_getString(json, "msg", "");
		string md5Pass = Json_getString(json, "data", "");
		//cocos2d::log("code %d, \nMsg: %s \n %s", code, msg,md5Pass);
		if (code == 404)
		{
			cocos2d::log("Login failed");
			userInput->setText("");
			passwordInput->setText("");
			return;
		}
		if (code == 200) {
			cocos2d::log("Success");
			Director::getInstance()->replaceScene(TransitionZoomFlipX::create(1, GameOverScene::createScene(-1)));
		}
		else {
			actionInfo->setFontName("fonts/japan1.ttf");
			if (code == 100)
			{
				actionInfo->setString(DataUtils::MultiByteToUTF8("“o˜^‚ª¬Œ÷‚µ‚Ü‚µ‚½B"));
			}
			else {
				actionInfo->setString(DataUtils::MultiByteToUTF8("ƒGƒ‰[‚ªo‚½"));
			}
		}
	}
	else
	{
		cocos2d::log("Some error in JSON");
	}
	
}

bool TestNewGUI::onTextFieldAttachWithIME(TextFieldTTF * sender)
{
	if (!_action) {
		_textField->runAction(_textFieldAction);
		_action = true;
	}
	return false;
}

bool TestNewGUI::onTextFieldDetachWithIME(TextFieldTTF * sender)
{
	if (_action) {
		_textField->stopAction(_textFieldAction);
		_textField->setOpacity(100);
		_action = false;
	}
	return false;
}

bool TestNewGUI::onTextFieldInsertText(TextFieldTTF * sender, const char * text, size_t nLen)
{
	if (*text == '\n')
	{
		return false;
	}
	if (sender->getCharCount() >= _charLimit) {
		return true;
	}
	auto label = Label::createWithSystemFont(text, "", 30);
	layer->addChild(label);
	label->setTextColor(Color4B::RED);

	auto endPoint = sender->getPosition();
	if (sender->getCharCount())
	{
		endPoint.x = sender->getContentSize().width / 2;
	}
	auto inputSize = label->getContentSize();
	Vec2 beginPoint = Vec2(endPoint.x, layer->getContentSize().height - inputSize.height * 2);
	float duration = 0.5;
	label->setPosition(beginPoint);
	label->setScale(10);
	auto seq = Sequence::create(
		Spawn::create(
		MoveTo::create(duration, endPoint),
		ScaleTo::create(duration, 1),
		FadeOut::create(duration),
		nullptr),
		CallFuncN::create(CC_CALLBACK_1(TestNewGUI::endTextAction, this)),
		nullptr);
	label->runAction(seq);
	return false;
}

bool TestNewGUI::onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, size_t nLen)
{
	// create a delete text sprite and do some action
	auto label = Label::createWithSystemFont(delText, "", 30);
	this->addChild(label);

	// move the sprite to fly out
	auto beginPos = sender->getPosition();
	auto textfieldSize = sender->getContentSize();
	auto labelSize = label->getContentSize();
	beginPos.x += (textfieldSize.width - labelSize.width) / 2.0f;

	auto winSize = Director::getInstance()->getWinSize();
	Vec2 endPos(-winSize.width / 4.0f, winSize.height * (0.5 + (float)rand() / (2.0f * RAND_MAX)));

	float duration = 1;
	float rotateDuration = 0.2f;
	int repeatTime = 5;
	label->setPosition(beginPos);

	auto seq = Sequence::create(
		Spawn::create(
		MoveTo::create(duration, endPos),
		Repeat::create(
		RotateBy::create(rotateDuration, (rand() % 2) ? 360 : -360),
		repeatTime),
		FadeOut::create(duration),
		nullptr),
		CallFuncN::create(CC_CALLBACK_1(TestNewGUI::endTextAction, this)),
		nullptr);
	label->runAction(seq);
	return false;
}

bool TestNewGUI::onDraw(TextFieldTTF * sender)
{
	return false;
}

void TestNewGUI::endTextAction(Node *node)
{
	layer->removeChild(node,true);
}

void TestNewGUI::textFieldEvent(Ref *pSener, TextField::EventType type)
{
	TextField *text = (TextField*)pSener;
	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
	{
		if (text->getStringLength() >= _charLimit) return;
		if (!_action) {
			text->runAction(_textFieldAction);
			_action = true;
		}
	}
		break;
	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME: {
		if (_action) {
			
			text->stopAction(_textFieldAction);
			text->setOpacity(100);
			_action = false;
		}
	}
		break;
	case cocos2d::ui::TextField::EventType::INSERT_TEXT: {
		
		if (text->getStringLength() >= _charLimit) {
			return;
		}
		auto t = text->getString();
		auto label = Label::createWithTTF(t.substr(t.length()-1,1), text->getFontName(), 30);
		layer->addChild(label);
		label->setTextColor(Color4B::RED);
		auto endP = text->getPosition();
		auto textfieldSize = text->getContentSize();
		auto labelSize = label->getContentSize();
		endP.x += (textfieldSize.width - labelSize.width) / 2.0f;

		/*auto endPoint = text->getPosition();
		if (text->getStringLength())
		{
			endPoint.x = text->getContentSize().width / 2;
		}*/
		Vec2 beginPoint = Vec2(endP.x, endP.y + labelSize.height * 2);
		float duration = 0.5;
		label->setPosition(beginPoint);
		label->setScale(15);
		auto seq = Sequence::create(
			Spawn::create(
			MoveTo::create(duration, endP),
			ScaleTo::create(duration, 1),
			FadeOut::create(duration),
			nullptr),
			CallFuncN::create(CC_CALLBACK_1(TestNewGUI::endTextAction, this)),
			nullptr);
		label->runAction(seq);
		return;
	}
		break;
	case cocos2d::ui::TextField::EventType::DELETE_BACKWARD: {
		auto t = text->getString();
		if (t.length() <= 0) return;
		auto label = Label::createWithTTF(t.substr(t.length() - 1, 1), text->getFontName(), text->getFontSize());
		label->setTextColor(Color4B::BLACK);
		layer->addChild(label);
		//label->setScale(1.5);
		// move the sprite to fly out
		auto beginPos = text->getPosition();
		auto textfieldSize = text->getContentSize();
		auto labelSize = label->getContentSize();
		beginPos.x += (textfieldSize.width - labelSize.width) / 2.0f;

		auto winSize = Director::getInstance()->getWinSize();
		Vec2 endPos(-winSize.width / 4.0f, winSize.height * (0.5 + (float)rand() / (2.0f * RAND_MAX)));

		float duration = 1;
		float rotateDuration = 0.2f;
		int repeatTime = 5;
		label->setPosition(beginPos);

		auto seq = Sequence::create(
			Spawn::create(
			MoveTo::create(duration, endPos),
			Repeat::create(
			RotateBy::create(rotateDuration, (rand() % 2) ? 360 : -360),
			repeatTime),
			FadeOut::create(duration),
			nullptr),
			CallFuncN::create(CC_CALLBACK_1(TestNewGUI::endTextAction, this)),
			nullptr);
		label->runAction(seq);
		return;
	}
		break;
	default:
		break;
	}
}




