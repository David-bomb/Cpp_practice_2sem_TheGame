#include "objects.h"

Shapes::Obj::Obj() {
	_width = _heigth = -1;
	point = sf::Vector2f();
	created = false;
}

Shapes::Obj::Obj(int x, int y, int width, int height) {
	point = sf::Vector2f(x, y); // ������ �������� �����, ��� ���� ��� �� ������������, �� � ������ �������� �����
	_width = width;
	_heigth = height;

	if (!texture.loadFromFile("Texture.png")) { // �������� �� ���������� �������� ��������. 
		//���� ��� Texture.png ����� � ����� � .exe ������, �� � ������� ���� ����� ����� ������ ������� ��-�����������
		std::cout << "Image loading failed.\n";
	}

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(x, y, width, height)); // ���� �������� �����
	sprite.setColor(sf::Color(0, 0, 255));
	created = true;
}

bool Shapes::Obj::IsInRect(const sf::Vector2f& p) const {
	return ((point.x < p.x) && (p.x < point.x + _width) && (point.y < p.y) && (p.y < point.y + _heigth)); // �������� ������� �������������� � �������
}

void Shapes::Obj::drawer(sf::RenderWindow& window) const {
	if (created) {
		window.draw(sprite);
	}
	else {
		std::cout << "ERR: Attempt to draw empty object.\n";
	}
}
