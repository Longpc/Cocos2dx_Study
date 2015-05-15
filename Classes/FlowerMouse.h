#ifndef _FLOWER_MOUSE_H__
#define _FLOWER_MOUSE_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class FlowerMouse :public Layer
{
public:
	/*
	@Size contentSize : value for layer content size;
	@string filename: name of Plist file to create particle effect
	@ Select in: Flower,Comet,debian,Galaxy,LavaFlow,lines,Phoenix,SmallSun,Spiral,ExplodingRing, BurstPipe
	*/
	static FlowerMouse* create(Size contentSize ,string filename);
	virtual bool init(Size contentSize,string filename);
	void onEnter();
private:
	ParticleSystemQuad*    _emitter;
	Size _contentSize;
	string _filename;
};


#endif // !_FLOWER_MOUSE_H__
