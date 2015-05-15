#ifndef ___HIGHSCORE__
#define ___HIGHSCORE__


#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui\CocosGUI.h"
#include "network\HttpClient.h"

#include "Define.h"
#include "PopLayer1.h"
#include "GameOverScene.h"
#include "SpriteSheetScene.h"
#include "ModeSelectScene.h"
#include "spine/Json.h"
#include "sqlUtils/DataUtils.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
using namespace cocos2d::network;
using namespace cocos2d::extension;
class HighScore : public Layer
{
public:
	static Scene* createScene();
	//static HighScore* create(const Color4B& color);
	//virtual bool initWithColor(const Color4B& color);
	CREATE_FUNC(HighScore);
	virtual bool init();

	virtual void clickBackListener(Ref *pSender, Widget::TouchEventType type);
	virtual void retryClickListener(Ref *pSender, Widget::TouchEventType type);
	virtual void onEnterTransitionDidFinish();
	virtual void httpRequest();
	virtual void callback(HttpClient* sender, HttpResponse* response);
	virtual void topCallback(HttpClient* sender, HttpResponse* response);
	virtual void setNewTopValue(string name, int score);
	virtual void displayLocalData();
private:
	Text* topNameView;
	Text* topScoreView;
};



#endif