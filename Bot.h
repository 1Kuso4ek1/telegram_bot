#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

#include <curl/curl.h>
#include <json/json.h>
class Bot
{
public:
	Bot(std::string apiurl);
	~Bot();
	void Update();
	void Send(std::string text, int chat_id);
	std::string GetLastMessage();
	std::string GetUsername();
	int GetChatId();
	long long GetMessageId();
private:
	static size_t write_data(char* ptr, size_t size, size_t nmemb, std::string* data);
	Json::Value Parse();

	Json::CharReaderBuilder builder;
	Json::Value root;
	JSONCPP_STRING err;
	
	CURL* curl;
	CURLcode res;
	
	std::string content;
	std::string apiurl;
	std::string message;
	std::string username;
	
	int chat_id;
	long long message_id;
};

