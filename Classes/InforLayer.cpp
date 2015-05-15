#ifndef __INFOLAYER_H__
#define __INFOLAYER_H__

#include "InfoLayer.h"
using namespace std;
bool InforLayer::init() {
	if (!Layer::init())
	{
		return false;
	}
	return true;

}

InforLayer::InforLayer() {
	this->setTag(TAG_INFOLAYER);
	cocos2d::log("On Contructer");
}
InforLayer::~InforLayer() {
	cocos2d::log("On Destructer");
	this->removeAllChildren();
}
#endif