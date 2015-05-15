#include "FlowerMouse.h"


void FlowerMouse::onEnter()
{
	Layer::onEnter();
	string filename = "Particles/"+_filename+".plist";
	_emitter = ParticleSystemQuad::create(filename);
	_emitter->retain();
	_emitter->setEmissionRate(100);
	_emitter->setLife(4);
	_emitter->setDuration(-1);
	addChild(_emitter,10);
	_emitter->setPosition(Vec2(_contentSize.width / 2, _contentSize.height / 2));
}

FlowerMouse* FlowerMouse::create(Size contentSize,string filename)
{
	FlowerMouse *layer = new FlowerMouse();
	if (layer && layer->init(contentSize,filename)) {
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}

bool FlowerMouse::init(Size contentSize,string filename)
{
	if (!Layer::init()) {
		return false;
	}
	this->setContentSize(contentSize);
	_contentSize = contentSize;
	_filename = filename;
	return true;
}
