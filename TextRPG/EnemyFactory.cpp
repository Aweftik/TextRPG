#include "EnemyFactory.h"

EnemyFactory::EnemyFactory() {
	std::random_device rd;
		rng = std::mt19937(rd());
}
std::unique_ptr<Enemy> EnemyFactory::createRandomEnemy() {
	std::uniform_int_distribution<int> dist(0, 2); 
	int type = dist(rng); 
	switch (type) {
	case 0: 
			return std::make_unique<Enemy>("Slime", 20, 3, 15);
	case 1:
		return std::make_unique<Enemy>("Goblin", 20, 3, 15);
	case 2:
		return std::make_unique<Enemy>("Skelet", 20, 3, 15);
	default:
		return std::make_unique<Enemy>("Rat", 20, 3, 15);
	}
}