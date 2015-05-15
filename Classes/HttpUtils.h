#ifndef _HTTP_UTILS_H__
#define _HTTP_UTILS_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::network;
using namespace std;
class HttpUtils
{
public:
	/*
	
	*/
	static void postToServer(string svAddress,string username, string password,const ccHttpRequestCallback& callback);
	/*
	*/
	static float stringToFloat(const string str);
	/*

	*/
	static void postTopData(string svAddress, string name, string score, const ccHttpRequestCallback& callback);

};

#endif