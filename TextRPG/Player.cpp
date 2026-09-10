#include "Player.h"
#include <iostream>

// 1. Конструктор (закрывается своей фигурной скобкой })
Player::Player(const std::string& name, int health, int attackPower) // описания сущности что она имеет 
    : Entity(name, health, attackPower), xp(0), level(1) {
    // Тело конструктора
}

// 2. Метод addXp пишется ОТДЕЛЬНО от конструктора
void Player::addXp(int amount) {
    xp += amount; // добавление опыта 
    std::cout << "Получено опыта: " << amount << " (Всего: " << xp << ")\n"; // вывод сколько получено опыта 

    int xpToNextLevel = level * 100; // сколько нужно опыта для перехода 

    // Используем ключевое слово if вместо int
    if (xp >= xpToNextLevel) {
        xp -= xpToNextLevel;
        level++; // добавление уровня после успешной проверки хватает ли на переход следующий уровень 

        attackPower += 5;
        maxHealth += 20;
        health = maxHealth;

        std::cout << "Поздравляем! Новый уровень: " << level << "!\n";
        std::cout << "Атака выросла до: " << attackPower << ", HP восстановлено до " << maxHealth << "\n";
    }
}

// 3. Геттер getXp (исправлено имя с addXp на getXp)
int Player::getXp() const {
    return xp;
}

// 4. Геттер getLevel
int Player::getLevel() const {
    return level;
}