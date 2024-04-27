#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include "lib/AttemptCounter.hpp"
#include "lib/DeathCounter.hpp"

using namespace geode::prelude;

class $modify(DTPlayLayer, PlayLayer) {
	bool hasRespawned = false;
	AttemptCounter attemptCounter;
	DeathCounter deathCounter;

	bool init(GJGameLevel * level, bool p1, bool p2) {
		if (!PlayLayer::init(level, p1, p2)) {
			return false;
		}

		int id = level->m_levelID.value();
		auto best = level->m_normalPercent.value();

		m_fields->deathCounter = DeathCounter(id, best >= 100);

		return true;
	}

	void destroyPlayer(PlayerObject * player, GameObject * p1) {
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

CCLabelBMFont* createLabel(GJGameLevel* level, std::string str, int order) {
	int offset = (level->m_coins == 0) ? 17 : 4;
	auto size = CCDirector::sharedDirector()->getWinSize();
	int yoffset = 2;

	CCLabelBMFont* label = CCLabelBMFont::create(str.c_str(), "goldFont.fnt");

	label->setPosition({ size.width / 2 - 100, size.height / 2 + offset + yoffset + order * -10 });
	label->setScale(0.3f);

	return label;
}

class ButtonCreator {
public:
	void onButton(CCObject* sender) {
		int id = sender->getTag();
		std::string url = "https://demonlistvn.com/level/" + std::to_string(id);

		web::openLinkInBrowser(url);
	}

	CCMenu* create(std::vector<std::string> labels, GJGameLevel* level, CCLayer* layer) {
		int offset = (level->m_coins == 0) ? 17 : 4;
		auto size = CCDirector::sharedDirector()->getWinSize();

		std::string text;

		for (std::string& s : labels) {
			text += s;
			text += '\n';
		}

		text.pop_back();

		CCLabelBMFont* label = CCLabelBMFont::create(text.c_str(), "goldFont.fnt");

		label->setScale(0.3f);
		label->setAlignment(kCCTextAlignmentCenter);

		auto btn = CCMenuItemSpriteExtra::create(
			label, layer, menu_selector(ButtonCreator::onButton)
		);

		btn->setTag(level->m_levelID.value());

		auto menu = CCMenu::create();

		menu->addChild(btn);
		menu->setPosition({ size.width / 2 - 100, size.height / 2 + offset });

		return menu;
	}
};

class $modify(LevelInfoLayer) {
	bool init(GJGameLevel* level, bool a) {
		if (!LevelInfoLayer::init(level, a)) {
			return false;
		}

		if (level->m_demonDifficulty != 6 && level->m_demonDifficulty != 5) {
			return true;
		}

		int id = level->m_levelID.value();
		auto loadingLabel = createLabel(level, "...", 0);

		this->addChild(loadingLabel);

		web::AsyncWebRequest()
			.fetch("https://api.demonlistvn.com/level/" + std::to_string(id))
			.json()
			.then([this, level, loadingLabel](matjson::Value& res) {
				loadingLabel->removeFromParent();

				if (res["rating"].is_number() && res["flPt"].is_number()) {
					std::string dl = "DL: " + std::to_string(res["rating"].as_int()) + " (#" + std::to_string(res["dlTop"].as_int()) + ")";
					std::string fl = "FL: " + std::to_string(res["flPt"].as_int()) + " (#" + std::to_string(res["flTop"].as_int()) + ")";

					auto btn = ButtonCreator().create({ dl, fl }, level, this);

					this->addChild(btn);
				} else if (res["rating"].is_number()) {
					std::string dl = "DL: " + std::to_string(res["rating"].as_int()) + " (#" + std::to_string(res["dlTop"].as_int()) + ")";
					auto btn = ButtonCreator().create({ dl }, level, this);

					this->addChild(btn);
				} else if (res["flPt"].is_number()) {
					std::string fl = "FL: " + std::to_string(res["flPt"].as_double()) + " (#" + std::to_string(res["flTop"].as_int()) + ")";
					auto btn = ButtonCreator().create({ fl }, level, this);

					this->addChild(btn);
				}
			})
			.expect([loadingLabel](std::string const& error) {
				loadingLabel->removeFromParent();
			});

		return true;
	}
};