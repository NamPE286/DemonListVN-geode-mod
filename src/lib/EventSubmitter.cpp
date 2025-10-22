#include "EventSubmitter.hpp"
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include "../common.hpp"

EventSubmitter::EventSubmitter() {}

EventSubmitter::~EventSubmitter() {
	getListener.disable();
	putListener.disable();
}

EventSubmitter::EventSubmitter(int levelID): levelID(levelID) {
	web::WebRequest req = web::WebRequest();
	std::string url = API_URL + "/level/" + std::to_string(levelID) + "/inEvent";
	std::string APIKey = geode::prelude::Mod::get()->getSettingValue<std::string>("API key");

	getListener.bind([this](web::WebTask::Event *e) {
		if (web::WebResponse *res = e->getValue()) {
			inEvent.store(res->ok());
		}
		});

	req.header("Authorization", "Bearer " + APIKey);
	getListener.setFilter(req.get(url));
}

void EventSubmitter::submit() {
	if (!inEvent.load()) {
		return;
	}

	web::WebRequest req = web::WebRequest();
	std::string url = API_URL + "/event/submitLevel/" + std::to_string(levelID) + "?progress=" + std::to_string(best) + "&password=69229623652108781802661011115864";
	std::string APIKey = geode::prelude::Mod::get()->getSettingValue<std::string>("API key");

	req.header("Authorization", "Bearer " + APIKey);
	putListener.setFilter(req.put(url));
}

void EventSubmitter::record(float progress) {
	if (progress <= best) {
		return;
	}

	best = progress;

	submit();
}