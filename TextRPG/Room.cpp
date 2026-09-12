#include "Room.h"

Room::Room(const std::string& description) : description(description), enemy(nullptr) {}
void Room::setExit(Direction dir, std::shared_ptr<Room> neighbor) {
	exits[dir] = neighbor; 
}

std::shared_ptr<Room> Room::getExit(Direction dir) const {

	auto it = exits.find(dir); 
	if (it != exits.end()) {
		return it->second; // Возвращаем найденную комнату
	}
	return nullptr; // если выхода в эту сторону нет 

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
void Room::ClearEnemy() {
	enemy.reset(); // Освобождает память и делает указатель nullptr
}
std::string Room::getDescription() const {
	return description;
}