#include "JNIAlert.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif

#define CLASS_NAME "com/boi/extensions/AndroidNativeAlert"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C" {
	JNIEXPORT void JNICALL Java_com_boi_extensions_AndroidNativeAlert_alertDidDismiss(JNIEnv *env, jclass, jstring jid, jint jindex) {
		auto charID = env->GetStringUTFChars(jid, NULL);
		std::string alertID = charID;
		env->ReleaseStringUTFChars(jid, charID);
		cocos2d::NativeAlert::alertDidDismiss(alertID, jindex);
	}
}
#endif

NS_CC_BEGIN

static std::unordered_map<std::string, std::pair<int, std::function<void(int tag, cocos2d::NativeAlert::ButtonType type)>>> s_AlertViewIDs;

void cocos2d::NativeAlert::show(std::string title, std::string message, std::string cancelButtonTitle)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	NativeAlert::showWithCallback(title,message,cancelButtonTitle,"","",0,nullptr);
#endif
}

void cocos2d::NativeAlert::showWithCallback(std::string title, std::string message, std::string cancelButtonTitle, std::string returnButtonTitle, std::string otherBUttonTitle, int tag, const std::function<void(int tag, ButtonType type)> &callback)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	std::string alertID("");

	if (!JniHelper::getStaticMethodInfo(t,CLASS_NAME,"showNativeAlert","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;")) {
		return;
	}

	jstring jTitle = t.env->NewStringUTF(title.c_str());
	jstring jMsg = t.env->NewStringUTF(message.c_str());
	jstring jCanBtn = t.env->NewStringUTF(cancelButtonTitle.c_str());
	jstring jRetBtn = t.env->NewStringUTF(returnButtonTitle.c_str());
	jstring jOthBtn = t.env->NewStringUTF(otherBUttonTitle.c_str());
	jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, jTitle, jMsg, jCanBtn, jRetBtn, jOthBtn);
	t.env->DeleteLocalRef(t.classID);
	alertID = JniHelper::jstring2string(str);
	t.env->DeleteLocalRef(str);

	if (callback) {
		std::pair<int, std::function<void(int tag, ButtonType type)>> tnf(tag, callback);
		s_AlertViewIDs[alertID] = tnf;
	}
#endif
}

void cocos2d::NativeAlert::alertDidDismiss(std::string alertId, int buttonIndex)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	std::pair<int, std::function<void(int tag, ButtonType type)>> pair1;
	try
	{
		pair1 = s_AlertViewIDs.at(alertId);
	}
	catch (const std::out_of_range& e)
	{
		return;
	}
	ButtonType type = ButtonType::OTHER;
	if (buttonIndex == -1) {
		type = ButtonType::RETURN;
	}
	else if (buttonIndex == -2)
	{
		type = ButtonType::CANCEL;
	}
	pair1.second(pair1.first, type);
	s_AlertViewIDs.erase(alertId);
#endif
}
NS_CC_END