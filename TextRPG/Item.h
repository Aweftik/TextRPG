#pragma once
#pragma once
#include <string>


enum class ItemType {
    Weapon,
    Potion
};

class Item {
private:
    std::string name;
    ItemType type;
    int value; // Урон для оружия или здоровье для зелья

public:
    Item(const std::string& name, ItemType type, int value);

    std::string getName() const { return name; }
    ItemType getType() const { return type; }
    int getValue() const { return value; }
};