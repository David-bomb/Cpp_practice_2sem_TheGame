#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "../constants/constants.h"

namespace Leveling {
	std::string generate_path(const std::string&);
}

namespace Shapes {

	class Obj { // Базовый класс объекта. Пока что классов-наследников нет, так что для тестировки используется этот объект. Кол-во полей класса может меняться в зависимости от нужд классов-наследников
	private:
		sf::Vector2f position;
		sf::Vector2f size;
		sf::Texture texture;
		sf::Sprite sprite;
		bool harmful;
		bool passable;
		bool created;
	public:
		Obj();
		Obj(const Obj&);
		Obj(const std::string&, const sf::Vector2f&, const sf::Vector2f&, bool, bool);

		void draw(sf::RenderWindow& window) const; // "Рисовальщик" для объекта Shapes::Obj

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
