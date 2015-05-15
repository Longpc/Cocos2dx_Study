#ifndef _TESTNEWUI_H__
#define _TESTNEWUI_H__


#include <string.h>
#include "ui\CocosGUI.h"
#include "extensions\cocos-ext.h"
#include "cocos2d.h"
#include "network\HttpClient.h"
#include "spine\Json.h"

#include "sqlUtils\DataUtils.h"
#include "LoadingLayer.h"
#include "HttpUtils.h"
#include "JNI\JNICall.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
using namespace ui;
using namespace cocos2d::network;

class TestNewGUI : public Layer ,public TextFieldDelegate
{
public:

	static Scene* createScene();
	//static TestNewGUI* create();
	CREATE_FUNC(TestNewGUI);
	virtual bool init();
	void update(float dt) override;
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void touchEvent(Ref *pSender, Widget::TouchEventType type);
	virtual void sliderEvent(Ref *pSender, Slider::EventType type);
	virtual void touchButton2(Ref* pSender, Widget::TouchEventType type);
	virtual void sendRequest();
	virtual void callback(HttpClient* client, HttpResponse* response);
	virtual void clickLogin(Ref *pSender, Widget::TouchEventType type);
	virtual void clickCancel(Ref *pSender, Widget::TouchEventType type);
	virtual void checkInputedValues(int offset);
	/*
	@
	*/
	virtual void authWithServer(string user, string pass);
	virtual void authenCallback(HttpClient* client, HttpResponse* response);
	virtual void sigupWithServer(string username, string password);
	// TextFieldDelegate
	virtual bool onTextFieldAttachWithIME(TextFieldTTF * sender);
	virtual bool onTextFieldDetachWithIME(TextFieldTTF * sender);
	virtual bool onTextFieldInsertText(TextFieldTTF * sender, const char * text, size_t nLen) override;
	virtual bool onTextFieldDeleteBackward(TextFieldTTF * sender, const char * delText, size_t nLen) override;
	virtual bool onDraw(TextFieldTTF * sender);
	virtual void endTextAction(Node *node);
	virtual void textFieldEvent(Ref *pSener, TextField::EventType type);

private:
	Size screenSize;
	Slider* slider;
	Button* testButton;
	Button* button2;
	Text *textView;
	extension::ScrollView* scroll;
	Layer *layer;
	Point touch;
	TextField *formLabel;
	Text *actionInfo;
	ui::EditBox *userInput;
	ui::EditBox *passwordInput;
	Button *submitButton;
	Button *cancelButton;

	TextFieldTTF * _textField;
	Action * _textFieldAction;
	bool _action;
	int _charLimit = 1000;

};


#endif
