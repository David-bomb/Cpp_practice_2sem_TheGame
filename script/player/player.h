#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "../constants/constants.h"

namespace Character {
	class Player { // ����� ���������
	private:
		float y_speed;
		sf::Vector2f position; // �������
		sf::Vector2f size; // ������
		sf::Texture texture; // ��������
		sf::Sprite sprite; // ������
		int move_on(float, int); // ��������� �� �����, int ( -1 ��� �����; 1 ��� �����)
		int move_down(float);
	public:
		Player(const std::string&, const sf::Vector2f&, const sf::Vector2f&);  // ������� �����������
		int draw(sf::RenderWindow&) const; // ����� ��������
		int update(float); // ���������� ������
		int jump(); // ������
	};
}

