#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "../constants/constants.h"

namespace Character {
	class Player { // класс персонажа
	private:
		float y_speed;
		sf::Vector2f position; // позиция
		sf::Vector2f size; // размер
		sf::Texture texture; // текстура
		sf::Sprite sprite; // спрайт
		int move_on(float, int); // подвинуть за время, int ( -1 для влево; 1 для право)
		int move_down(float);
	public:
		Player(const std::string&, const sf::Vector2f&, const sf::Vector2f&);  // базовый конструктор
		int draw(sf::RenderWindow&) const; // вывод текстуры
		int update(float); // обновление игрока
		int jump(); // прыжок
	};
}

