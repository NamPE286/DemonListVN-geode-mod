#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include "lib/AttemptCounter.hpp"
#include "lib/DeathCounter.hpp"

using namespace geode::prelude;

class $modify(DTPlayLayer, PlayLayer) {
	bool hasRespawned = false;
	AttemptCounter attemptCounter;
	DeathCounter deathCounter;

	bool init(GJGameLevel* level, bool p1, bool p2) {
		if (!PlayLayer::init(level, p1, p2)) {
			return false;
		}

		int id = level->m_levelID.value();
		auto best = level->m_normalPercent.value();

	 	m_fields->deathCounter = DeathCounter(id, best >= 100);

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
		m_fields->attemptCounter.add();

		if (!m_level->isPlatformer() && !m_isPracticeMode) {
			m_fields->deathCounter.add(this->getCurrentPercentInt());
		}
    }

	void resetLevel() {
		PlayLayer::resetLevel();

		m_fields->hasRespawned = true;
	}

	void onQuit() {
		PlayLayer::onQuit();
		
		m_fields->attemptCounter.submit();
		m_fields->deathCounter.submit();
	}
};