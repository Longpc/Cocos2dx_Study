#include "HttpUtils.h"

void HttpUtils::postToServer(string svAddress,string username, string password, const ccHttpRequestCallback& callback)
{
	const char *serverURL = svAddress.c_str(); 
	auto httpRequest = new HttpRequest();
	httpRequest->setUrl(serverURL);
	httpRequest->setRequestType(HttpRequest::Type::POST);
	httpRequest->setResponseCallback(callback);
	httpRequest->setTag("login");
	auto text = "name=" + username + "&pass=" + password;
	//cocos2d::log("%s", text);
	const char* buffer = text.c_str();
	cocos2d::log("%s", buffer);
	httpRequest->setRequestData(buffer, strlen(buffer));

	auto client = HttpClient::getInstance();
	client->enableCookies(nullptr);
	client->send(httpRequest);
}

void HttpUtils::postTopData(string svAddress, string name, string score, const ccHttpRequestCallback& callback)
{
	const char *serverURL = svAddress.c_str();
	auto httpRequest = new HttpRequest();
	httpRequest->setUrl(serverURL);
	httpRequest->setRequestType(HttpRequest::Type::POST);
	httpRequest->setResponseCallback(callback);
	httpRequest->setTag("update");
	auto text = "name=" + name + "&score=" + score;
	//cocos2d::log("%s", text);
	const char* buffer = text.c_str();
	cocos2d::log("%s", buffer);
	httpRequest->setRequestData(buffer, strlen(buffer));

	auto client = HttpClient::getInstance();
	client->enableCookies(nullptr);
	client->send(httpRequest);
}

