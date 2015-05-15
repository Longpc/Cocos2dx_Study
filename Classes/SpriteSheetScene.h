#ifndef __SPRITE_SCENE_H__
#define __SPRITE_SCENE_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui\CocosGUI.h"

#include "Define.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "MyBodyParser.h"
#include "PopLayer1.h"
#include "FlowerMouse.h"
//#include "DrawLine.h"

#include <math.h>
#include <time.h>


USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace std;

class SpriteSheetScene :public Layer
{
public:
	SpriteSheetScene();
	~SpriteSheetScene();
	PhysicsWorld* _myWorld;
	void setPhysicWorld(PhysicsWorld* world) {
		_myWorld = world;
	}
	static Scene* createScene(int mode, int ui);
	static SpriteSheetScene* create(int mode, int ui);
	virtual bool init(int mode,int ui);
	virtual void update(float dt);
	virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
	virtual Sprite* randomSprite();
	virtual void getTouchedSprite(Vec2 point);
	virtual bool checkCondition(Sprite* sprite, Vec2 point);
	virtual void onEnterTransitionDidFinish();
	virtual void resetOpa();
	virtual string numberToString(string temp, int number);
	virtual void createCusor(Vec2);
private:
	////4 for easy 5 for normal an 6 for hard
	int gameLevel;
	int gameUIMode;

	FlowerMouse *magicMouse;

	Sprite* _backButton;
	Sprite* _ballMan;
	Size size1;
	Action *walkAction;
	Action *moveAction;
	bool movingback = true;
	////

	Slider* timeSlider;
	int percent = 100;
	///
	Label* onGavity;
	Label* onDynamic;
	Label* onDebugDraw;
	Label* onClean;
	///
	vector<Sprite*> allSprite;
	vector<Sprite*> touchedSpritesIndex;
	vector<Vec2> allPoint;
	Vec2 prePoint;
	///
	string missName;
	int maxCombo = 0;
	bool onbreak = false;

	///
	int gameScore = 0;
	Label* scoreView;
	Label* comboView;
	Label* timeView;
	Label* getScoreView;
	///
	struct tm day;
	time_t timer;
	struct tm * timeinfo;
	int remaintime = 60;
	int oldSecond = 0;

	///draw line
	std::vector<Vec2*> * _posaray;
	Vec2* _fingerPos;
};


#endif