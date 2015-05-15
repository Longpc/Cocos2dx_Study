#ifndef GAF_TEST_SCENE
#define GAF_TEST_SCENE
#include "cocos2d.h"
#include "external/Cocos2dxGAFPlayer-gaf-4.0/Library/Sources/GAF.h"
#include "external/Cocos2dxGAFPlayer-gaf-4.0/Library/Sources/GAFObject.h"
#include "external/Cocos2dxGAFPlayer-gaf-4.0/Library/Sources/GAFAsset.h"
#include "../base/BaseLayer.h"
#include "../GameOverScene.h"
USING_NS_GAF;
class GAFTest :public BaseLayer
{
public:
	static Scene* createScene();
	CREATE_FUNC(GAFTest);
	virtual void restartCallback(Ref *pSender);
	virtual void exitCallback(Ref *pSender);
	virtual void debugCallback(Ref *pSender);
	virtual void nextCallback(Ref *pSender);

	bool init();
	virtual void onEnter();
	virtual void update(float delta);
	virtual void onFinishSequence(gaf::GAFObject *object, string sequenceName);
	virtual void onFramPlayed(GAFObject *object, uint32_t frame);
	virtual void animationFInishDelegate(GAFObject *object);
	virtual void animationStartedNextLoop(GAFObject *object);



private:
	gaf::GAFObject *obj;
	int countLoop = 0;
};

#endif