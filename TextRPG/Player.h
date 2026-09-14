#pragma once
#include "Entity.h" // включаем базовый класс для всех существ
#pragma once
#include <vector>
#include <memory>
#include "Item.h"

class Player : public Entity {
private:
    int xp;
    int level;
    std::vector<std::unique_ptr<Item>> inventory; // Инвентарь игрока

public:
    Player(const std::string& name, int health, int attackPower);

    void addXp(int amount);
    void addItem(std::unique_ptr<Item> item); // Забираем владение предметом
    void showInventory() const;
    void usePotion(); // Использование зелья из инвентаря

    int getXp() const;
    int getLevel() const;
};