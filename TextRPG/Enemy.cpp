#include "Enemy.h"

Enemy:: Enemy( const std::string& name, int health, int attackPower,int expReward) : Entity(name, health,attackPower), expReward(expReward) {}

int Enemy::getExpReward() const {
	return expReward; 
}