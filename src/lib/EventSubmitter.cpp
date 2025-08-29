#include "EventSubmitter.hpp"
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

EventSubmitter::EventSubmitter() {}

EventSubmitter::EventSubmitter(int levelID):
	levelID(levelID), getListener(getListener) {
	web::WebRequest req = web::WebRequest();
	std::string url = "http://localhost:8080/level/" + std::to_string(levelID) + "/inEvent";
	std::string APIKey = geode::prelude::Mod::get()->getSettingValue<std::string>("API key");

	getListener.bind([this](web::WebTask::Event *e) {
		try {
			if (web::WebResponse *res = e->getValue()) {
				this->inEvent.store(res->ok());
				geode::log::info("{}", this->inEvent);
			}
		} catch (...) {
		}
		});

	geode::log::info("Sending request to: {}", url);

	req.header("Authorization", "Bearer " + APIKey);
	getListener.setFilter(req.get(url));
}

void EventSubmitter::submit() {
	if (!inEvent.load()) {
		return;
	}

	web::WebRequest req = web::WebRequest();
	std::string url = "http://localhost:8080/event/submitLevel/" + std::to_string(levelID) + "?progress=" + std::to_string(best);
	std::string APIKey = geode::prelude::Mod::get()->getSettingValue<std::string>("API key");

	geode::log::info("Sending request to: {}", url);

	req.header("Authorization", "Bearer " + APIKey);
	putListener.setFilter(req.put(url));
}

void EventSubmitter::record(int progress) {
	if (progress <= best) {
		return;
	}

	best = progress;
	geode::log::info("New best: {}%. Level: {}", progress, levelID);

	submit();
}