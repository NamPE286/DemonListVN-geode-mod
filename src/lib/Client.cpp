#include "Client.hpp"
#include <Geode/utils/web.hpp>

void Client::submitAttempt(size_t count) {
	using namespace geode::prelude;
	
	auto APIKey = Mod::get()->getSettingValue<std::string>("API key");
	auto APIUrl = Mod::get()->getSettingValue<std::string>("API url");
	std::string url = APIUrl + std::string("/player/heatmap/") + std::to_string(count);
	std::string curlCmd = "curl.exe -X POST \"" + url + "\" --header \"Authorization: Bearer " + APIKey + "\"";
	log::info("{}", APIKey);
	log::info("{}", curlCmd);
	log::info("{}", "Sending data to " + url);
	system(curlCmd.c_str());
}