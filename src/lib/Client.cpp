#include "Client.hpp"
#include "../utils/utils.hpp"
#include <Geode/Geode.hpp>

void Client::submitAttempt(size_t count) {
	utils::extractUID("this is api key");
	geode::prelude::log::info("{}", count);
}