#include "AttemptCounter.hpp"
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

void AttemptCounter::add() {
	cnt++;
}

void AttemptCounter::submit(geode::prelude::EventListener<geode::prelude::web::WebTask>* m_listener) {
	using namespace geode::prelude;

	auto APIKey = Mod::get()->getSettingValue<std::string>("API key");
	const std::string APIUrl = "https://api.demonlistvn.com";
	std::string urlPath = "/player/heatmap/" + std::to_string(cnt);

	web::WebRequest req = web::WebRequest();
	req.header("Authorization", "Bearer " + APIKey);
	m_listener->setFilter(req.post(APIUrl + urlPath));
}