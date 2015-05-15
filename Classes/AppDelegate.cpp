#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

typedef struct tagResource {
	cocos2d::Size size;
	char directory[100];
}Resource;
//PHONE PORTRAIN
static Resource smallSize1 = { cocos2d::Size(640, 960), "2.2 inch small" };
static Resource mediumSize1 = { cocos2d::Size(1080, 1920), "5inch medium" };
static cocos2d::Size designResolution1 = cocos2d::Size(640, 960);

//ON WINDOW
static Resource smallSize2 = { cocos2d::Size(480, 720), "2.2 inch small" };
static Resource mediumSize2 = { cocos2d::Size(640, 960), "5inch medium" };
static cocos2d::Size designResolution2 = cocos2d::Size(640, 960);
Resource smallSize;
Resource mediumSize;
cocos2d::Size designResolution;

void AppDelegate::initGLContextAttrs() {
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) {
		smallSize = smallSize2;
		mediumSize = mediumSize2;
		designResolution = designResolution2;
		glview->setFrameSize(designResolution.width, designResolution.height);
	}
	else {
		smallSize = smallSize1;
		mediumSize = mediumSize1;
		designResolution = designResolution1;
	}
	
	glview->setDesignResolutionSize(designResolution.width, designResolution.height,ResolutionPolicy::EXACT_FIT);
	Size frameSize = director->getVisibleSize();
	Size winSize = director->getWinSize();
	cocos2d::log("Visibale Size: Width: %d, Height: %d", int(frameSize.width), int(frameSize.height));
	cocos2d::log("WIn Size: Width: %d, Height: %d", int(winSize.width), int(winSize.height));
	frameSize = glview->getVisibleSize();
	if (frameSize.height > smallSize.size.height)
	{
		director->setContentScaleFactor(mediumSize.size.height / designResolution.height);
	}
	// if the frame's height is larger than the height of small resource size, select medium resource.
	else
	{
		director->setContentScaleFactor(smallSize.size.height / designResolution.height);
	}
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	auto scDirector = Director::getInstance();
	//scDirector->set

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
	auto scene = GameOverScene::createScene(-1);
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
