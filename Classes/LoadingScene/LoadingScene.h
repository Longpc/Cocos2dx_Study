#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class AsyncImageLoader;
class AsyncAtlasLoader;

class LoadingScene : public Layer
{
protected:
    AsyncImageLoader *asyncImageLoader;
    AsyncAtlasLoader *asyncAtlasLoader;
    
public:
    void onEnter(void)
    {
        Layer::onEnter();
        //....
	
        this->runAction(CallFunc::create(this, callfunc_selector(LoadingScene::startLoading)));
    }

protected:
    void startLoading(void)
    {
        this->prepareLists();
        this->startImageLoading();
    }
    
    void endLoading(void)
    {
    }
    
    void prepareLists(void)
    {
        this->prepareImageList();
        this->prepareAtlasList();
    }
    
    void prepareImageList(void)
    {
        vector<Object*> imageList;
     
        auto arr = Array::createWithContentsOfFile("ListOfImages.plist");
        Object *obj;
        CCARRAY_FOREACH(arr, obj)
            imageList.push_back(static_cast(obj)->m_sString);
         
        this->asyncImageLoader = new AsyncImageLoader(imageList, this,
            callfuncI_selector(LoadingScene::onImageLoaded), callfuncB_selector(LoadingScene::onImageLoadingFinished));
    }
    
    void prepareAtlasList(void)
    {
        vector<Object*> atlasList;
     
        auto arr = CCArray::createWithContentsOfFile("ListOfAtlases.plist");
        CCObject *obj;
        CCARRAY_FOREACH(arr, obj)
            atlasList.push_back(static_cast(obj)->m_sString);
         
        this->asyncAtlasLoader = new AsyncAtlasLoader(atlasList, this,
            callfunc_selector(LoadingScene::onAtlasLoaded), callfunc_selector(LoadingScene::onAtlasLoadingFinished));
    }
    
    void updateProgress(void)
    {
    }
    
    void startImageLoading(void)
    {
        this->asyncImageLoader->start();
    }
    
    void onImageLoaded(int index)
    {
        this->updateProgress();
    }
    
    void onImageLoadingFinished(bool successful)
    {
        if (!successful)
        {
	    // show error
            return;
        }
         
        this->startAtlasLoading();
    }
    
    void startAtlasLoading(void)
    {
        this->asyncAtlasLoader->start();
    }
    
    void onAtlasLoaded(void)
    {
        this->updateProgress();
    }
    
    void onAtlasLoadingFinished(void)
    {
        this->endLoading();
    }
};
