#include "EventSubmitter.hpp"

EventSubmitter::EventSubmitter(int levelID) {
	// TODO: Check if level is in an active event
}

void EventSubmitter::submit() {
	// TODO: Submit to event
}

void EventSubmitter::record(int progress) {
	if (progress <= best) {
		return;
	}

	best = progress;

	if (inEvent) {
		submit();
	}
}