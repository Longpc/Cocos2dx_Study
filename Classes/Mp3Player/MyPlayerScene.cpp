#include "MyPlayer.h"

void MyPlayer::onEnter()
{
	BaseLayer::onEnter();
	
	srand(time(NULL));
	this->scheduleUpdate();
}

void MyPlayer::onExit()
{
	BaseLayer::onExit();
	//experimental::AudioEngine::stopAll();
	//experimental::AudioEngine::uncacheAll();
}

void MyPlayer::update(float dt)
{
	if (_onPlaying == true) {
		auto a = experimental::AudioEngine::getCurrentTime(curentEffectId);
		auto b = experimental::AudioEngine::getDuration(curentEffectId);
		
		if (_timeSlider != nullptr && _onSlideTime == false) {
			//log("a b p: %f %f %f", a, b, a / b*100);
			_timeSlider->setPercent(round(a / b*100));
		}
		string cur = timeFloattoString(a);
		string total = timeFloattoString(b);
		string text = cur.append(" / ").append(total);
		if (_timeView != nullptr) {
			_timeView->setString(text);
		}

	}
	if (_playEnded) {
		_playEnded = false;
		playCurentEffect();
	}
	
}

void MyPlayer::exitCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, GameOverScene::createScene(-1)));
}

void MyPlayer::restartCallback(Ref *pSender)
{

}

void MyPlayer::debugCallback(Ref *pSender)
{

}

Scene* MyPlayer::createScene()
{
	auto scene = Scene::create();
	auto layer = MyPlayer::create();
	scene->addChild(layer);

	return scene;
}

bool MyPlayer::init()
{
	if (!BaseLayer::init()) {
		return false;
	}
	filelist = getFileList();
	/*char fimename[20] = { 0 };
	for (int i = 1; i < 9; i++)
	{
		sprintf(fimename, "(%d).mp3", i);
		//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(fimename);
	}*/

	auto back = Sprite::create("Player/background/2.png");
	back->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
	addChild(back, -100);


	_playButton = Button::create();
	_playButton->loadTextureNormal("Player/button/play.png");
	_playButton->setTouchEnabled(true);
	_playButton->addTouchEventListener(CC_CALLBACK_2(MyPlayer::playButtonCallback, this));
	_playButton->setPosition(Vec2(_visibleSize.width / 2, 150));
	addChild(_playButton, 100);

	_previousButton = Button::create();
	_previousButton->loadTextureNormal("Player/button/previous.png");
	_previousButton->setTouchEnabled(true);
	_previousButton->addTouchEventListener(CC_CALLBACK_2(MyPlayer::previousButtonCallback, this));
	_previousButton->setPosition(Vec2(_visibleSize.width/2 - 80, 150));
	addChild(_previousButton, 100);

	_nextButton = Button::create();
	_nextButton->loadTextureNormal("Player/button/next.png");
	_nextButton->setTouchEnabled(true);
	_nextButton->addTouchEventListener(CC_CALLBACK_2(MyPlayer::nextButtonCallback, this));
	_nextButton->setPosition(Vec2(_visibleSize.width/2 + 80, 150));
	addChild(_nextButton, 100);

	_muteButon = Button::create();
	_muteButon->setTouchEnabled(true);
	_muteButon->loadTextureNormal("Player/button/unmute.png");
	_muteButon->addTouchEventListener(CC_CALLBACK_2(MyPlayer::muteButtonCallback, this));
	_muteButon->setPosition(Vec2(_visibleSize.width/2 - 160, 150));
	addChild(_muteButon, 100);

	_selectFileButton = Button::create();
	_selectFileButton->setTouchEnabled(true);
	_selectFileButton->loadTextureNormal("Player/button/open.png");
	_selectFileButton->addTouchEventListener(CC_CALLBACK_2(MyPlayer::selectFileButtonCallback, this));
	_selectFileButton->setPosition(Vec2(_visibleSize.width / 2 - 240, 150));
	addChild(_selectFileButton, 100);

	_stopButon = Button::create();
	_stopButon->setTouchEnabled(true);
	_stopButon->loadTextureNormal("Player/button/stop.png");
	_stopButon->addTouchEventListener(CC_CALLBACK_2(MyPlayer::stopButtonCallback, this));
	_stopButon->setPosition(Vec2(_visibleSize.width / 2 + 160, 150));
	addChild(_stopButon, 100);

	_loopButton = Button::create();
	_loopButton->setTouchEnabled(true);
	_loopButton->loadTextureNormal("Player/button/loopA.png");
	_loopButton->addTouchEventListener(CC_CALLBACK_2(MyPlayer::loopButtonCallback, this));
	_loopButton->setPosition(Vec2(_visibleSize.width/2 + 240, 150));
	addChild(_loopButton, 100);

	_volumeSlider = Slider::create();
	_volumeSlider->loadBarTexture("Player/slider/sliderTrack.png");
	_volumeSlider->loadSlidBallTextures("Player/slider/sliderThumb.png", "Player/slider/sliderThumb.png");
	_volumeSlider->loadProgressBarTexture("Player/slider/sliderProgress.png");
	_volumeSlider->addEventListener(CC_CALLBACK_2(MyPlayer::onVolumeSlider, this));
	_volumeSlider->setContentSize(Size(_visibleSize.width - 200, 25));
	_volumeSlider->setPercent(JNICall::getCurentVolumeinPercent());
	addChild(_volumeSlider, 100);
	_volumeSlider->setPosition(Vec2(_visibleSize.width / 2, 250));

	_timeSlider = Slider::create();
	_timeSlider->loadBarTexture("Player/slider/timeTrack.png");
	_timeSlider->loadSlidBallTextures("Player/slider/timeThumb.png", "Player/slider/timeThumb.png");
	_timeSlider->loadProgressBarTexture("Player/slider/timeProgress.png");
	_timeSlider->addEventListener(CC_CALLBACK_2(MyPlayer::onTimeSlider, this));
	_timeSlider->addTouchEventListener(CC_CALLBACK_2(MyPlayer::touchTimeSlider, this));
	_timeSlider->setContentSize(Size(_visibleSize.width - 200, 25));
	_timeSlider->setPercent(0);
	addChild(_timeSlider);
	_timeSlider->setPosition(Vec2(_visibleSize.width / 2, 350));

	_timeView = Text::create();
	_timeView->setTextColor(Color4B::RED);
	_timeView->setFontSize(25);
	_timeView->setPosition(Vec2(_visibleSize.width / 2, 450));
	_timeView->setString("--:-- / --:--");
	addChild(_timeView);

	_songNameView = Text::create();
	_songNameView->setTextColor(Color4B::RED);
	_songNameView->setFontSize(25);
	_songNameView->setPosition(Vec2(_visibleSize.width / 2, 510));
	_songNameView->setString("name");
	addChild(_songNameView);

	_curentSongIndexView = Text::create();
	_curentSongIndexView->setTextColor(Color4B::BLACK);
	_curentSongIndexView->setFontSize(25);
	_curentSongIndexView->setPosition(Vec2(_visibleSize.width / 2, 600));
	_curentSongIndexView->setString("0/0");
	addChild(_curentSongIndexView);

	_lightButton = Button::create();
	_lightButton->setTouchEnabled(true);
	_lightButton->loadTextureNormal("Player/button/lightoff.png");
	_lightButton->addTouchEventListener(CC_CALLBACK_2(MyPlayer::lighButtonCallback, this));
	_lightButton->setPosition(Vec2(_visibleSize.width / 2, 80));
	addChild(_lightButton, 100);


	return true;
}

