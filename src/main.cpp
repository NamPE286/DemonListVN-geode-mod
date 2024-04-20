#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "lib/Client.hpp"

using namespace geode::prelude;

class $modify(DTPlayLayer, PlayLayer) {
	size_t attemptCount = 0;
	bool hasRespawned = false;

	bool init(GJGameLevel * level, bool p1, bool p2) {
		if (!PlayLayer::init(level, p1, p2)) {
			return false;
		}

		return true;
	}

    void destroyPlayer(PlayerObject* player, GameObject* p1) {
        PlayLayer::destroyPlayer(player, p1);
		
		if (!player->m_isDead) {
			return;
		}

		if (!m_fields->hasRespawned) {
			return;
		}

		m_fields->hasRespawned = false;
		m_fields->attemptCount++;
    }

	void resetLevel() {
		PlayLayer::resetLevel();

		m_fields->hasRespawned = true;
	}

	void onQuit() {
		PlayLayer::onQuit();
		Client::submitAttempt(m_fields->attemptCount);
	}
};