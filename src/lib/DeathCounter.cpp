#include "DeathCounter.hpp"
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

DeathCounter::DeathCounter() {}

DeathCounter::DeathCounter(int id, bool completed) {
	deathData = DeathData(id, completed, {});
}

void DeathCounter::add(int percent) {
	deathData.addDeathCount(percent);
}

void DeathCounter::submit() {
	if (deathData.completed) {
		return;
	}

	using namespace geode::prelude;

	auto APIKey = geode::prelude::Mod::get()->getSettingValue<std::string>("API key");
	const std::string APIUrl = "https://dlvnapi-nampe.koyeb.app";
	std::string urlPath = "/deathCount/" + std::to_string(deathData.levelID) + "/" + deathData.serialize();

	web::AsyncWebRequest()
		.header("Authorization", "Bearer " + APIKey)
		.post(APIUrl + urlPath);
}