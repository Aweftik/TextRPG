#pragma once
#include <memory>
#include <vector>
#include <string>
#include <random>
#include "Room.h"
#include "EnemyFactory.h"
#include <clocale> // Поставить язык 
#include <Windows.h> 


inline Direction getOppositeDirection(Direction dir) {
    switch (dir) {
    case Direction::North: return Direction::South;
    case Direction::South: return Direction::North;
    case Direction::East:  return Direction::West;
    case Direction::West:  return Direction::East;
    }
    return Direction::South;
}


class DungeonGenerator {
private:
    EnemyFactory enemyFactory;
    std::mt19937 rng;
    std::vector<std::string> roomDescriptions;

public:
    DungeonGenerator();

    // Главная функция: генерирует линейный лабиринт из N комнат
    // Возвращает std::shared_ptr на стартовую (первую) комнату
    std::shared_ptr<Room> generateDungeon(int roomCount);
};