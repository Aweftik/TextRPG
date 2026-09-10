#include <iostream> // заголовочный файл в языке программирования C++, предназначенный для работы со стандартными потоками ввода и вывода.
#include "Player.h" // Выгрузка информации из этого файла 
#include <clocale> // Поставить язык 

int main() {
	setlocale(LC_ALL, "Russian"); // поставить русский язык для корректного вывода 
	Player player("losos", 100, 15);// сам персонаж 
	std::cout << "Player name: " << player.getName() << "\n"; // вывод имени персонажа 
	std::cout << "Level: " << player.getLevel() << ", Attack : " << player.getAttackPower() << "\n\n"; // вывод результатов повышения уровня 


	player.addXp(50); // фиктивное добавление опыта для проверки механики повышения уровня
	player.addXp(70);
	return 0;
}