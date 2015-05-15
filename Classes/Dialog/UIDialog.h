#ifndef CUSTOM_DIALOG_H__
#define CUSTOM_DIALOG_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace std;
USING_NS_CC_EXT;
using namespace ui;

struct UIDialogButton
{
private:
	string _name;
	std::function<void(Ref*)> &_action; //ccMenuCallback
	int _tag;
public:
	UIDialogButton(string name, std::function<void(Ref*)> &action, int tag = 1) :_name(name), _action(action), _tag(tag){}
	
	string name() const { return _name; }
	std::function<void(Ref*)> action() const { return _action; }
	int tag() const { return _tag; }

};

class UIDialog :public Layer
{
public:
	static UIDialog* create(string tile, string content, vector<UIDialogButton*> buttons);
	virtual bool init();
	virtual void view(string title, string content, vector<UIDialogButton*> buttons);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	void close();

protected:
	Layer* _uiLayer;
	Size _winSize;
};



#endif


