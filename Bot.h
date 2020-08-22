#pragma once
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <string>
#include <Windows.h>
class Bot
{
private:
	static size_t write_data(char* ptr, size_t size, size_t nmemb, std::string* data);
	CURL* curl;
	std::string content;
	CURLcode res;
	std::string apiurl;
	std::string message;
	int chat_id;
	long long message_id;
	std::string username;
	Json::Value Parse();
public:
	Bot(std::string apiurl);
	~Bot();
	void Update();
	void Send(std::string text, int chat_id);
	std::string GetLastMessage();
	std::string GetUsername();
	int GetChatId();
	long long GetMessageId();
};

