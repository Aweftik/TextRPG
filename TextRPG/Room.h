#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "Enemy.h"

// Перечисление для направлений движения в подземелье
enum class Direction {
    North,
    South,
    East,
    West
};

class Room {
private:
    std::string description;
    std::unique_ptr<Enemy> enemy;

    // Графовая структура: связи с соседами через smart pointers
    std::unordered_map<Direction, std::shared_ptr<Room>> exits;

    // Механика ловушек
    bool hasActiveTrap;
    int trapDamage;

public:
    // Конструктор (только объявление)
    explicit Room(const std::string& description);

    // Деструктор по умолчанию
    ~Room() = default;

    // --- Управление описанием и выходами ---
    std::string getDescription() const;
    std::string getAvailableExits() const;
    std::shared_ptr<Room> getExit(Direction dir) const;
    void setExit(Direction dir, std::shared_ptr<Room> room);

    // --- Управление врагом ---
    bool hasEnemy() const;
    Enemy* getEnemy() const;
    void setEnemy(std::unique_ptr<Enemy> newEnemy);
    void clearEnemy(); // Вместо clearEnemy()

    // --- Управление ловушками ---
    void setTrap(int damage);
    bool checkTrap() const;
    void triggerTrap();
};