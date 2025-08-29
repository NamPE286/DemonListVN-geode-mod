#pragma once

class EventSubmitter {
	int best = 0;
	bool inEvent = false;

	void submit();
public:
	EventSubmitter(int levelID);
	void record(int progress);
};