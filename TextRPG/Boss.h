#pragma once
#include "Enemy.h"

class Boss : public Enemy {
private:
    std::string specialAbilityName;

public:
    Boss(const std::string& name, int health, int attackPower, int expReward, const std::string& ability);

    // Уникальная супер-атака Босса
    int useSpecialAbility();
};