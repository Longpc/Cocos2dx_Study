#ifndef _DOWNLINE__H__
#define _DRAWLINE__H__

#include "cocos2d.h"

USING_NS_CC;

class DrawLine :public DrawNode
{
public:
	DrawLine(std::vector<Vec2*>*);
	static DrawLine* create(std::vector<Vec2*>*);
	virtual bool init();
	void remove();
	~DrawLine();
protected:
	DrawNode* _node;
	std::vector<Vec2*>* _vecs;
private:

};




#endif