#pragma once
#include <iostream> 
#include <string> 

class Entity { // параметры класса 
protected: 
	std::string name; 
	int health;
	int maxHealth; 
	int attackPower;
	
public: // выдача объекту параметров и проверка на жизнь
	Entity(const std::string& name, int health, int attackPower)
		:name(name), health(health), maxHealth(health), attackPower(attackPower) {}
	virtual ~Entity() = default;
	virtual void takeDamage(int damage) {
		health -= damage;
		if (damage <= 0) {
			health = 0; 
		}
	}
	// проверка жив ли 
	bool isAlive() const {
		return health > 0; 
	}
	// Геттеры чтобы получать параметры классу 
	std::string getName() const { return name; }
	int getHealth() const { return health;  }
	int getMaxHealth() const { return maxHealth; }
	int getAttackPower() const { return attackPower; } 
};