#include "Player.h"
#include <iostream>


Player::Player(const std::string& name, int health, int attackPower)
    : Entity(name, health, attackPower), xp(0), level(1) {
}

void Player::addXp(int amount) {
    xp += amount;
    std::cout << "Получено опыта: " << amount << " (Всего: " << xp << ")\n";

    int xpToNextLevel = level * 100;
    if (xp >= xpToNextLevel) {
        xp -= xpToNextLevel;
        level++;
        attackPower += 5;
        maxHealth += 20;
        health = maxHealth;
        std::cout << "ПОЗДРАВЛЯЕМ! Новый уровень: " << level << "!\n";
    }
}

void Player::addItem(std::unique_ptr<Item> item) {
    std::cout << "[ДОБЫЧА]: Вы получили предмет " << item->getName() << "!\n";

    // Если это оружие — сразу увеличиваем урон
    if (item->getType() == ItemType::Weapon) {
        attackPower += item->getValue();
        std::cout << "[ЭКИПИРОВКА]: Атака выросла на +" << item->getValue() << " (Теперь: " << attackPower << ")\n";
    }

    // Переносим unique_ptr в вектор инвентаря
    inventory.push_back(std::move(item));
}

void Player::showInventory() const {
    std::cout << "\n=== ИНВЕНТАРЬ ===\n";
    if (inventory.empty()) {
        std::cout << "(Пусто)\n";
        return;
    }
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << i + 1 << ". " << inventory[i]->getName() << "\n";
    }
}

void Player::usePotion() {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getType() == ItemType::Potion) {
            health += (*it)->getValue();
            if (health > maxHealth) health = maxHealth;
            std::cout << "[ЗЕЛЬЕ]: Вы испили " << (*it)->getName()
                << " и восстановили " << (*it)->getValue() << " HP! (Текущее HP: " << health << ")\n";

            inventory.erase(it); // Удаляем использованное зелье из вектора (память очистится автоматически)
            return;
        }
    }
    std::cout << "У вас нет зелий!\n";
}

int Player::getXp() const { return xp; }
int Player::getLevel() const { return level; }