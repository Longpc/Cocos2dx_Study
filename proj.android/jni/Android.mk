LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/Ball.cpp \
				   ../../Classes/CustomScroll.cpp \
				   ../../Classes/FlowerMouse.cpp \
				   ../../Classes/GameOverScene.cpp \
				   ../../Classes/HighScoreScene.cpp \
				   ../../Classes/HttpUtils.cpp \
				   ../../Classes/InforLayer.cpp \
				   ../../Classes/JumpGame.cpp \
				   ../../Classes/LoadingLayer.cpp \
				   ../../Classes/ModeSelectScene.cpp \
				   ../../Classes/Monkey.cpp \
				   ../../Classes/MyBodyParser.cpp \
				   ../../Classes/MyWebView.cpp \
				   ../../Classes/ParticleSystem.cpp \
				   ../../Classes/PopLayer.cpp \
				   ../../Classes/PopLayer1.cpp \
				   ../../Classes/SimpleSpriteCreator.cpp \
				   ../../Classes/SpriteSheetScene.cpp \
				   ../../Classes/TestBodyParserScene.cpp \
				   ../../Classes/TestBox2D.cpp \
				   ../../Classes/TestChipmurk.cpp \
				   ../../Classes/TestJoint.cpp \
				   ../../Classes/TestNewGUI.cpp \
				   ../../Classes/ThumbLayer.cpp \
				   ../../Classes/sqlUtils/DataUtils.cpp \
				   ../../Classes/sqlUtils/sqlite3.c \
				   ../../Classes/sqlUtils/SqlUtils.cpp \
				   ../../Classes/base/BaseLayer.cpp \
				   ../../Classes/multitouch/MultiTouchTest.cpp \
				   ../../Classes/JNI/JNICall.cpp \
				   ../../Classes/Mp3Player/MyPlayerScene.cpp \
				   ../../Classes/TestFollow/TestFollow.cpp \
				   ../../Classes/TestFollow/RotateWithVeloc.cpp \
				   ../../Classes/HugeLayer.cpp \
				   ../../Classes/TMXMap/TMXMapScene.cpp \
				   ../../Classes/JNI/JNIAlert.cpp \
				   ../../Classes/GAF/GAFTest.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += gafplayer_static
# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,Cocos2dxGAFPlayer-gaf-4.0/Library)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
