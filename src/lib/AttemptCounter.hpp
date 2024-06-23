#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/Geode.hpp>

class AttemptCounter {
private:
	size_t cnt;
public:
	void add();
	void submit(geode::prelude::EventListener<geode::prelude::web::WebTask>* m_listener);
};