#pragma once
#include "Entity.h"
#include "Enemy.h"
#include <memory>
#include <random>

class EnemyFactory {
private: 
	std::mt19937 rng; // generator random numbers 


public :
	EnemyFactory(); 
	std::unique_ptr<Enemy> createRandomEnemy(); 

};
