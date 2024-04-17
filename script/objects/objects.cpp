#include "objects.h"

Shapes::Obj::Obj() {
	_width = _heigth = -1;
	point = sf::Vector2f();
	created = false;
}

Shapes::Obj::Obj(int x, int y, int width, int height) {
	point = sf::Vector2f(x, y); // Задаем значение точки, тут пока оно не используется, но в других объектах будет
	_width = width;
	_heigth = height;

	if (!texture.loadFromFile("Texture.png")) { // Проверка на успешность загрузки текстуры. 
		//Пока что Texture.png лежит в папке с .exe файлом, но в будущем надо будет найти способ сделать по-человечески
		std::cout << "Image loading failed.\n";
	}

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(x, y, width, height)); // Даем текстуре форму
	sprite.setColor(sf::Color(0, 0, 255));
	created = true;
}

bool Shapes::Obj::IsInRect(const sf::Vector2f& p) const {
	return ((point.x < p.x) && (p.x < point.x + _width) && (point.y < p.y) && (p.y < point.y + _heigth)); // Проверка условий принадлежности к области
}

void Shapes::Obj::drawer(sf::RenderWindow& window) const {
	if (created) {
		window.draw(sprite);
	}
	else {
		std::cout << "ERR: Attempt to draw empty object.\n";
	}
}
