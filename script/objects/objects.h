#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
namespace Shapes {

	class Obj { // Базовый класс объекта. Пока что классов-наследников нет, так что для тестировки используется этот объект. Кол-во полей класса может меняться в зависимости от нужд классов-наследников
	private:
		sf::Vector2f point;
		int _width;
		int _heigth;
		sf::Texture texture;
		sf::Sprite sprite;
		bool created;
	public:

		Obj();

		Obj(int x, int y, int width, int height);

		bool IsInRect(const sf::Vector2f& p) const; // Находится ли точка внутри прямоугольника?

		void drawer(sf::RenderWindow& window) const; // "Рисовальщик" для объекта Shapes::Obj
	};
}
