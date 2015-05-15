#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__
#include "cocos2d.h"
#include "network/HttpClient.h"

#include "Define.h"
#include "TestTime.h"
#include "Ball.h"
#include "HelloWorldScene.h"
#include "TestBodyParser.h"
#include "SpriteSheetScene.h"
#include "TestNewGUI.h"
#include "ModeSelectScene.h"
#include "TestBox2D.h"
#include "TestChipmurk.h"
#include "TestJoint.h"
#include "sqlUtils/sqlite3.h"
#include "sqlUtils/SqlUtils.h"
#include "sqlUtils/DataUtils.h"
#include "ParticleSystem.h"
#include "CustomScroll.h"
#include "JumpGame.h"
#include "MyWebView.h"
#include "multitouch/MultiTouchTest.h"
#include "JNI/JNICall.h"
#include "Mp3Player/MyPlayer.h"
#include "TestFollow/TestFollow.h"
#include "TestFollow/RotateWithVeloc.h"
#include "TMXMap/TmxMapScene.h"
#include "JNI/JNIAlert.h"
#include "GAF/GAFTest.h"
USING_NS_CC;
using namespace std;
using namespace ui;

class GameOverScene : public Layer
{
public:
	GameOverScene();
	~GameOverScene();

	static Scene* createScene(int gameScore);
	static GameOverScene* create(int score);
	virtual bool init(int score);
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
	
	virtual void pSomthing();
	virtual void touchNewUI(Ref *pSender, Widget::TouchEventType type);
	virtual void touchBox2D(Ref *pSender, Widget::TouchEventType type);
	virtual void touchChip(Ref *pSender, Widget::TouchEventType type);
	virtual void touchJoint(Ref *pSender, Widget::TouchEventType type);
	virtual void touchParticle(Ref *pSender, Widget::TouchEventType type);
	virtual void touchJumpGame(Ref *pSender, Widget::TouchEventType type);
	virtual void touchWebView(Ref *pSender, Widget::TouchEventType type);
	virtual void touchCustomScroll(Ref *pSender, Widget::TouchEventType type);
	virtual void tochMultiTouch(Ref *pSender, Widget::TouchEventType type);
	virtual void touchMp3Player(Ref *pSender, Widget::TouchEventType type);
	virtual void touchTestFollow(Ref *pSender, Widget::TouchEventType type);
	virtual void touchRotate(Ref *pSender, Widget::TouchEventType type);
	virtual void touchTMXTileMap(Ref *pSender, Widget::TouchEventType type);
	virtual void touchGAFTest(Ref *pSender, Widget::TouchEventType type);
	


	virtual void onNativeButonCallback(int tag, NativeAlert::ButtonType type);
	
private:
	cocos2d::Sprite* playButton;
	cocos2d::Sprite* exitButton;
	cocos2d::Label* gameScoreView;
	cocos2d::Label* testBodyParser;
	cocos2d::Label* testSpriteSheet;
	int gameScore;
	int selectFlg = -1;
	Size size;
	virtual void replayGame();
	virtual void exitGame();

};

#endif
