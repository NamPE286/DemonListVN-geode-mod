#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <atomic>

using namespace geode::prelude;

class EventSubmitter {
	int levelID = 0, best = 0;
	std::atomic<bool> inEvent{ false };
	EventListener<web::WebTask> getListener, putListener;

	void submit();
public:
	EventSubmitter();
	EventSubmitter(int levelID);
	void record(int progress);
};