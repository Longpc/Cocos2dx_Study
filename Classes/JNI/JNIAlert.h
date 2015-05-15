#ifndef ANDROID_NATIVE_ALERT
#define ANDROID_NATIVE_ALERT

#include "cocos2d.h"

NS_CC_BEGIN

class CC_DLL NativeAlert
{
public:
	enum class ButtonType {
		CANCEL = -1,
		OTHER = 0,
		RETURN
	};

	static void show(std::string title, std::string message, std::string cancelButtonTitle);
	static void showWithCallback(std::string title, std::string message, std::string cancelButtonTitle, std::string returnButtonTitle, std::string otherBUttonTitle, int tag, const std::function<void(int tag, ButtonType type)> &callback);
	static void alertDidDismiss(std::string alertId, int buttonIndex);
};

NS_CC_END
#endif