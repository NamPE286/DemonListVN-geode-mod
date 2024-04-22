#include "AttemptCounter.hpp"
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

void AttemptCounter::add() {
	cnt++;
}

void AttemptCounter::submit() {
	using namespace geode::prelude;

	auto APIKey = Mod::get()->getSettingValue<std::string>("API key");
	const std::string APIUrl = "https://dlvnapi-nampe.koyeb.app";
	std::string urlPath = "/player/heatmap/" + std::to_string(cnt);

	web::AsyncWebRequest()
		.header("Authorization", "Bearer " + APIKey)
		.post(APIUrl + urlPath);
}