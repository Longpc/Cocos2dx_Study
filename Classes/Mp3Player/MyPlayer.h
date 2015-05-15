#ifndef MY_MP3_PLAYER_H__
#define MY_MP3_PLAYER_H__

#include <math.h>
#include <string.h>
#include "../base/BaseLayer.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

#include "../GameOverScene.h"
#include "../JNI/JNICall.h"

class MyPlayer :public BaseLayer
{
public:
	virtual void onEnter() override;
	virtual void onExit() override;

	virtual void exitCallback(Ref *pSender) override;
	virtual void restartCallback(Ref *pSender) override;
	virtual void debugCallback(Ref *pSender) override;

	static Scene* createScene();
	CREATE_FUNC(MyPlayer);

	bool init();
	void update(float dt);
private:
	virtual void playButtonCallback(Ref * pSender, Widget::TouchEventType type);
	virtual void stopButtonCallback(Ref *pSender, Widget::TouchEventType type);
	virtual void loopButtonCallback(Ref *pSender, Widget::TouchEventType type);
	virtual void previousButtonCallback(Ref *pSender, Widget::TouchEventType type);
	virtual void nextButtonCallback(Ref *pSender, Widget::TouchEventType type);
	virtual void selectFileButtonCallback(Ref *pSender, Widget::TouchEventType type);

	virtual void lighButtonCallback(Ref *pSender, Widget::TouchEventType type);
	virtual void muteButtonCallback(Ref *pSender, Widget::TouchEventType type);
	virtual void onVolumeSlider(Ref *psender,Slider::EventType type);
	virtual void onTimeSlider(Ref *pSender, Slider::EventType type);
	virtual void playEndCallback(int id, const string& filePath);
	virtual void touchTimeSlider(Ref *pSender, Widget::TouchEventType type);

	virtual vector<string> getFileList();
	virtual void playCurentEffect();
	virtual void stopEffect();
	virtual string timeFloattoString(float time);
	virtual void SimpleDelayTimer(float timInSecond);
	virtual void removeTouchDelay(Ref *pSender);

	Button *_playButton;
	Button *_pauseButton;
	Button *_stopButon;
	Button *_loopButton;

	Button *_previousButton;
	Button *_nextButton;
	Button *_selectFileButton;

	Button *_lightButton;
	Button *_muteButon;
	Slider *_volumeSlider;
	Slider *_timeSlider;
	Text *_timeView;
	Text *_songNameView;
	Text *_curentSongIndexView;

	bool _onPlaying = false;
	bool _onPause = false;
	bool _onLooping = false;
	bool _onMuting = false;
	bool _onSlideTime = false;
	bool _playEnded = false;
	bool _onDelay = false;
	bool _onKeepSceneOn = false;

	vector<string> filelist;
	int curentFile = 1;
	unsigned int curentEffectId;
	int saveVolume;
	int maxFile = 0;
};


#endif