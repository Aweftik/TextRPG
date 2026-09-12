#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "Enemy.h"

enum class Direction {
	North,
	South,
	East,
	West
};

class Room {
private: 
	std::string description; 
	// Враг в комнате (уникальное владение — комната владеет врагом)
	std::unique_ptr<Enemy> enemy; 
	// Связи с другими комнатами
	// Используем shared_ptr для перехода между локациями
	std::unordered_map<Direction, std::shared_ptr<Room>> exits; 

public: 
	// Связывание комнат
	explicit Room(const std::string& description); 
	void setExit(Direction dir, std::shared_ptr<Room> neighbor); 
	std::shared_ptr<Room> getExit(Direction dir) const; 
	// Работа с врагом
	void setEnemy(std::unique_ptr<Enemy> newEnemy); 

	Enemy* getEnemy() const; // Возвращаем сырой указатель для чтения, не передавая владение 
	bool hasEnemy() const; 
	void ClearEnemy(); // Вызывается после победы над врагом

	std::string getDescription() const;
};