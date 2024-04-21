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

	class Obj { // ������� ����� �������. ���� ��� �������-����������� ���, ��� ��� ��� ���������� ������������ ���� ������. ���-�� ����� ������ ����� �������� � ����������� �� ���� �������-�����������
	private:
		sf::Vector2f position;
		sf::Vector2f size;
		sf::Texture texture;
		sf::Sprite sprite;
		bool created;
		bool harmful = 0;
		bool passable = 0;
	public:

		Obj();

		Obj(int x, int y, int width, int height);

		Obj(const std::string&, const sf::Vector2f&, const sf::Vector2f&);

		bool IsInRect(const sf::Vector2f& p) const; // ��������� �� ����� ������ ��������������?

		void drawer(sf::RenderWindow& window) const; // "�����������" ��� ������� Shapes::Obj



		sf::Vector2f get_position() const;

		sf::Vector2f get_size() const;

		float left_boarder() const;
		float right_boarder() const;
		float up_boarder() const;
		float down_boarder() const;

		bool is_passable() const;
	};
}
