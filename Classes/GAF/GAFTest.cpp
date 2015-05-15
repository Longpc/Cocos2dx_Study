#include "GAFTest.h"
Scene* GAFTest::createScene()
{
	auto scene = Scene::create();
	auto layer = GAFTest::create();

	scene->addChild(layer);
	return scene;
}

void GAFTest::restartCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5, GAFTest::createScene()));
}

void GAFTest::exitCallback(Ref *pSender)
{
	Director::getInstance()->replaceScene(GameOverScene::createScene(-1));
}

void GAFTest::debugCallback(Ref *pSender)
{

}

void GAFTest::nextCallback(Ref *pSender)
{

}

bool GAFTest::init()
{
	if (!BaseLayer::init()) {
		return false;
	}

	return true;
}

void GAFTest::onEnter()
{
	BaseLayer::onEnter();
	scheduleUpdate();
	gaf::GAFAsset *asset = gaf::GAFAsset::create("GAF/getItemAnimationEffect/getItemAnimationEffect.gaf",nullptr);
	obj = asset->createObject();


	obj->setPosition(Vec2(0, _visibleSize.height));
	obj->setLooped(true);
	obj->start();
	obj->setSequenceDelegate(CC_CALLBACK_2(GAFTest::onFinishSequence,this));
	obj->setFramePlayedDelegate(CC_CALLBACK_2(GAFTest::onFramPlayed, this));
	obj->setAnimationFinishedPlayDelegate(CC_CALLBACK_1(GAFTest::animationFInishDelegate, this));
	obj->setAnimationStartedNextLoopDelegate(CC_CALLBACK_1(GAFTest::animationStartedNextLoop, this));
	obj->setTag(1);
	uint32_t endF = obj->getTotalFrameCount();
	log("Total Frame: %d", endF);
	addChild(obj);

}

void GAFTest::update(float delta)
{

}

void GAFTest::onFinishSequence(gaf::GAFObject *object, string sequenceName)
{
	log("Sequence Finished");
}

void GAFTest::onFramPlayed(GAFObject *object, uint32_t frame)
{
	log("%d", frame);
}

void GAFTest::animationFInishDelegate(GAFObject *object)
{
	log("Animation Finish");
	object->stop();
}

void GAFTest::animationStartedNextLoop(GAFObject *object)
{
	log("Next loop");
	countLoop++;
	if (countLoop >= 5) {
		object->stop();
	}
}