void MyPlayer::playButtonCallback(Ref * pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		
		if (_onPlaying == false)
		{
			_playButton->loadTextureNormal("Player/button/pause.png");
			_onPlaying = true;
			if (_onPause == false) {
				playCurentEffect();

			}
			else {
				_onPause = false;
				//CocosDenshion::SimpleAudioEngine::getInstance()->resumeEffect(curentEffectId);
				experimental::AudioEngine::resume(curentEffectId);
			}
			
		}
		else
		{
			_playButton->loadTextureNormal("Player/button/play.png");
			_onPlaying = false;
			//CocosDenshion::SimpleAudioEngine::getInstance()->pauseEffect(curentEffectId);
			experimental::AudioEngine::pause(curentEffectId);
			_onPause = true;
		}
		break; 
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	

}

void MyPlayer::stopButtonCallback(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		//CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
		experimental::AudioEngine::stopAll();
		_onPause = false;
		_onPlaying = false;
		_playButton->loadTextureNormal("Player/button/play.png");
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void MyPlayer::loopButtonCallback(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		if (_onLooping == false)
		{
			_onLooping = true;
			experimental::AudioEngine::setLoop(curentEffectId, true);
			_loopButton->loadTextureNormal("Player/button/loop1.png");
		} 
		else
		{
			_onLooping = false;
			experimental::AudioEngine::setLoop(curentEffectId, false);
			_loopButton->loadTextureNormal("Player/button/loopA.png");
		}
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}

}

