#include "../utils/DeathData.hpp"

class DeathCounter {
private:
	DeathData deathData;
public:
	DeathCounter();
	DeathCounter(int id, bool completed);
	void add(int percent);
	void submit();
};