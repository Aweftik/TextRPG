#pragma once
#include "Entity.h" 

class Enemy : public Entity {
private:
		int expReward; // выдаваемый опыт за монстра 
public:
		Enemy(const std::string& name, int health, int attackPower, int expReward); 
	int getExpReward() const; 
};