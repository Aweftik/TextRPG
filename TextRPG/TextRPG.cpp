#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include "Player.h"
#include "DungeonGenerator.h"
#include "Item.h"
#include "Boss.h" 

void printDivider() {
    std::cout << "\n=====================================================\n";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    std::cout << "=====================================================\n";
    std::cout << "       ТЕНЬ В ПОДЗЕМЕЛЬЕ: ТЕКСТОВЫЙ КВЕСТ            \n";
    std::cout << "=====================================================\n\n";

    Player player("Артем", 100, 15);
    DungeonGenerator generator;

    player.addItem(std::make_unique<Item>("Старый стальной меч", ItemType::Weapon, 5));

    auto currentRoom = generator.generateDungeon(5);
    int roomNum = 1;

    while (currentRoom != nullptr && player.isAlive()) {
        printDivider();
        std::cout << "КОМНАТА " << roomNum << ": " << currentRoom->getDescription() << "\n";

        // === ПРОВЕРКА И СРАБАТЫВАНИЕ ЛОВУШКИ ПРИ ВХОДЕ ===
        if (currentRoom->checkTrap()) {
            currentRoom->triggerTrap();
            player.takeDamage(20);
            std::cout << "Ваше здоровье после ловушки: " << player.getHealth() << "/" << player.getMaxHealth() << "\n";

            if (!player.isAlive()) {
                std::cout << "\nВы погибли от ран, полученных в ловушке...\n";
                break;
            }
        }

        // === БОЕВОЙ ЦИКЛ ===
        if (currentRoom->hasEnemy()) {
            Enemy* enemy = currentRoom->getEnemy();

            // Проверяем, является ли враг Боссом для особого приветствия
            Boss* bossCheck = dynamic_cast<Boss*>(enemy);
            if (bossCheck != nullptr) {
                std::cout << "\n🔥 [БИТВА С БОССОМ!]: Перед вами владыка подземелья " << enemy->getName()
                    << " (HP: " << enemy->getHealth() << ", Атака: " << enemy->getAttackPower() << ")!\n";
            }
            else {
                std::cout << "\n[ВРАГ]: Перед вами " << enemy->getName()
                    << " (HP: " << enemy->getHealth() << ", Атака: " << enemy->getAttackPower() << ")!\n";
            }

            while (enemy->isAlive() && player.isAlive()) {
                std::cout << "\nВаше HP: " << player.getHealth() << "/" << player.getMaxHealth() << "\n";
                std::cout << "1. Атаковать\n2. Выпить зелье\n3. Инвентарь\n> ";

                int choice;
                std::cin >> choice;

                if (choice == 1) {
                    std::cout << "\nВы наносите " << player.getAttackPower() << " урона!\n";
                    enemy->takeDamage(player.getAttackPower());

                    if (!enemy->isAlive()) {
                        std::cout << "🎉 Вы повергли " << enemy->getName() << "!\n";
                        player.addXp(enemy->getExpReward());
                        player.addItem(std::make_unique<Item>("Зелье исцеления", ItemType::Potion, 30));
                        currentRoom->clearEnemy();
                        break;
                    }

                    // === ОТВЕТНЫЙ ХОД ВРАГА / БОССА ===
                    Boss* boss = dynamic_cast<Boss*>(enemy);
                    if (boss != nullptr && (rand() % 100 < 30)) {
                        // С шансом 30% Босс наносит двойной урон супер-атакой
                        int bossDamage = boss->useSpecialAbility();
                        player.takeDamage(bossDamage);
                    }
                    else {
                        // Обычная атака врага
                        std::cout << enemy->getName() << " отвечает атакой на " << enemy->getAttackPower() << " урона!\n";
                        player.takeDamage(enemy->getAttackPower());
                    }
                }
                else if (choice == 2) {
                    player.usePotion();

                    // При использовании зелья враг/босс все равно атакует
                    Boss* boss = dynamic_cast<Boss*>(enemy);
                    if (boss != nullptr && (rand() % 100 < 30)) {
                        int bossDamage = boss->useSpecialAbility();
                        player.takeDamage(bossDamage);
                    }
                    else {
                        std::cout << enemy->getName() << " пользуется моментом и наносит " << enemy->getAttackPower() << " урона!\n";
                        player.takeDamage(enemy->getAttackPower());
                    }
                }
                else if (choice == 3) {
                    player.showInventory();
                }
            }
        }

        if (!player.isAlive()) break;

        // === МЕНЮ ИССЛЕДОВАНИЯ ===
        bool moved = false;
        while (!moved && player.isAlive()) {
            std::cout << "\n[Доступные выходы]: " << currentRoom->getAvailableExits() << "\n";
            std::cout << "1. Север | 2. Юг | 3. Восток | 4. Запад | 5. Инвентарь | 6. Зелье\n> ";

            int choice;
            std::cin >> choice;

            Direction chosenDir;
            bool wantsToMove = false;

            if (choice == 1) { chosenDir = Direction::North; wantsToMove = true; }
            else if (choice == 2) { chosenDir = Direction::South; wantsToMove = true; }
            else if (choice == 3) { chosenDir = Direction::East;  wantsToMove = true; }
            else if (choice == 4) { chosenDir = Direction::West;  wantsToMove = true; }
            else if (choice == 5) { player.showInventory(); }
            else if (choice == 6) { player.usePotion(); }

            if (wantsToMove) {
                auto nextRoom = currentRoom->getExit(chosenDir);
                if (nextRoom != nullptr) {
                    currentRoom = nextRoom;
                    roomNum++;
                    moved = true;
                }
                else {
                    std::cout << "Сюда пройти нельзя — глухая стена!\n";
                }
            }
        }
    }

    printDivider();
    if (player.isAlive()) {
        std::cout << "\n=== ВЫ ПОБЕДИЛИ ВЛАДЫКУ ПОДЗЕМЕЛЬЯ И ВЫЖИЛИ! ===\n";
    }
    else {
        std::cout << "\n=== GAME OVER ===\n";
    }

    return 0;
}