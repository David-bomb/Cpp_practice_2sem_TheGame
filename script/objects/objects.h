#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "../constants/constants.h"

namespace Leveling {
	std::string generate_path(const std::string&);
	std::string generate_sound_path(const std::string& name);
}

namespace Shapes {

	class Obj { // Базовый класс объекта. Пока что классов-наследников нет, так что для тестировки используется этот объект. Кол-во полей класса может меняться в зависимости от нужд классов-наследников
	private:
		sf::Vector2f position;
		sf::Vector2f size;
		sf::Texture texture;
		sf::Sprite sprite;
		bool harmful; // опасный (если не проходимый, то определения направления (следующий уровень true /предыдущий уровень false))
		bool passable; // проходимый (если не проходимый, то служит для перехода между уровнями)
		bool created;
	public:
		Obj();
		Obj(const Obj&);
		Obj(const std::string&, const sf::Vector2f&, const sf::Vector2f&, bool, bool);

		void draw(sf::RenderWindow& window) const;

		sf::Vector2f get_position() const;
		sf::Vector2f get_size() const;
		float left_boarder() const;
		float right_boarder() const;
		float up_boarder() const;
		float down_boarder() const;
		bool is_passable() const;
		bool is_harmful() const;
	};
}

namespace Audio {
	class Sounds {
		sf::SoundBuffer buffer;
		sf::Sound sound;
	public:
		Sounds(const std::string& filename); // создаем объект звука по имени
		Sounds(); // пустышка
		int play(); // проиграть звук
		int setVolume(int volume); // установить громкость
		int setLoop(bool looped); // зациклить
	};

	class Music {
		sf::Music music;
	public:
		Music(const std::string& filename); // создаем объект музыки по имени
		Music(); // пустышка
		int play(); // проиграть музыку
		int setVolume(int volume); // установить громкость
		int setLoop(bool looped); // зациклить
	};
}
