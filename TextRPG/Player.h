#pragma once
#include "Entity.h" // включаем базовый класс для всех существ

class Player : public Entity { 
private : 
	int xp; 
	int level; 

public : 
	// объявление конструктора
	Player(const std::string& name, int health, int attackPower);
	// объявляем метод добавления опыта
	void addXp(int amount);
	// объявляем геттеры(функция для чтения приватных данных)
	int getXp() const; 
	
	int getLevel() const;
};