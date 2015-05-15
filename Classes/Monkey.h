#ifndef _MONKEY_H
#define _MONKEY_H

#include "cocos2d.h"

USING_NS_CC;

class Monkey : public Sprite
{
public:
	Monkey(void);
	virtual ~Monkey(void);
	virtual void onEnter() override;

	static Monkey* create();

};

#endif
