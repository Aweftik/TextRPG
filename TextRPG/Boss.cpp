#include "Boss.h"
#include <iostream>

Boss::Boss(const std::string& name, int health, int attackPower, int expReward, const std::string& ability)
    : Enemy(name, health, attackPower, expReward), specialAbilityName(ability) {
}

int Boss::useSpecialAbility() {
    std::cout << "\n🔥 [БОСС ИСПОЛЬЗУЕТ СПОСОБНОСТЬ]: " << getName()
        << " кастует '" << specialAbilityName << "'!\n";
    return attackPower * 2; // Супер-атака наносит двойной урон!
}