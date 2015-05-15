#include "UIDialog.h"


UIDialog* UIDialog::create(string tile, string content, vector<UIDialogButton*> buttons)
{
	auto dialog = new UIDialog();
	dialog->init();
	dialog->view(tile, content, buttons);
	dialog->autorelease();

	return dialog;
}

bool UIDialog::init()
{
	if (!Layer::init()) {
		return false;
	}

	_winSize = Director::getInstance()->getWinSize();
	_uiLayer = Layer::create();
	addChild(_uiLayer);
	return true;
}

void UIDialog::view(string title, string content, vector<UIDialogButton*> buttons)
{
	auto sp = Sprite::create();
	sp->setTextureRect(Rect(0, 0, _winSize.width * 2, _winSize.height * 2));
	sp->setColor(Color3B::BLACK);
	sp->setOpacity(126);
	_uiLayer->addChild(sp);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(UIDialog::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	int size = buttons.size() - 1;
	if (title != "") size++;
	if (content != "") size++;

	float mergin = 150;
	float height = mergin*size / 2;

	Vector<MenuItem*> item;

	if (title != ""){
		auto* titleLabel = Label::createWithSystemFont(title, "Arial", 28, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
		titleLabel->setPosition(Point(_winSize.width / 2, _winSize.height / 2 + height));
		_uiLayer->addChild(titleLabel);
		height -= mergin;
	}

	if (content != ""){
		auto* contentLabel = Label::createWithSystemFont(content, "Arial", 28, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
		contentLabel->setPosition(Point(_winSize.width / 2, _winSize.height / 2 + height));
		_uiLayer->addChild(contentLabel);
		height -= mergin;
	}

	int tag = 1;
	for (auto b : buttons){
		auto* labelBtnLabel = Label::createWithSystemFont(b->name(), "Arial", 48);
		auto* itemLabel = MenuItemLabel::create(labelBtnLabel, b->action());

		itemLabel->setPosition(Vec2(0.0f, height));
		if (b->tag() != 1) tag = b->tag(); 
		itemLabel->setTag(tag);
		item.pushBack(itemLabel);
		height -= mergin;
		tag++; 
	}
	auto* menu = Menu::createWithArray(item);
	_uiLayer->addChild(menu);

}

void UIDialog::close()
{
	Action *action = RemoveSelf::create();
	runAction(action);
}

bool UIDialog::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

