#include "Client.hpp"
#include <Geode/utils/web.hpp>

void Client::submitAttempt(size_t count) {
	using namespace geode::prelude;
	
	auto APIKey = Mod::get()->getSettingValue<std::string>("API key");
	auto APIUrl = "https://dlvnapi-nampe.koyeb.app";
	std::string urlPath = "/player/heatmap/" + std::to_string(count);
	
	web::AsyncWebRequest()
		.header("Authorization", "Bearer " + APIKey)
		.post(APIUrl + urlPath);
}