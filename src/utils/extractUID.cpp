#include "utils.hpp"
#include <Geode/Geode.hpp>

std::string utils::extractUID(std::string key) {
	geode::prelude::log::info("{}", key);
	return key;
}