#ifndef JNI_CALL_H
#define JNI_CALL_H
#include "cocos2d.h"
#include <iostream>
#include <string>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif

USING_NS_CC;
using namespace std;

class JNICall
{
public:
	static void simpleLogJNI();
	static string getWriteablePathJNI();
	static string getMp3FileName(int index);
	static bool isVibrateSupported();
	static void makeVibrate(int duration);
	static void stopVibrate();
	static string testCallStringwithInt(int number);
	static void makeCallWithNumberJNI(const char *string);
	static void checkDeviceInfo();
	static void setVolume(int percent);
	static int getCurentVolumeinPercent();
	static int preLoad();
	static void setScreenOn();
	static void unsetScreenOn();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	static void Java_com_boi_extensions_VolumeObserver_onChange(JNIEnv *env, jobject thiz);
#endif
	
private:

};
#endif


