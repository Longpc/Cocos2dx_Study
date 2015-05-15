#ifndef TMX_MAP_SCENE
#define TMX_MAP_SCENE
#include "base/BaseLayer.h"
#include "../GameOverScene.h"
#include "JNI/JNIAlert.h"
#include "ui/CocosGUI.h"
class TMXMapScene :public BaseLayer
{
public:
	static Scene* createScene();
	static void doSomethingHere();
	CREATE_FUNC(TMXMapScene);
	bool init();
	virtual void setPhysicWorld(PhysicsWorld* world);
	virtual void update(float dt);

	virtual void restartCallback(Ref *pSender);
	virtual void exitCallback(Ref *pSender);
	virtual void debugCallback(Ref *pSender);
	virtual void nextCallback(Ref *pSender);
	virtual void onEnter();


private:
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);
	
	void onNativeCallback(int tag, NativeAlert::ButtonType type);

	void setViewPointCenter(Vec2 centerPos);
	void setPlayerPosition(Vec2 pos);
	Vec2 titleCoordForPosition(Vec2 location);

	virtual void addEnemyWithPos(Vec2 pos);

	PhysicsWorld *_myWorld;
	TMXTiledMap *_myMap;
	TMXLayer *_myLayer;
	TMXLayer *_blockLayer;
	TMXLayer *_collectLayer;

	Sprite *_myPlayer;
	int _itemNum = 0;

	vector<Sprite*> _allEnemies;

};

class MenuLayer :public BaseLayer
{
public:
	CREATE_FUNC(MenuLayer);
	virtual bool init();
	virtual void restartCallback(Ref *pSender);
	virtual void exitCallback(Ref *pSender);
	virtual void debugCallback(Ref *pSender);
	virtual void nextCallback(Ref *pSender);
	void addPhysicWorld(PhysicsWorld *world);

	PhysicsWorld *pWorld;
	Label *label;


	static void numCollectedChanged(int num);
};


#endif


