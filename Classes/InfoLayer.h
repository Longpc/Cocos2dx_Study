#ifndef __INFO_LAYER_H__
#define __INFO_LAYER_H__
#include "cocos2d.h"
#include "Define.h"
USING_NS_CC;
using namespace std;
class InforLayer : public cocos2d::Layer
{
public:
	InforLayer();
	~InforLayer();
	virtual bool init();
	CREATE_FUNC(InforLayer);
private:
	Size visibleSize;
};


#endif