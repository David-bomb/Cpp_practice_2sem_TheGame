#include "objects.h"

Shapes::Obj::Obj() : position(0, 0), size(0, 0), harmful(false), passable(false), created(false) { ; }

Shapes::Obj::Obj(const Obj& obj) : position(obj.position), size(obj.size), harmful(obj.harmful), passable(obj.passable), created(obj.created) {
	texture.loadFromImage(obj.texture.copyToImage());
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y));
	sprite.setPosition(position);
}

Shapes::Obj::Obj(const std::string& name, const sf::Vector2f& position, const sf::Vector2f& size, bool harmful, bool passable) : position(position), size(size), harmful(harmful), passable(passable), created(true) {
	if (!texture.loadFromFile(Leveling::generate_path(name))) { // Проверка на успешность загрузки текстуры. 
		std::cout << "Image loading failed.\n";
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y)); // Даем текстуре форму
	sprite.setPosition(position);
}

void Shapes::Obj::draw(sf::RenderWindow& window) const {
	if (created) {
		window.draw(sprite);
	}
	else {
		std::cout << "ERR: Attempt to draw empty object.\n";
	}
}

sf::Vector2f Shapes::Obj::get_position() const{
	return position;
}

sf::Vector2f Shapes::Obj::get_size() const {
	return size;
}

float Shapes::Obj::left_boarder() const {
	return position.x;
}
float Shapes::Obj::right_boarder() const {
	return position.x + size.x;
}
float Shapes::Obj::up_boarder() const {
	return position.y;
}
float Shapes::Obj::down_boarder() const {
	return position.y + size.y;
}

bool Shapes::Obj::is_passable() const {
	return passable;
}

bool Shapes::Obj::is_harmful() const {
	return harmful;
}
