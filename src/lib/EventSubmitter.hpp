#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <atomic>

using namespace geode::prelude;

class EventSubmitter {
	int levelID = 0;
	float best = 0;
	std::atomic<bool> inEvent{ false };
	EventListener<web::WebTask> getListener, putListener;

	void submit();
public:
	EventSubmitter();
	~EventSubmitter();
	EventSubmitter(int levelID);
	void record(float progress);
};