void MyPlayer::previousButtonCallback(Ref *pSender, Widget::TouchEventType type)
{
	if (_onDelay) {
		return;
	}
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		SimpleDelayTimer(0.5f);
		curentFile = curentFile - 1;
		if (curentFile < 1) {
			curentFile = maxFile;
		}
		_playButton->loadTextureNormal("Player/button/pause.png");
		_onPlaying = true;
		_onPause = false;
		playCurentEffect();
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void MyPlayer::nextButtonCallback(Ref *pSender, Widget::TouchEventType type)
{
	if (_onDelay)
	{
		return;
	}
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		SimpleDelayTimer(0.5f);
		curentFile = curentFile+ 1;
		if (curentFile > maxFile) {
			curentFile = 1;
		}
		_playButton->loadTextureNormal("Player/button/pause.png");
		_onPlaying = true;
		_onPause = false;
		playCurentEffect();
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void MyPlayer::selectFileButtonCallback(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		//getFileList();
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
	
}

void MyPlayer::muteButtonCallback(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		if (_onMuting) {
			_muteButon->loadTextureNormal("Player/button/unmute.png");
			_onMuting = false;
			_volumeSlider->setPercent(saveVolume);
			JNICall::setVolume(saveVolume);
		}
		else {
			_muteButon->loadTextureNormal("Player/button/mute.png");
			_onMuting = true;
			saveVolume = _volumeSlider->getPercent();
			_volumeSlider->setPercent(0);
			JNICall::setVolume(0);
		}
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void MyPlayer::onVolumeSlider(Ref *psender, Slider::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
	{
		JNICall::setVolume(_volumeSlider->getPercent());
		_onMuting = false;
		_muteButon->loadTextureNormal("Player/button/unmute.png");
		break;
	}
	default:
		break;
	}
}
void MyPlayer::onTimeSlider(Ref *pSender, Slider::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
	{
		float time = _timeSlider->getPercent()* experimental::AudioEngine::getDuration(curentEffectId) / 100;
		//log("time %f percent: %d", time,_timeSlider->getPercent());
		experimental::AudioEngine::setCurrentTime(curentEffectId,time);
	}
		break;
	default:
		break;
	}
}

vector<string> MyPlayer::getFileList()
{
	string path = FileUtils::getInstance()->getWritablePath() + string("Music/Music");

	
	string path3 = JNICall::getWriteablePathJNI();
	string path4 = path3 + string("/mp3");
	string path2 = path3 + string("/Music/Music");
	vector<string> result = FileUtils::getInstance()->getSearchPaths();

	result.insert(result.begin(),path);
	result.insert(result.begin(), path2);
	result.insert(result.begin(), path3);
	result.insert(result.begin(), path4);
	FileUtils::getInstance()->setSearchPaths(result);
	maxFile = JNICall::preLoad();

	return result;
}

void MyPlayer::playCurentEffect()
{
	if (maxFile < 1) return;
	stopEffect();
	string fName = JNICall::getMp3FileName(curentFile);
	string a = "";
	while (strcmp(fName.c_str(), a.c_str()) == 0)
	{
		curentFile++;
		if(curentFile > maxFile) {
			curentFile = 1;
		}
		if (curentFile < 1) {
			curentFile = maxFile;
		}
		fName = JNICall::getMp3FileName(curentFile);
	}
	string path = FileUtils::getInstance()->fullPathForFilename(fName.c_str());
	_songNameView->setString(fName);
	//curentEffectId = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(fimename);
	auto soundId = experimental::AudioEngine::play2d(fName.c_str());
	log("Sound id %d ", soundId);
	curentEffectId = soundId;
	experimental::AudioEngine::setFinishCallback(soundId, CC_CALLBACK_2(MyPlayer::playEndCallback,this));
	if (_curentSongIndexView != nullptr) {
		_curentSongIndexView->setString(DataUtils::numberToString(curentFile) + "/" + DataUtils::numberToString(maxFile));
	}
}

void MyPlayer::stopEffect()
{
	//CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
	experimental::AudioEngine::stopAll();
}

void MyPlayer::playEndCallback(int id, const string& filePath)
{
	curentFile++;
	_playEnded = true;
}

string MyPlayer::timeFloattoString(float time)
{
	if (time < 0) return "--:--";
	char Mtotal[10] = { 0 };
	char Stotal[10] = { 0 };
	int tMinute = time / 60;
	if (tMinute < 10) {
		sprintf(Mtotal, "0%d", tMinute);
	}
	else {
		sprintf(Mtotal, "%d", tMinute);
	}
	int tSecond = int(trunc(time)) % 60;
	if (tSecond < 10) {
		sprintf(Stotal, "0%d", tSecond);
	}
	else {
		sprintf(Stotal, "%d", tSecond);
	}

	string ret = "";
	ret.append(Mtotal).append(":").append(Stotal);
	return ret;
}

void MyPlayer::touchTimeSlider(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
	{
		_onSlideTime = true;
	}
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		_onSlideTime = false;
	}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void MyPlayer::SimpleDelayTimer(float time)
{
	_onDelay = true;
	DelayTime *delay = DelayTime::create(time);
	CallFuncN *callFu = CallFuncN::create(CC_CALLBACK_1(MyPlayer::removeTouchDelay, this));
	this->runAction(Sequence::createWithTwoActions(delay, callFu));
}

void MyPlayer::removeTouchDelay(Ref *pSEnder)
{
	_onDelay = false;
}

void MyPlayer::lighButtonCallback(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		if (_onKeepSceneOn == true) {
			_onKeepSceneOn = false;
			_lightButton->loadTextureNormal("Player/button/lightoff.png");
			JNICall::unsetScreenOn();
		}
		else {
			_onKeepSceneOn = true;
			_lightButton->loadTextureNormal("Player/button/lighton.png");
			JNICall::setScreenOn();
		}
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}


