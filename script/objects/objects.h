#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
namespace Shapes {

	class Obj { // ������� ����� �������. ���� ��� �������-����������� ���, ��� ��� ��� ���������� ������������ ���� ������. ���-�� ����� ������ ����� �������� � ����������� �� ���� �������-�����������
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

		bool IsInRect(const sf::Vector2f& p) const; // ��������� �� ����� ������ ��������������?

		void drawer(sf::RenderWindow& window) const; // "�����������" ��� ������� Shapes::Obj
	};
}
