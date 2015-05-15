#include "JNICall.h"

#define CLASS_NAME "com/boi/extensions/MyExtensionActivity"
#define COCOS_HELPER "org/cocos2dx/lib/Cocos2dxHelper"
void JNICall::simpleLogJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	if (!JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "logJNI", "()V")) {
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
#endif
}

string JNICall::getWriteablePathJNI()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "getPath", "()Ljava/lang/String;");

	jstring jpath = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);

	const char* npath = methodInfo.env->GetStringUTFChars(jpath, NULL);

	string str = npath;
	methodInfo.env->ReleaseStringUTFChars(jpath, npath);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
	cocos2d::log("path in Phone is: %s", str.c_str());
	return str.c_str();
#endif
	return "";
}

string JNICall::testCallStringwithInt(int number)
{

	return "";
}

void JNICall::makeCallWithNumberJNI(const char *string)
{
	cocos2d::log("%s: ",string);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	JniMethodInfo methodInfo;
	if (!JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "callPhone", "(Ljava/lang/String;)V")) {
		return;
	}
	jstring tStringArg1 = methodInfo.env->NewStringUTF(string);
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, tStringArg1);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
#endif
}
bool JNICall::isVibrateSupported() {
	bool ret = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "isVibrateSupported", "()Z")) {
		ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}

#endif
	return ret;
}
void JNICall::makeVibrate(int duration)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	if (!JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "makeVibrate", "(I)V")) {
		return;
	}
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID,duration);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
#endif
}

void JNICall::stopVibrate() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "stopVibrate", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
#endif
}

void JNICall::checkDeviceInfo()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo mi;
	if (!JniHelper::getStaticMethodInfo(mi, CLASS_NAME, "checkDevice", "()V")) {
		return;
	}
	mi.env->CallStaticVoidMethod(mi.classID, mi.methodID);
	mi.env->DeleteLocalRef(mi.classID);
#endif
}

void JNICall::setVolume(int percent= 0)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	if (!JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "setVolume", "(I)V")) {
		return;
	}
	if(percent < 0) {
		percent = 0;
	}
	if (percent > 100)
	{
		percent = 100;
	}
	cocos2d::log("Percent on JNICall: %d",percent);
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, percent);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
#endif
}
int JNICall::getCurentVolumeinPercent()
{
	int volume = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo method;
	if (!JniHelper::getStaticMethodInfo(method,CLASS_NAME,"getVolume","()I")) {
		return volume;
	}
	volume = method.env->CallStaticIntMethod(method.classID,method.methodID);
	method.env->DeleteLocalRef(method.classID);
#endif
	return volume;
}
string JNICall::getMp3FileName(int index)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	if (!JniHelper::getStaticMethodInfo(methodInfo, CLASS_NAME, "getFileNameAtIndex", "(I)Ljava/lang/String;")) {
		return "";
	}
	jstring jpath = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID,index);

	const char* npath = methodInfo.env->GetStringUTFChars(jpath, NULL);

	string str = npath;
	methodInfo.env->ReleaseStringUTFChars(jpath, npath);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
	cocos2d::log("Mp3 name: %s", str.c_str());
	return str.c_str();
#endif
	return "";
}
int JNICall::preLoad()
{
	int i = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo method;
	if (!JniHelper::getStaticMethodInfo(method, CLASS_NAME, "preLoad", "(Ljava/lang/String;)I")) {
		return 0;
	}
	string a = "/Music/Music/";
	jstring jmsg = method.env->NewStringUTF(a.c_str());
	i = method.env->CallStaticIntMethod(method.classID,method.methodID,jmsg);
	method.env->DeleteLocalRef(method.classID);
#endif
	log("Call PreLoad %d", i);
	return i;
}
void JNICall::setScreenOn()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo method;
	if (!JniHelper::getStaticMethodInfo(method, CLASS_NAME, "setScreenStayOn", "()V")) {
		return;
	}
	method.env->CallStaticVoidMethod(method.classID, method.methodID);
	method.env->DeleteLocalRef(method.classID);
#endif

}

void JNICall::unsetScreenOn()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo method;
	if (!JniHelper::getStaticMethodInfo(method, CLASS_NAME, "unsetScreenStayOn", "()V")) {
		return;
	}
	method.env->CallStaticVoidMethod(method.classID, method.methodID);
	method.env->DeleteLocalRef(method.classID);
#endif
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
void JNICall::Java_com_boi_extensions_VolumeObserver_onChange(JNIEnv *env, jobject thiz)
{
	cocos2d::log("this is code in C++");
}







#endif
