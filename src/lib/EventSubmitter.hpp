#pragma once

class EventSubmitter {
	int best = 0;

	void submit();
public:
	EventSubmitter();
	void record(int progress);
};