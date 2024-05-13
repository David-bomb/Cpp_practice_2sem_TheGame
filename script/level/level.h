#pragma once

#include "../player/player.h"

namespace Leveling {
	enum class Objects { Player, Movable, Obj };

	class SubLevel {
		friend class Level;
		std::vector<Shapes::Obj> objects; // список объектов
		std::vector<Moving::Movable> movables; // список подвижных объектов
		Moving::Player player; // игрок
		int number; // номер уровня
		int n; // номер подуровня
		int read_from_file(const std::string&); // считать подуровень из файла
		int write_to_file(const std::string&); // записать подуровень в файл (мертвая функция, можно удалить)
		int update_window(sf::RenderWindow&);
	public:
		SubLevel(int, int);
		int start(sf::RenderWindow&); // запуск подуровня
		int restart(); // перезапуск
	};

	class Level {
		std::vector<SubLevel> sublevels; // список подуровней
		int number; // номер уровня
		int k; // количество подуровней
	public:
		Level(int, int);
		int start(sf::RenderWindow&); // запуск уровня
		int generate() const; // генерация
		int restart() const; // перезапуск
	};



	std::string generate_path(const std::string&);
	std::string generate_sublevel_name(int, int);
	std::string generate_sublevel_original_name(int, int);
	std::string generate_sound_path(const std::string&);
}
