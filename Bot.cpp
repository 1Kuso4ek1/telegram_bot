#include "Bot.h"

size_t Bot::write_data(char* ptr, size_t size, size_t nmemb, std::string* data)
{
	if (data) {
		data->append(ptr, size * nmemb);
		return size * nmemb;
	}
	else {
		return 0;
	}
}
Json::Value Bot::Parse()
{
	Json::CharReaderBuilder builder;
	Json::Value root;
	JSONCPP_STRING err;
	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(content.c_str(), content.c_str() + content.size(), &root, &err)) {
		std::cout << "error" << std::endl;
	}
	return root;
}
Bot::Bot(std::string apiurl) : apiurl(apiurl)
{
	curl = curl_easy_init();
	curl_global_init(CURL_GLOBAL_DEFAULT);
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, TRUE);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &content);
	}
}

Bot::~Bot()
{
	curl_easy_cleanup(curl);
}

void Bot::Update()
{
	curl_easy_setopt(curl, CURLOPT_URL, (apiurl + "getUpdates").c_str());
	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		std::cout << "Error!" << std::endl;
		std::cout << curl_easy_strerror(res) << std::endl;
	}
	Json::Value root = Parse();
	message_id = root["result"][root["result"].size() - 1]["message"]["message_id"].asInt64();
	message = root["result"][root["result"].size() - 1]["message"]["text"].asString();
	chat_id = root["result"][root["result"].size() - 1]["message"]["from"]["id"].asInt64();
}

void Bot::Send(std::string text, int chat_id)
{
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, (apiurl + "sendMessage?chat_id=" + std::to_string(chat_id) + "&text=" + text).c_str());
	}
	res = curl_easy_perform(curl);
	if (res != CURLE_OK) {
		std::cout << "Error!" << std::endl;
		std::cout << curl_easy_strerror(res) << std::endl;
	}
}

std::string Bot::GetLastMessage()
{
	return message;
}

std::string Bot::GetUsername()
{
	return username;
}

int Bot::GetChatId()
{
	return chat_id;
}

long long Bot::GetMessageId()
{
	return message_id;
}
