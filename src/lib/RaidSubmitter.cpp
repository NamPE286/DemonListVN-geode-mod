#include "RaidSubmitter.hpp"
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include "../common.hpp"

RaidSubmitter::RaidSubmitter() {}

RaidSubmitter::~RaidSubmitter() {
	getListener.disable();
	putListener.disable();
}

RaidSubmitter::RaidSubmitter(int levelID): levelID(levelID) {
	web::WebRequest req = web::WebRequest();
	std::string url = API_URL + "/level/" + std::to_string(levelID) + "/inEvent?type=raid";
	std::string APIKey = geode::prelude::Mod::get()->getSettingValue<std::string>("API key");

	getListener.bind([this](web::WebTask::Event *e) {
		if (web::WebResponse *res = e->getValue()) {
			inEvent.store(res->ok());
		}
		});

	req.header("Authorization", "Bearer " + APIKey);
	getListener.setFilter(req.get(url));
}

void RaidSubmitter::submit() {
	if (!inEvent.load()) {
		return;
	}

	web::WebRequest req = web::WebRequest();
	std::string url = API_URL + "/event/submitLevel/" + std::to_string(levelID) + "?progress=" + std::to_string(best) + "&password=" + EVENT_PASSWORD;
	std::string APIKey = geode::prelude::Mod::get()->getSettingValue<std::string>("API key");

	req.header("Authorization", "Bearer " + APIKey);
	putListener.setFilter(req.put(url));
}

void RaidSubmitter::record(float progress) {
	best = progress;

	submit();
}