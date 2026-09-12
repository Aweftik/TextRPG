#include <iostream> // заголовочный файл в языке программирования C++, предназначенный для работы со стандартными потоками ввода и вывода.
#include "Player.h" // Выгрузка информации из этого файла 
#include <clocale> // Поставить язык 
#include <Windows.h> 
#include "EnemyFactory.h"


int main() {
	SetConsoleOutputCP(CP_UTF8);
	setlocale(LC_ALL, "Russian"); // поставить русский язык для корректного вывода 
	Player player("losos", 100, 15);// сам персонаж 
	std::cout << "Player name: " << player.getName() << "\n"; // вывод имени персонажа 
	std::cout << "Level: " << player.getLevel() << ", Attack : " << player.getAttackPower() << "\n\n"; // вывод результатов повышения уровня 

	EnemyFactory factory; 
	for (int i = 0; i < 3; ++i) {
		auto enemy = factory.createRandomEnemy(); 
		std::cout << "Появился монстр:  " << enemy->getName()
			<< " (HP: " << enemy->getHealth()
			<< " (Damage: " << enemy->getAttackPower() << ")\n"; 

	}
	
	return 0; 
}
