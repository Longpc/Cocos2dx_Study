#ifndef _TEST_CHIPMURK_H__
#define _TEST_CHIPMURK_H__

#include "cocos2d.h"
#include "Define.h"
#include "ui\CocosGUI.h"
#include "extensions\cocos-ext.h"
#include <math.h>
#include "GameOverScene.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
using namespace ui;


const PhysicsMaterial MY_MASTERIAL(1.0f,0.9f,1.0f);

class TestChipmurk : public  Layer
{
public:
	///Variables
	PhysicsWorld* _myWorld;
	PhysicsBody* _ballBody;
	PhysicsBody* _ballBodyNoGavity;
	Sprite*_ball;
	Sprite* _box;
	Sprite* _arraw;
	Size winSize;
	Size ordinSize;
	Button* debugButton;

	Vec2 beginPoint;
	Vec2 endPoint;
	
	bool onBegin = false;
	bool canTouch = true;

	float backGroundScaleRatio;
	int _gameScore  = 0;
	vector<Sprite*> _allBox;

	//Functions
	static Scene* createScene();
	static TestChipmurk* create();
	bool init();
	void onEnterTransitionDidFinish();
	void update(float);

	void setPhysicWorld(PhysicsWorld* world) {
		_myWorld = world;
	}

	bool onContactBegin(const PhysicsContact &contact);
	void destroyBallBody(PhysicsBody*);


	virtual bool onTouchBegan(Touch*, Event*);
	virtual void onTouchMoved(Touch*, Event*);
	virtual void onTouchEnded(Touch*, Event*);

	virtual void drawDebug(Ref *pSender, Widget::TouchEventType type);
	virtual void checkDrawDebug();
	virtual void clickBack(Ref *pSender, Widget::TouchEventType type);
	virtual void afterTensecond();
	virtual void touchCameraButton(Ref *pSender, Widget::TouchEventType type);
private:
	Slider* strengthSlider;
	bool onCamera = false;
	Button *cameraButton;

	
};


#endif