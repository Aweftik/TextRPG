#include "Room.h"
#include <clocale> // Поставить язык 
#include <Windows.h> 

Room::Room(const std::string& description) : description(description), enemy(nullptr) {}
void Room::setExit(Direction dir, std::shared_ptr<Room> neighbor) {
	exits[dir] = neighbor; 
}
// В конструкторе Room инициализируем ловушки по умолчанию выключенными:
void Room::setTrap(int damage) {
	hasActiveTrap = true;
	trapDamage = damage;
}

bool Room::checkTrap() const {
	return hasActiveTrap;
}

void Room::triggerTrap() {
	if (hasActiveTrap) {
		std::cout << "[ЛОВУШКА!]: Вы задели скрытую растяжку! Ловушка наносит " << trapDamage << " урона!\n";
		hasActiveTrap = false; // Ловушка обезвреживается после срабатывания
	}
}
std::shared_ptr<Room> Room::getExit(Direction dir) const {

	auto it = exits.find(dir); 
	if (it != exits.end()) {
		return it->second; // Возвращаем найденную комнату
	}
	return nullptr; // если выхода в эту сторону нет 

}
std::string Room::getAvailableExits() const {
	std::string result = "";
	if (getExit(Direction::North)) result += "Север ";
	if (getExit(Direction::South)) result += "Юг ";
	if (getExit(Direction::East))  result += "Восток ";
	if (getExit(Direction::West))  result += "Запад ";

	if (result.empty()) return "Нет видимых выходов";
	return result;
}
void Room::setEnemy(std::unique_ptr<Enemy> newEnemy) {
	enemy = std::move(newEnemy); 
}
Enemy* Room::getEnemy() const {
	return enemy.get(); 
}
bool Room::hasEnemy() const {
	return enemy != nullptr && enemy->isAlive();
}
std::string Room::getDescription() const {
	return description;
}
void Room::clearEnemy() {
	enemy.reset();
}
