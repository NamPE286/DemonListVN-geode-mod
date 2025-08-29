#include "EventSubmitter.hpp"
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>

EventSubmitter::EventSubmitter() {}

EventSubmitter::EventSubmitter(int levelID):
	levelID(levelID), getListener(getListener) {
	web::WebRequest req = web::WebRequest();
	std::string url = "https://api.demonlistvn.com/level/" + std::to_string(levelID) + "/inEvent";
	std::string APIKey = geode::prelude::Mod::get()->getSettingValue<std::string>("API key");

	getListener.bind([this](web::WebTask::Event *e) {
		try {
			if (web::WebResponse *res = e->getValue()) {
				this->inEvent.store(res->ok());
			}
		} catch (...) {
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
	std::string url = "https://api.demonlistvn.com/event/submitLevel/" + std::to_string(levelID) + "?progress=" + std::to_string(best);
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