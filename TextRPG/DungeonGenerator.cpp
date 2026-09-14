#include "DungeonGenerator.h"
#include <clocale>
#include "Boss.h"

DungeonGenerator::DungeonGenerator() {
    std::random_device rd;
    rng = std::mt19937(rd());
   
   
    // Набор шаблонов описаний для атмосферы
    roomDescriptions = {
        "Темный сырой коридор, выложенный старым камнем.",
        "Заброшенный зал с разрушенными колоннами.",
        "Узкий затопленный туннель. Вода капает с потолка.",
        "Старая оружейная. На полу лежат ржавые доспехи.",
        "Зал с затухающим факелом на стене.",
        "Пещера с мерцающими светящимися грибами."
    };
}

// Добавь #include "Boss.h" в начало DungeonGenerator.cpp

std::shared_ptr<Room> DungeonGenerator::generateDungeon(int roomCount) {
    if (roomCount <= 0) return nullptr;

    auto startRoom = std::make_shared<Room>("Вход в подземелье. Назад пути нет.");
    auto currentRoom = startRoom;

    std::uniform_int_distribution<int> descDist(0, static_cast<int>(roomDescriptions.size()) - 1);
    std::uniform_int_distribution<int> enemyChanceDist(1, 100);
    std::uniform_int_distribution<int> dirDist(0, 3);

    std::vector<Direction> directions = { Direction::North, Direction::South, Direction::East, Direction::West };

    for (int i = 1; i < roomCount; ++i) {
        // Проверяем, последняя ли это комната
        bool isLastRoom = (i == roomCount - 1);

        std::string desc = isLastRoom
            ? "Огромный тронный зал, заваленный костями. Воздух пропитан махинациями и магией!"
            : roomDescriptions[descDist(rng)];

        auto nextRoom = std::make_shared<Room>(desc);

        if (isLastRoom) {
            // В ПОСЛЕДНЕЙ КОМНАТЕ ВСЕГДА БОСС!
            nextRoom->setEnemy(std::make_unique<Boss>(
                "Древний Дракон Лич", 150, 20, 500, "Дыхание Бездны"
            ));
        }
        else {
            // Обычная логика для рядовых комнат
            if (enemyChanceDist(rng) <= 70) {
                nextRoom->setEnemy(enemyFactory.createRandomEnemy());
            }
            else {
                std::uniform_int_distribution<int> trapChanceDist(1, 100);
                if (trapChanceDist(rng) <= 40) {
                    nextRoom->setTrap(15);
                }
            }
        }

        // Связывание комнат
        Direction chosenDir = directions[dirDist(rng)];
        while (currentRoom->getExit(chosenDir) != nullptr) {
            chosenDir = directions[dirDist(rng)];
        }

        Direction oppositeDir = getOppositeDirection(chosenDir);
        currentRoom->setExit(chosenDir, nextRoom);
        nextRoom->setExit(oppositeDir, currentRoom);

        currentRoom = nextRoom;
    }

    return startRoom;
}