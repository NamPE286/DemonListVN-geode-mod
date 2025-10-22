#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <atomic>

using namespace geode::prelude;

class RaidSubmitter {
	int levelID = 0;
	float best = 0;
	std::atomic<bool> inEvent{ false };
	EventListener<web::WebTask> getListener, putListener;

	void submit();
public:
	RaidSubmitter();
	~RaidSubmitter();
	RaidSubmitter(int levelID);
	void record(float progress);
};