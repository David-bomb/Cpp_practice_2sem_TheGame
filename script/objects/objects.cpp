#include "objects.h"

Shapes::Obj::Obj() {
	size = { 0,0 };
	position = sf::Vector2f();
	created = false;
}

Shapes::Obj::Obj(int x, int y, int width, int height) {
	position = sf::Vector2f(x, y); // ������ �������� �����, ��� ���� ��� �� ������������, �� � ������ �������� �����
	size = sf::Vector2f(width, height);

	if (!texture.loadFromFile(Leveling::generate_path("Texture.png"))) { // �������� �� ���������� �������� ��������. 
		//���� ��� Texture.png ����� � ����� � .exe ������, �� � ������� ���� ����� ����� ������ ������� ��-�����������
		std::cout << "Image loading failed.\n";
	}

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, width, height)); // ���� �������� �����
	sprite.setPosition(position);
	//sprite.setColor(sf::Color(0, 0, 255));
	created = true;
}

bool Shapes::Obj::IsInRect(const sf::Vector2f& p) const {
	return ((position.x < p.x) && (p.x < position.x + size.x) && (position.y < p.y) && (p.y < position.y + size.y)); // �������� ������� �������������� � �������
}

void Shapes::Obj::drawer(sf::RenderWindow& window) const {
	if (created) {
		window.draw(sprite);
	}
	else {
		std::cout << "ERR: Attempt to draw empty object.\n";
	}
}



Shapes::Obj::Obj(const std::string& name, const sf::Vector2f& position, const sf::Vector2f& size): position(position), size(size) {
	if (!texture.loadFromFile(Leveling::generate_path(name))) { // �������� �� ���������� �������� ��������. 
		//���� ��� Texture.png ����� � ����� � .exe ������, �� � ������� ���� ����� ����� ������ ������� ��-�����������
		std::cout << "Image loading failed.\n";
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, (int)size.x, (int)size.y)); // ���� �������� �����
	sprite.setPosition(position);
	created = true;
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
